#include <stegozavr/api/v1/encode.hpp>
#include <stegozavr/engine/encode/encode.hpp>
#include <userver/crypto/base64.hpp>

namespace api::v1 {

userver::formats::json::Value EncodeHandler::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                                             const userver::formats::json::Value& request_json,
                                                             userver::server::request::RequestContext& context) const
{
  namespace json = userver::formats::json;
  namespace base64 = userver::crypto::base64;

  auto file_content = base64::Base64Decode(request_json["file_content"].As<std::string>());
  auto text_to_hide = request_json["text_to_hide"].As<std::string>();

  // TODO: FIX BUG WITH ENCODING
  // ::stegozavr::engine::blocking::Encode(file_content, {text_to_hide.begin(), text_to_hide.end()});

  json::ValueBuilder value_builder;
  value_builder["result"] = base64::Base64Encode(file_content);
  return value_builder.ExtractValue();
}

} // namespace api::v1
