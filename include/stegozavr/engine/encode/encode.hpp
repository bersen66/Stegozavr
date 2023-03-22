#pragma once

#include <string>
#include <vector>


/// @ingroup engine


namespace stegozavr::engine::blocking
{
/**
 * @fn Encode
 * @brief Сокрытие текста сообщения в изображении.
 * @param image_data - изображение в бинарном формате
 * @param text_to_hide - текст, для сокрытия
 * @return новое изображение в котором скрыт текст
 */

std::string Encode(std::string_view image_data, std::string_view text_to_hide);

} // namespace stegozavr::engine::blocking