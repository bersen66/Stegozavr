#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace stegozavr::engine::blocking
{

void Encode(std::string& file_content, const std::vector<uint8_t>& text_to_hide);

} // namespace stegozavr::engine::blocking