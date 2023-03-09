#pragma once

#include <string>
#include <string_view>

namespace stegozavr::engine::blocking {

std::string Decode(std::string_view image_data);

} // namespace stegozavr::engine::blocking