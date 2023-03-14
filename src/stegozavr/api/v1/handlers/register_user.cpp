#include <stegozavr/api/v1/handlers/register_user.hpp>

namespace api::v1::handlers {

RegisterUser::RegisterUser(const userver::components::ComponentConfig& config,
                                 const userver::components::ComponentContext& context)
  : userver::server::handlers::HttpHandlerJsonBase(config, context),
    pg_cluster_(context.FindComponent<userver::components::Postgres>("stegozavr").GetCluster())
{
  LOG_DEBUG() << "RegisterUser started";
}


userver::formats::json::Value RegisterUser::HandleRequestJsonThrow(
    const userver::server::http::HttpRequest& request,
    const userver::formats::json::Value& request_json,
    userver::server::request::RequestContext& context) const
{
  return userver::formats::json::Value();
}
} // namespace api::v1