#include <stegozavr/api/handlers.hpp>
#include <userver/utils/daemon_run.hpp>
#include <userver/components/minimal_server_component_list.hpp>


int main(int argc, char** argv)
{
  // clang-format off
  const auto server_components =
      userver::components::MinimalServerComponentList()
        .Append<api::v1::handlers::RegisterUser>()
        .Append<api::v1::handlers::Decode>()
        .Append<api::v1::handlers::Encode>();
  // clang-format on
  return userver::utils::DaemonMain(argc, argv, server_components);
}
