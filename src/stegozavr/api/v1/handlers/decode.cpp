#include "impl/db_utils.hpp"
#include <stegozavr/api/v1/handlers/decode.hpp>
#include <stegozavr/engine/decode/decode.hpp>
#include <userver/crypto/base64.hpp>
#include <userver/logging/log.hpp>
namespace api::v1::handlers
{

Decode::Decode(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context)
    : userver::server::handlers::HttpHandlerJsonBase(config, context)
    , pg_cluster_(context.FindComponent<userver::components::Postgres>("stegozavr_db").GetCluster())
{
  LOG_INFO() << "HANDLER: Decode started";
}

userver::formats::json::Value Decode::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                                             const userver::formats::json::Value& request_json,
                                                             userver::server::request::RequestContext& context) const
{
  namespace json = ::userver::formats::json;
  namespace base64 = ::userver::crypto::base64;
  namespace engine = ::stegozavr::engine;

  LOG_INFO() << "Started decoding";
  json::ValueBuilder value_builder;

  if (request_json.HasMember("username") && request_json.HasMember("token") && request_json.HasMember("file_content"))
  {
    try
    {
      const auto& username = request_json["username"].As<std::string>();
      const auto& token = request_json["token"].As<std::string>();

      if (!impl::UserCanUseThisToken(pg_cluster_, username, token))
      {
        LOG_DEBUG() << "Identification is failed.";
        value_builder["status"] = "Error";
        value_builder["message"] = "Identification is failed.";
        return value_builder.ExtractValue();
      }

      const auto& file_content = base64::Base64Decode(request_json["file_content"].As<std::string>());
      value_builder["result"] = engine::blocking::Decode(file_content);
      value_builder["status"] = "Ok";
    }
    catch (const std::exception& exc)
    {
      value_builder["status"] = "Error";
      value_builder["info"] = exc.what();
      LOG_DEBUG() << "Exception occurred: " << exc.what();
    }
  }
  else
  {
    LOG_DEBUG() << "Required fields is missing";
    value_builder["status"] = "Error";
    value_builder["message"] = "Required field is missing. See doc for explanation.";
  }

  LOG_INFO() << "Finished decoding";
  return value_builder.ExtractValue();
}

} // namespace api::v1::handlers