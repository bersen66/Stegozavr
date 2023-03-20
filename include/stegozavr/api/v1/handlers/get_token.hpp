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

/**
 * @class Encode.
 *
 * @brief Обработка http-запроса на генерацию access-токена, используемого при работе с API.
 *
 * Вызывается userver-ом при обработке пути /v1/get_token с методом GET.
 * Перед тем как обработать запрос проверяет, что отправитель имеет нужные права.
 * Для этого осуществляется запрос к БД.
 *
 * Создается userver-ом неявно и в единственном экземпляре.
 */
class GetToken final : public ::userver::server::handlers::HttpHandlerJsonBase
{
public:
  /// Имя обработчика в конфиге и системе компонентов.
  static constexpr std::string_view kName = "handler-get-token";

  /// @brief Остальные, не переопределенные методы - из HttpHandlerJsonBase.
  using ::userver::server::handlers::HttpHandlerJsonBase::HttpHandlerJsonBase;

  /**
   * Конструктор.
   *
   * @param config - конфигурация компонента. Генерируется из configs/static_config.yaml.
   * @param context - компонент, позволяющий воспользоваться другими компонентами userver-а.
   */
  GetToken(const ::userver::components::ComponentConfig& config,
           const ::userver::components::ComponentContext& context);

  /**
   * @brief Тело обработчика.
   *
   * Именно здесь реализуется вся логика, связанная с обслуживанием пользовательского запроса.
   *
   * @param request - Объектное представление http-запроса.
   * @param request_json - Десериализованное представление тела запроса в формате json.
   * @param context - Хранит специфичную для запроса информацию.
   *
   * @return userver::formats::json::Value - результат работы обработчика.
   * Сгенерированый access-токен.
   *
   * Токен будет возвращен пользователю, только при условии его уникальности(токена)
   */
  ::userver::formats::json::Value HandleRequestJsonThrow(
      const ::userver::server::http::HttpRequest& request, const ::userver::formats::json::Value& request_json,
      ::userver::server::request::RequestContext& context) const override;

private:
  /**
   * @brief Генерация уникального токена.
   *
   * @param transaction - Транзакция, в течение которой осуществляется создание токена.
   * @return Уникальный токен.
   */
  std::string GenerateToken(::userver::storages::postgres::Transaction& transaction) const;

  /**
   * @brief Проверка токена на уникальность.
   *
   * @param transaction - Транзакция, в течение которой осуществляется создание токена.
   * @param token - Токен, который будет проверяться на уникальность.
   *
   * @return Результат проверки. (true/false)
   */
  bool IsUniqueToken(::userver::storages::postgres::Transaction& transaction, ::std::string_view token) const;

  /**
   * @brief Добавление токена в БД.
   *
   * @param transaction - Транзакция, в течение которой осуществляется создание токена.
   * @param token - Токен, который будет вноситься в БД.
   *
   * @return Количество строк, измененных в рамках операции. Если их кол-во != 0, то токен был добавлен.
   */
  size_t InsertToken(::userver::storages::postgres::Transaction& transaction, ::std::string_view token) const;

  /**
   * @brief Получить id пользовтаеля.
   *
   * Проверка на существование не осуществляется.
   *
   * @param transaction - Транзакция, в течение которой осуществляется создание токена.
   * @param username - Имя пользователя, для которого будет искаться id.
   * @return id пользователя
   */
  std::int64_t UserId(::userver::storages::postgres::Transaction& transaction, ::std::string_view username) const;


  /**
   * @brief Получить id токена.
   *
   * Проверка на существование не осуществляется.
   *
   * @param transaction - Транзакция, в течение которой осуществляется создание токена.
   * @param username - Токен, для которого будет искаться id.
   * @return id токена
   */
  std::int64_t TokenId(::userver::storages::postgres::Transaction& transaction, ::std::string_view token) const;

private:
  /// Умный указатель на userver::storages::postgres::Cluster
  userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace api::v1::handlers