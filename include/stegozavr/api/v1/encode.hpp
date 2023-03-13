#pragma once

#include <userver/components/minimal_component_list.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/utils/daemon_run.hpp>

namespace api::v1
{

/**
 * This API handler is
 *
 */

class EncodeHandler final : public userver::server::handlers::HttpHandlerJsonBase
{
public:
  static constexpr std::string_view kName = "handler-encode";
  using userver::server::handlers::HttpHandlerJsonBase::HttpHandlerJsonBase;

  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request, const userver::formats::json::Value& request_json,
      userver::server::request::RequestContext& context) const override;

private:
};

} // namespace api::v1
