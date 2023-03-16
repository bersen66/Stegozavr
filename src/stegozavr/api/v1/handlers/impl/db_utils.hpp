#pragma once

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace api::v1::handlers::impl
{

bool HasUser(userver::storages::postgres::ClusterPtr pg_cluster, std::string_view username);

bool UserCanUseThisToken(userver::storages::postgres::ClusterPtr pg_cluster, std::string_view username,
                         std::string_view token);

} // namespace api::v1::handlers::impl
