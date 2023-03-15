#include <stegozavr/api/v1/handlers/get_token.hpp>
#include <userver/logging/log.hpp>

namespace api::v1::handlers
{

GetToken::GetToken(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context)
    : userver::server::handlers::HttpHandlerJsonBase(config, context)
    , pg_cluster_(context.FindComponent<userver::components::Postgres>("stegozavr_db").GetCluster())
{
  LOG_INFO() << "HANDLER: GetToken started";
}

userver::formats::json::Value GetToken::HandleRequestJsonThrow(const userver::server::http::HttpRequest& request,
                                                               const userver::formats::json::Value& request_json,
                                                               userver::server::request::RequestContext& context) const
{

  namespace pg = ::userver::storages::postgres;
  userver::formats::json::ValueBuilder value_builder;

  pg::Transaction transaction =
      pg_cluster_->Begin("get_token_transaction", pg::ClusterHostType::kMaster, {});

  return value_builder.ExtractValue();
}

} // namespace api::v1::handlers