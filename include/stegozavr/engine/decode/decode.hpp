#pragma once

#include <string>
#include <string_view>

namespace stegozavr::engine::blocking {


/**
 * @param image_data - Изображение в бинарном виде.
 * @return Текст сообщения
 */
std::string Decode(std::string_view image_data);

} // namespace stegozavr::engine::blocking