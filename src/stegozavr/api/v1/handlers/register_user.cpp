#include <stegozavr/api/v1/handlers/register_user.hpp>
#include <stegozavr/api/v1/handlers/queries.hpp>

#include <userver/logging/log.hpp>
#include <string_view>


namespace api::v1::handlers
{

RegisterUser::RegisterUser(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context)
    : userver::server::handlers::HttpHandlerJsonBase(config, context)
    , pg_cluster_(context.FindComponent<userver::components::Postgres>("stegozavr_db").GetCluster())
{
  LOG_INFO() << "HANDLER: RegisterUser started";
}

userver::formats::json::Value RegisterUser::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                                          const userver::formats::json::Value& request_json,
                                                          userver::server::request::RequestContext& context) const
{

  userver::formats::json::ValueBuilder value_builder;
  if (request_json.HasMember("username"))
  {
    const auto& username = request_json["username"].As<std::string>();
    try
    {
      InsertUser(username);
      value_builder["status"] = "Ok";
      value_builder["message"] = "User been inserted successfully";
    }
    catch (const std::exception& exc)
    {
      value_builder["status"] = "Error";
      value_builder["info"] = exc.what();
      LOG_INFO() << "Exception occurred: " << exc.what();
    }
  }
  else
  {
    LOG_DEBUG() << "Required fields is missing";
    value_builder["status"] = "Error";
    value_builder["message"] = "Required field is missing. See doc for explanation.";
  }

  return value_builder.ExtractValue();
}



void RegisterUser::InsertUser(std::string_view username) const
{
  pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::kInsertUser, username);
}

} // namespace api::v1::handlers