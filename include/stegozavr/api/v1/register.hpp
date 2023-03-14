#pragma once

#include <userver/components/minimal_component_list.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/utils/daemon_run.hpp>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace api::v1 {

class RegisterHandler final : public userver::server::handlers::HttpHandlerJsonBase {
public:
  static constexpr std::string_view kName = "handler-register";
  using userver::server::handlers::HttpHandlerJsonBase::HttpHandlerJsonBase;

  RegisterHandler(const userver::components::ComponentConfig& config,
                  const userver::components::ComponentContext& context);

  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request, const userver::formats::json::Value& request_json,
      userver::server::request::RequestContext& context) const override;

private:
  userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace api::v1