#pragma once
#include <istream>
#include <string>

/// @ingroup engine

namespace stegozavr::engine::utils::blocking
{
/**
 * @fn ContentOf
 * @param input
 * @return
 */
std::string ContentOf(std::istream& input);

} // namespace stegozavr::engine::utils::blocking