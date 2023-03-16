#include <stegozavr/api/v1/handlers/queries.hpp>

#include "db_utils.hpp"

namespace api::v1::handlers::impl
{

bool HasUser(userver::storages::postgres::ClusterPtr pg_cluster, std::string_view username)
{
  auto res = pg_cluster->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::kHasUser, username);
  return res.AsSingleRow<std::int64_t>();
}

bool UserCanUseThisToken(userver::storages::postgres::ClusterPtr pg_cluster, std::string_view username,
                         std::string_view token)
{
  auto res = pg_cluster->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::kUserCanUseThisToken,
                                 username, token);
  return (res.AsSingleRow<std::int64_t>() != 0);
}

} // namespace api::v1::handlers::impl
