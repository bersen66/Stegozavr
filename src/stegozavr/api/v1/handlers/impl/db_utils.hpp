#pragma once

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace api::v1::handlers::impl {

bool HasUser(userver::storages::postgres::ClusterPtr pg_cluster, std::string_view username);

} // namespace api::v1::impl
