#pragma once

#include <string>
#include <string_view>

/// @ingroup engine

namespace stegozavr::engine::blocking {

/**
 * @brief Извлечение текста из изображения
 * @fn Decode
 * @param image_data - Изображение в бинарном виде.
 * @return Текст сообщения
 */
std::string Decode(std::string_view image_data);

} // namespace stegozavr::engine::blocking