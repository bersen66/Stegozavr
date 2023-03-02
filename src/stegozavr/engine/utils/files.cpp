#include <stegozavr/engine/utils/files.hpp>

namespace stegozavr::engine::utils::blocking
{
std::string ContentOf(std::istream& input)
{
  return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

} // namespace stegozavr::engine::utils::blocking