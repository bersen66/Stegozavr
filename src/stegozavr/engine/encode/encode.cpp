#include <stegozavr/engine/encode/encode.hpp>
#include <stegozavr/engine/utils/files.hpp>
#include <userver/fs/blocking/temp_file.hpp>

#include "userver/logging/log.hpp"
#include <in_image_hider/hider_png.h>

namespace stegozavr::engine::blocking
{

namespace impl
{
std::string Encode(std::istream& steg_container, std::string_view text_to_hide)
{
  std::stringstream output_image(std::ios::binary | std::ios::in | std::ios::out);

  hider_png::custom::encode(steg_container, text_to_hide, output_image);
  LOG_DEBUG() << "Buffer created";
  std::string result = output_image.str();
  return result;
}

} // namespace impl

std::string Encode(std::string_view image_data, std::string_view text_to_hide)
{
  std::stringstream image(std::ios::binary | std::ios::in | std::ios::out);
  image.write(image_data.data(), image_data.size());

  return  impl::Encode(image, text_to_hide);
}

} // namespace stegozavr::engine::blocking