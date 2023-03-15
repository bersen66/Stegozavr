#include <stegozavr/api/v1/handlers/encode.hpp>
#include <stegozavr/engine/encode/encode.hpp>
#include <userver/crypto/base64.hpp>
#include <userver/logging/log.hpp>



namespace api::v1::handlers
{

Encode::Encode(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context)
    : userver::server::handlers::HttpHandlerJsonBase(config, context)
{
  LOG_INFO() << "HANDLER: Encode started";
}

userver::formats::json::Value Encode::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                                             const userver::formats::json::Value& request_json,
                                                             userver::server::request::RequestContext& context) const
{
  namespace json = ::userver::formats::json;
  namespace base64 = ::userver::crypto::base64;
  namespace engine = ::stegozavr::engine;

  LOG_INFO() << "Started encoding";
  json::ValueBuilder value_builder;

  if (request_json.HasMember("text_to_hide") && request_json.HasMember("file_content"))
  {
    LOG_DEBUG() << "Request contains all fields";

    auto file_content = base64::Base64Decode(request_json["file_content"].As<std::string>());
    auto text_to_hide = request_json["text_to_hide"].As<std::string>();

    try
    {
      value_builder["result"] = base64::Base64Encode(engine::blocking::Encode(file_content, text_to_hide));
      value_builder["status"] = "Ok";
    }
    catch (const std::exception& exception)
    {
      value_builder["status"] = "Error";
      value_builder["info"] = exception.what();
      LOG_INFO() << "Exception occurred: " << exception.what();
    }
  }
  else
  {
    LOG_DEBUG() << "Required fields is missing";
    value_builder["status"] = "Error";
    value_builder["message"] = "Required field is missing. See doc for explanation.";
  }

  LOG_INFO() << "Encoding finished";
  auto result = value_builder.ExtractValue();
  return result;
}

} // namespace api::v1::handlers
