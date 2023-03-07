#include <stegozavr/engine/encode/encode.hpp>
#include <stegozavr/engine/utils/files.hpp>
#include <userver/fs/blocking/temp_file.hpp>

#include <in_image_hider/hider_png.h>


namespace stegozavr::engine::blocking
{

void Encode(std::string& file_content, const std::vector<uint8_t>& text_to_hide)
{
  namespace fs = userver::fs::blocking;
  auto temp_file = fs::TempFile::Create();

  std::fstream src(temp_file.GetPath(), std::ios::binary);
  src.write(file_content.data(), file_content.size());
  src.close();

  //::hider_png::custom::encode(temp_file.GetPath(), {file_content.begin(), file_content.end()}, 0);




//  std::stringstream content(file_content, std::ios::binary);
//
//  //::hider_png::custom::encode(content, temp_file.GetPath(), text_to_hide);
//
//  std::fstream res_content(temp_file.GetPath(), std::ios::binary);
//
//  file_content = ::stegozavr::engine::utils::blocking::ContentOf(res_content);


}

} // namespace stegozavr::engine::blocking