#pragma once

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace api::v1::handlers::queries
{

const ::userver::storages::postgres::Query kInsertUser = {
    "INSERT INTO users (username) VALUES ($1)", ::userver::storages::postgres::Query::Name("stegozavr_insert_user")};


} // namespace api::v1::handlers::queries