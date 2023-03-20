#pragma once
#include <istream>
#include <string>

///@file stegozavr/engine/files/files.hpp

namespace stegozavr::engine::utils::blocking
{

std::string ContentOf(std::istream& input);

} // namespace stegozavr::engine::utils::blocking