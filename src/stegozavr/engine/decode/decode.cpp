#include <in_image_hider/hider_png.h>
#include <sstream>
#include <stegozavr/engine/decode/decode.hpp>

namespace stegozavr::engine::blocking
{

std::string Decode(std::string_view image_data)
{
  std::stringstream image(std::ios::binary | std::ios::in | std::ios::out);
  image.write(image_data.data(), image_data.size());

  return ::hider_png::custom::decode(image);
}

} // namespace stegozavr::engine::blocking