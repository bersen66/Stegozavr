#pragma once

#include <userver/components/minimal_component_list.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/utils/daemon_run.hpp>

#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>


/// @ingroup handlers

namespace api::v1::handlers
{


/**
 * @class RegisterUser.
 *
 * @brief Обработка http-запроса на регистрацию пользователя.
 *
 * Вызывается userver-ом при обработке пути /v1/register  с методом POST.
 *
 * Инстанцируется userver-ом неявно и в единственном экземпляре.
 */
class RegisterUser final : public userver::server::handlers::HttpHandlerJsonBase
{
public:
  /// Имя обработчика в конфиге и системе компонентов.
  static constexpr std::string_view kName = "handler-register-user";

  /// @brief Остальные, не переопределенные методы - из HttpHandlerJsonBase.
  using userver::server::handlers::HttpHandlerJsonBase::HttpHandlerJsonBase;

  /**
   * Конструктор.
   *
   * @param config - конфигурация компонента. Генерируется из configs/static_config.yaml.
   * @param context - компонент, позволяющий воспользоваться другими компонентами userver-а.
   */
  RegisterUser(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

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
   * Регистрация пользователя или информирование о том, что он был зарегистрирован ранее.
   *
   */
  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request, const userver::formats::json::Value& request_json,
      userver::server::request::RequestContext& context) const override;

private:
  void InsertUser(std::string_view username) const;

private:
  /// Умный указатель на userver::storages::postgres::Cluster
  userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace api::v1::handlers