#include <userver/clients/dns/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include <stegozavr/api/handlers.hpp>

int main(int argc, char** argv)
{
  LOG_INFO() << "STEGOZAVR STARTED";
  // clang-format off
  const auto server_components =
      userver::components::MinimalServerComponentList()
        .Append<userver::components::Postgres>("stegozavr-db")
        .Append<userver::clients::dns::Component>()
        .Append<userver::components::TestsuiteSupport>()
        .Append<api::v1::handlers::Decode>()
        .Append<api::v1::handlers::Encode>()
        .Append<api::v1::handlers::RegisterUser>()
        .Append<api::v1::handlers::GetToken>()
      ;
  // clang-format on
  LOG_INFO() << "COMPONENTS COMBINED";
  return userver::utils::DaemonMain(argc, argv, server_components);
}
