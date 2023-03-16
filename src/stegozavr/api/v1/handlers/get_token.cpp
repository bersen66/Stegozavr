#include <userver/logging/log.hpp>
#include <userver/utils/uuid4.hpp>

#include <stegozavr/api/v1/handlers/get_token.hpp>
#include <stegozavr/api/v1/handlers/queries.hpp>

#include "impl/db_utils.hpp"

namespace pg = ::userver::storages::postgres;
namespace json = ::userver::formats::json;

namespace api::v1::handlers
{

GetToken::GetToken(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context)
    : userver::server::handlers::HttpHandlerJsonBase(config, context)
    , pg_cluster_(context.FindComponent<userver::components::Postgres>("stegozavr_db").GetCluster())
{
  LOG_INFO() << "HANDLER: GetToken started";
}

json::Value GetToken::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                             const json::Value& request_json,
                                             userver::server::request::RequestContext& context) const
{

  json::ValueBuilder value_builder;

  if (!request_json.HasMember("username"))
  {
    LOG_INFO() << "Required fields is missing.";
    value_builder["status"] = "Error";
    value_builder["message"] = "Required field is missing. See doc for explanation.";
    return value_builder.ExtractValue();
  }

  const auto& username = request_json["username"].As<std::string>();

  if (!impl::HasUser(pg_cluster_, username))
  {
    LOG_INFO() << "User not found";
    value_builder["status"] = "Error";
    value_builder["message"] = "User not found.";
    return value_builder.ExtractValue();
  }

  {
    pg::Transaction transaction = pg_cluster_->Begin("get_token_transaction", pg::ClusterHostType::kMaster, {});
    auto token = GenerateToken(transaction);

    if (!InsertToken(transaction, token))
    {
      LOG_INFO() << "Token not inserted";
      value_builder["status"] = "Error";
      value_builder["message"] = "Token not inserted.";
      transaction.Rollback();
    }
    else
    {
      try
      {
        transaction.Execute(queries::kAttachTokenToUser, UserId(transaction, username), TokenId(transaction, token));
        transaction.Commit();
        LOG_INFO() << "Token inserted";
        value_builder["status"] = "Ok";
        value_builder["token"] = token;
      }
      catch (std::exception& exc)
      {
        transaction.Rollback();
        LOG_ERROR() << "Exception occured" << exc.what();
        value_builder["status"] = "Error";
        value_builder["message"] = exc.what();
      }
    }
  }

  return value_builder.ExtractValue();
}

std::string GetToken::GenerateToken(userver::storages::postgres::Transaction& transaction) const
{
  std::string result;
  while (true)
  {
    auto temp = userver::utils::generators::GenerateUuid();
    if (IsUniqueToken(transaction, temp))
    {
      result = std::move(temp);
      break;
    }
  }
  return result;
}

bool GetToken::IsUniqueToken(userver::storages::postgres::Transaction& transaction, std::string_view token) const
{
  auto res = transaction.Execute(queries::kHasToken, token);
  return (res.AsSingleRow<std::int64_t>() == 0);
}

std::size_t GetToken::InsertToken(userver::storages::postgres::Transaction& transaction, std::string_view token) const
{
  auto res = transaction.Execute(queries::kInsertToken, token);
  return res.RowsAffected();
}

std::int64_t GetToken::UserId(userver::storages::postgres::Transaction& transaction, std::string_view username) const
{
  auto res = transaction.Execute(queries::kGetUserId, username);
  return res.AsSingleRow<std::int64_t>();
}

std::int64_t GetToken::TokenId(userver::storages::postgres::Transaction& transaction, std::string_view token) const
{
  auto res = transaction.Execute(queries::kGetTokenId, token);
  return res.AsSingleRow<std::int64_t>();
}

} // namespace api::v1::handlers