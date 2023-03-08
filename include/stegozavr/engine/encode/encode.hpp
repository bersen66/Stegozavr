#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace stegozavr::engine::blocking
{
std::string Encode(std::string_view image_data, std::string_view text_to_hide);

} // namespace stegozavr::engine::blocking