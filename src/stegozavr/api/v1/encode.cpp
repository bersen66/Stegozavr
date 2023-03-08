#include <stegozavr/api/v1/encode.hpp>
#include <stegozavr/engine/encode/encode.hpp>
#include <userver/crypto/base64.hpp>
#include <userver/logging/log.hpp>

namespace api::v1
{

userver::formats::json::Value EncodeHandler::HandleRequestJsonThrow(
    const userver::server::http::HttpRequest& request, const userver::formats::json::Value& request_json,
    userver::server::request::RequestContext& context) const
{
  namespace json = ::userver::formats::json;
  namespace base64 = ::userver::crypto::base64;
  namespace engine = ::stegozavr::engine;

  LOG_INFO() << "Started encoding";
  json::ValueBuilder value_builder;

  if (request_json.HasMember("text_to_hide") && request_json.HasMember("file_content")) {
    LOG_DEBUG() << "Request contains all fields";

    auto file_content = base64::Base64Decode(request_json["file_content"].As<std::string>());
    auto text_to_hide = request_json["text_to_hide"].As<std::string>();

    value_builder["status"] = "Ok";
    value_builder["result"] = base64::Base64Encode(engine::blocking::Encode(file_content, text_to_hide));
  } else {
    LOG_DEBUG() << "Required fields is missing";
    value_builder["status"] = "Error";
    value_builder["message"] = "Required field is missing. See doc for explanation.";
  }

  LOG_INFO() << "Encoding finished";
  return value_builder.ExtractValue();
}

} // namespace api::v1
