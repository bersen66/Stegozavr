#pragma once

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace api::v1::handlers::queries
{

const ::userver::storages::postgres::Query kInsertUser = {
    "INSERT INTO users (username) VALUES ($1)", ::userver::storages::postgres::Query::Name("stegozavr_insert_user")};

const ::userver::storages::postgres::Query kInsertToken = {
    "INSERT INTO tokens (token_val, creation_date) VALUES ($1, $2)",
    ::userver::storages::postgres::Query::Name("stegozavr_insert_token")};

const ::userver::storages::postgres::Query kHasUser = {
    "SELECT COUNT(1) FROM users WHERE username=$1 LIMIT 1",
    ::userver::storages::postgres::Query::Name("stegozavr_contains_user")};

const ::userver::storages::postgres::Query kHasToken = {
    "SELECT COUNT(1) FROM tokens WHERE token_val=$1 LIMIT 1",
    ::userver::storages::postgres::Query::Name("stegozavr_contains_token")};

const ::userver::storages::postgres::Query kUserCanUseThisToken = {
    "SELECT COUNT(1) FROM user_to_token_kv WHERE username=$1 and token_val=$2 and (NOW()::date - creation_date::date) < 14",
    ::userver::storages::postgres::Query::Name("stegozavr_contains_token")};

} // namespace api::v1::handlers::queries