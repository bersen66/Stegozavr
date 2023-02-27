#include <stegozavr/api/v1/encode.hpp>

namespace api::v1 {

userver::formats::json::Value EncodeHandler::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                                             const userver::formats::json::Value& request_json,
                                                             userver::server::request::RequestContext& context) const
{
  return userver::formats::json::Value();
}

} // namespace api::v1
