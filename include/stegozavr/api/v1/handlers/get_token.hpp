#pragma once

#include <userver/components/minimal_component_list.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/utils/daemon_run.hpp>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

#include <string>
#include <string_view>


namespace api::v1::handlers
{

class GetToken final : public userver::server::handlers::HttpHandlerJsonBase
{
public:
  static constexpr std::string_view kName = "handler-get-token";
  using userver::server::handlers::HttpHandlerJsonBase::HttpHandlerJsonBase;

  GetToken(const userver::components::ComponentConfig& config, const userver::components::ComponentContext& context);

  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request, const userver::formats::json::Value& request_json,
      userver::server::request::RequestContext& context) const override;

private:
  std::string GenerateToken(userver::storages::postgres::Transaction& transaction) const;

  bool IsUniqueToken(userver::storages::postgres::Transaction& transaction, std::string_view token) const;

  size_t InsertToken(userver::storages::postgres::Transaction& transaction, std::string_view token) const;


  std::int64_t UserId(userver::storages::postgres::Transaction& transaction, std::string_view username) const;

  std::int64_t TokenId(userver::storages::postgres::Transaction& transaction, std::string_view token) const;

private:
  userver::storages::postgres::ClusterPtr pg_cluster_;

};

} // namespace api::v1::handlers