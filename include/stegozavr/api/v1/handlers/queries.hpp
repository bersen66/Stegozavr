#pragma once

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>



namespace api::v1::handlers::queries
{

/**
 * @brief Добавление пользователя в БД.
 * @param $1 - имя пользователя.
 */
const ::userver::storages::postgres::Query kInsertUser = {
    "INSERT INTO users (username) VALUES ($1)", ::userver::storages::postgres::Query::Name("stegozavr_insert_user")};


/**
 * @brief Добавление токена в БД.
 * @param $1 - значение токена.
 */
const ::userver::storages::postgres::Query kInsertToken = {
    "INSERT INTO tokens (token_val) VALUES ($1)", ::userver::storages::postgres::Query::Name("stegozavr_insert_token")};


/**
 * @brief Получение ID пользователя из БД.
 * @param $1 - имя пользователя.
 */
const ::userver::storages::postgres::Query kGetUserId = {
    "SELECT user_id FROM users WHERE username=$1", ::userver::storages::postgres::Query::Name("stegozavr_get_user_id")};

/**
 * @brief Получение ID токена из БД.
 * @param $1 - значение токена.
 */
const ::userver::storages::postgres::Query kGetTokenId = {
    "SELECT token_id FROM tokens WHERE token_val=$1",
    ::userver::storages::postgres::Query::Name("stegozavr_get_token_id")};


/**
 * @brief Создать пару {Пользователь, Токен} в базе данных.
 * @param $1 - id пользователя.
 * @param $2 - id токена.
 */
const ::userver::storages::postgres::Query kAttachTokenToUser = {
    "INSERT INTO user_to_token (user_id, token_id) VALUES ($1, $2)",
    ::userver::storages::postgres::Query::Name("stegozavr_attach_token_to_user")};


/**
 *  @brief Посчитать кол-во пользователей с таким username в БД.
 *  @param $1 - имя пользователя.
 */
const ::userver::storages::postgres::Query kHasUser = {
    "SELECT COUNT(1) FROM users WHERE username=$1 LIMIT 1",
    ::userver::storages::postgres::Query::Name("stegozavr_contains_user")};

/**
 *  @brief Посчитать кол-во токенов с таким значением в БД.
 *  @param $1 - значение токена.
 */
const ::userver::storages::postgres::Query kHasToken = {
    "SELECT COUNT(1) FROM tokens WHERE token_val=$1 LIMIT 1",
    ::userver::storages::postgres::Query::Name("stegozavr_contains_token")};


/**
 *  @brief Проверить права пользователя.
 *  @param $1 - Имя пользователя.
 *  @param $2 - Значение токена.
 */
const ::userver::storages::postgres::Query kUserCanUseThisToken = {
    "SELECT COUNT(1) FROM usertotokenkv WHERE username=$1 and token_val=$2 and (NOW()::date - creation_date::date)<14",
    ::userver::storages::postgres::Query::Name("stegozavr_check_permission")};

} // namespace api::v1::handlers::queries