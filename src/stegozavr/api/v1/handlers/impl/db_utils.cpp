#include <stegozavr/api/v1/handlers/queries.hpp>

#include "db_utils.hpp"


namespace pg = userver::storages::postgres;
namespace api::v1::handlers::impl {

bool HasUser(pg::ClusterPtr pg_cluster, std::string_view username)
{
  auto res = pg_cluster->Execute(pg::ClusterHostType::kSlave, queries::kHasUser, username);
  return res.AsSingleRow<std::int64_t>();
}

} // api::v1::handlers::impl
