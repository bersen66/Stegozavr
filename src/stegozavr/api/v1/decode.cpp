#include <stegozavr/api/v1/decode.hpp>
#include <stegozavr/engine/decode/decode.hpp>
#include <userver/crypto/base64.hpp>
#include <userver/logging/log.hpp>

namespace api::v1
{

userver::formats::json::Value DecodeHandler::HandleRequestJsonThrow(
    const userver::server::http::HttpRequest& request, const userver::formats::json::Value& request_json,
    userver::server::request::RequestContext& context) const
{
  namespace json = ::userver::formats::json;
  namespace base64 = ::userver::crypto::base64;
  namespace engine = ::stegozavr::engine;

  LOG_INFO() << "Started decoding";
  json::ValueBuilder value_builder;

  if (request_json.HasMember("file_content"))
  {
    try
    {
      const auto& file_content = base64::Base64Decode(request_json["file_content"].As<std::string>());
      value_builder["result"] = engine::blocking::Decode(file_content);
      value_builder["status"] = "Ok";
    }
    catch (const std::exception& exc)
    {
      value_builder["status"] = "Error";
      value_builder["info"] = exc.what();
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

} // namespace api::v1