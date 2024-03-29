#include <in_image_hider/hider_png.h>

/**
 * define STEG_ENABLE_DEBUG macro, if you want to see debug information.
 */

namespace hider_png
{
namespace hider_png_internal
{

#define OUT_FILENAME "output.png"
#define SIGN_PX_CNT 0x4
#define DATA_TYPE_BITS_CNT 0x1

// Filling signature bits with 0x7, 0x1, 0x3, 0x5, ...
const auto signature_bits_boost = []() -> bdb<uint8_t> {
  bdb<uint8_t> bits(SIGN_PX_CNT * 3);

  uint8_t bit = 0x7;
  for (uint64_t i = 0; i < SIGN_PX_CNT; ++i)
  {
    bits <<= 0x3;
    bits |= bdb<uint8_t>(SIGN_PX_CNT * 3, bit);
    bit = (bit + 2) % 8;
  }

  return bits;
}();

// Functions

const uint64_t get_dss(const png::image<png::rgb_pixel>& image)
{
  return ceil(std::log2(image.get_width() * image.get_height() * 3 - SIGN_PX_CNT * 3 - DATA_TYPE_BITS_CNT));
}

void encode(png::image<png::rgb_pixel>& image, const bdb<uint8_t>& bits)
{
  const uint64_t bits_size = bits.size();

  uint64_t x = 0, y = 0;
  uint64_t bits_cnt = bits_size;
  uint64_t cur_bit_i = bits_size - 1;

  while (bits_cnt)
  {
    png::byte rgb[] = {image[y][x].red, image[y][x].green, image[y][x].blue};

    for (uint8_t k = 0; (k < 3) && bits_cnt; ++k, --bits_cnt)
    {
      if (bits[cur_bit_i--] == 0)
      {
        rgb[k] &= 0b11111110;
      }
      else
      {
        rgb[k] |= 0b00000001;
      }
    }

    image[y][x] = png::rgb_pixel(rgb[0], rgb[1], rgb[2]);

    if (++x == image.get_width())
    {
      x = 0;
      ++y;
    }
  }

  //image.write(OUT_FILENAME);
}


} // namespace hider_png_internal

void encode(const std::string& filename, const std::vector<uint8_t>& data, const uint8_t& data_type)
{
  png::image<png::rgb_pixel> image(filename);

  const uint64_t data_bits_cnt = data.size() * 8;
  const uint64_t dss = hider_png_internal::get_dss(image);
  const uint64_t bits_cnt = SIGN_PX_CNT * 3 + DATA_TYPE_BITS_CNT + dss + data_bits_cnt;

  const bdb<uint8_t>& signature_bits = hider_png_internal::signature_bits_boost;
  const bdb<uint8_t> type_bits(DATA_TYPE_BITS_CNT, data_type);
  const bdb<uint8_t> data_size_bits(dss, data_bits_cnt);

  const auto bits = [&signature_bits, &type_bits, &dss, &data_size_bits, &data_bits_cnt, &bits_cnt,
                     &data]() -> bdb<uint8_t> {
    bdb<uint8_t> bits(bits_cnt);

    for (int64_t i = SIGN_PX_CNT * 3 - 1; i >= 0; --i)
    {
      bits <<= 1;
      bits |= bdb<uint8_t>(bits_cnt, signature_bits[i]);
    }

    for (int64_t i = DATA_TYPE_BITS_CNT - 1; i >= 0; --i)
    {
      bits <<= 1;
      bits |= bdb<uint8_t>(bits_cnt, type_bits[i]);
    }

    for (int64_t i = dss - 1; i >= 0; --i)
    {
      bits <<= 1;
      bits |= bdb<uint8_t>(bits_cnt, data_size_bits[i]);
    }

    for (int64_t i = 0; i < data.size(); ++i)
    {
      for (int64_t j = 0; j < 8; ++j)
      {
        bits <<= 1;
        bits |= bdb<uint8_t>(bits_cnt, (data[i] & (0b10000000 >> j)) >> (7 - j));
      }
    }

    return bits;
  }();

#ifdef STEG_ENABLE_DEBUG
  std::cout << "RECEIVED BITS FOR ENCODE - " << bits << "\n\n";

  std::cout << "SIGNATURE SIZE - " << SIGN_PX_CNT * 3 << " bit.\n";
  std::cout << "TYPE SIZE - " << DATA_TYPE_BITS_CNT << " bit.\n";
  std::cout << "DATA SIZE - " << dss << " bit.\n";
  std::cout << "DATA - " << data_bits_cnt << " bit.\n\n";

  std::cout << "TOTAL BITS - " << bits_cnt << " bit.\n\n";

  std::cout << "PIXELS USED - " << ceil(bits_cnt / 3) << " px.\n";
#endif // STEG_ENABLE_DEBUG
  hider_png_internal::encode(image, bits);
}

std::vector<uint8_t> decode(const std::string& filename)
{
  png::image<png::rgb_pixel> image(filename);

  // GETTING SIGNATURE
  const uint64_t sign_bits_cnt = SIGN_PX_CNT * 3;

  const bdb<uint8_t>& signature_bits = hider_png_internal::signature_bits_boost;

  bdb<uint8_t> signature_bits_received(sign_bits_cnt);

  uint64_t x = 0, y = 0;
  uint64_t sign_bit_i = sign_bits_cnt;

  while (sign_bit_i)
  {
    for (uint8_t i = 0; (i < 3) && sign_bit_i; ++i, --sign_bit_i)
    {
      signature_bits_received <<= 1;

      if (i == 0)
      {
        signature_bits_received |= bdb<uint8_t>(sign_bits_cnt, image[y][x].red & 0b00000001);
      }
      else if (i == 1)
      {
        signature_bits_received |= bdb<uint8_t>(sign_bits_cnt, image[y][x].green & 0b00000001);
      }
      else if (i == 2)
      {
        signature_bits_received |= bdb<uint8_t>(sign_bits_cnt, image[y][x].blue & 0b00000001);
      }
    }

    if (++x == image.get_width())
    {
      x = 0;
      ++y;
    }
  }

  if (signature_bits_received != signature_bits)
    exit(1);
#ifdef STEG_ENABLE_DEBUG
  std::cout << "\nSIGNATURE CORRECT - " << signature_bits_received << "\n";
#endif // STEG_ENABLE_DEBUG
       //

  typedef enum _color_i
  {
    RED = 0,
    GREEN,
    BLUE
  } _color_i; // last color identifier | 0 - red, 1 - green, 2 - blue
  _color_i color_i = BLUE;

  // GETTING TYPE
  bdb<uint8_t> type_bits_received(DATA_TYPE_BITS_CNT);

  uint64_t type_bit_i = DATA_TYPE_BITS_CNT;

  while (type_bit_i)
  {
    for (uint8_t i = 0; (i < 3) && type_bit_i; ++i, --type_bit_i)
    {
      type_bits_received <<= 1;

      if (color_i == BLUE)
      {
        type_bits_received |= bdb<uint8_t>(DATA_TYPE_BITS_CNT, image[y][x].red & 0b00000001);
        color_i = RED;
      }
      else if (color_i == RED)
      {
        type_bits_received |= bdb<uint8_t>(DATA_TYPE_BITS_CNT, image[y][x].green & 0b00000001);
        color_i = GREEN;
      }
      else if (color_i == GREEN)
      {
        type_bits_received |= bdb<uint8_t>(DATA_TYPE_BITS_CNT, image[y][x].blue & 0b00000001);
        color_i = BLUE;

        if (++x == image.get_width())
        {
          x = 0;
          ++y;
        }
      }
    }
  }
#ifdef STEG_ENABLE_DEBUG
  std::cout << "TYPE - " << type_bits_received << "\n";
#endif // STEG_ENABLE_DEBUG
       //

  // GETTING DATA SIZE
  const uint64_t dss = hider_png_internal::get_dss(image);

  bdb<uint8_t> data_size(dss);

  uint64_t dss_i = dss;

  while (dss_i)
  {
    for (uint8_t i = 0; (i < 3) && dss_i; ++i, --dss_i)
    {
      data_size <<= 1;

      if (color_i == BLUE)
      {
        data_size |= bdb<uint8_t>(dss, image[y][x].red & 0b00000001);
        color_i = RED;
      }
      else if (color_i == RED)
      {
        data_size |= bdb<uint8_t>(dss, image[y][x].green & 0b00000001);
        color_i = GREEN;
      }
      else if (color_i == GREEN)
      {
        data_size |= bdb<uint8_t>(dss, image[y][x].blue & 0b00000001);
        color_i = BLUE;

        if (++x == image.get_width())
        {
          x = 0;
          ++y;
        }
      }
    }
  }
#ifdef STEG_ENABLE_DEBUG
  std::cout << "DSS - " << dss << " | DATA SIZE - " << data_size << "\n";
#endif // STEG_ENABLE_DEBUG

  // GETTING DATA SIZE
  const uint64_t data_size_u64 = data_size.to_ulong();

  bdb<uint8_t> data(data_size_u64);

  uint64_t data_i = data_size_u64;

  while (data_i)
  {
    for (uint8_t i = 0; (i < 3) && data_i; ++i, --data_i)
    {
      data <<= 1;

      if (color_i == BLUE)
      {
        data |= bdb<uint8_t>(data_size_u64, image[y][x].red & 0b00000001);
        color_i = RED;
      }
      else if (color_i == RED)
      {
        data |= bdb<uint8_t>(data_size_u64, image[y][x].green & 0b00000001);
        color_i = GREEN;
      }
      else if (color_i == GREEN)
      {
        data |= bdb<uint8_t>(data_size_u64, image[y][x].blue & 0b00000001);
        color_i = BLUE;

        if (++x == image.get_width())
        {
          x = 0;
          ++y;
        }
      }
    }
  }
#ifdef STEG_ENABLE_DEBUG
  std::cout << "DATA - " << data << "\n";
#endif // STEG_ENABLE_DEBUG

  const std::vector<uint8_t> data_bytes = [&data]() -> std::vector<uint8_t> {
    std::vector<uint8_t> data_v;

    bdb<uint8_t> byte_bs(8);

    uint8_t byte = 0;
    for (int64_t i = data.size() - 1; i >= 0; --i)
    {
      byte_bs <<= 1;
      byte_bs |= bdb<uint8_t>(8, data[i]);

      if (i % 8 == 0)
      {
        data_v.push_back(byte_bs.to_ulong());
      }
    }

    return data_v;
  }();

  return data_bytes;
}

namespace custom
{

namespace impl
{

void run_lsb(png::image<png::rgb_pixel>& container, std::string_view text_to_hide) {
  constexpr int data_type = 0;
  const uint64_t data_bits_cnt = text_to_hide.size() * 8;
  const uint64_t dss = hider_png_internal::get_dss(container);
  const uint64_t bits_cnt = SIGN_PX_CNT * 3 + DATA_TYPE_BITS_CNT + dss + data_bits_cnt;

  const bdb<uint8_t>& signature_bits = hider_png_internal::signature_bits_boost;
  const bdb<uint8_t> type_bits(DATA_TYPE_BITS_CNT, data_type);
  const bdb<uint8_t> data_size_bits(dss, data_bits_cnt);

  const auto bits = [&signature_bits, &type_bits, &dss, &data_size_bits, &data_bits_cnt, &bits_cnt,
                     &text_to_hide]() -> bdb<uint8_t> {
    bdb<uint8_t> bits(bits_cnt);

    for (int64_t i = SIGN_PX_CNT * 3 - 1; i >= 0; --i)
    {
      bits <<= 1;
      bits |= bdb<uint8_t>(bits_cnt, signature_bits[i]);
    }

    for (int64_t i = DATA_TYPE_BITS_CNT - 1; i >= 0; --i)
    {
      bits <<= 1;
      bits |= bdb<uint8_t>(bits_cnt, type_bits[i]);
    }

    for (int64_t i = dss - 1; i >= 0; --i)
    {
      bits <<= 1;
      bits |= bdb<uint8_t>(bits_cnt, data_size_bits[i]);
    }

    for (int64_t i = 0; i < text_to_hide.size(); ++i)
    {
      for (int64_t j = 0; j < 8; ++j)
      {
        bits <<= 1;
        bits |= bdb<uint8_t>(bits_cnt, (text_to_hide[i] & (0b10000000 >> j)) >> (7 - j));
      }
    }

    return bits;
  }();

  hider_png_internal::encode(container, bits);
}

png::image<png::rgb_pixel> encode(std::istream& container, std::string_view text_to_hide) {
  png::image<png::rgb_pixel> src_image(container);
  run_lsb(src_image, text_to_hide);
  return src_image;
}

} // namespace impl


void encode(std::istream& container, std::string_view text_to_hide, std::ostream& out) {
  auto encoded_image = impl::encode(container, text_to_hide);
  encoded_image.write_stream(out);
}

std::string decode(std::istream& container)
{
  png::image<png::rgb_pixel> image(container);

  // GETTING SIGNATURE
  const uint64_t sign_bits_cnt = SIGN_PX_CNT * 3;

  const bdb<uint8_t>& signature_bits = hider_png_internal::signature_bits_boost;

  bdb<uint8_t> signature_bits_received(sign_bits_cnt);

  uint64_t x = 0, y = 0;
  uint64_t sign_bit_i = sign_bits_cnt;

  while (sign_bit_i)
  {
    for (uint8_t i = 0; (i < 3) && sign_bit_i; ++i, --sign_bit_i)
    {
      signature_bits_received <<= 1;

      if (i == 0)
      {
        signature_bits_received |= bdb<uint8_t>(sign_bits_cnt, image[y][x].red & 0b00000001);
      }
      else if (i == 1)
      {
        signature_bits_received |= bdb<uint8_t>(sign_bits_cnt, image[y][x].green & 0b00000001);
      }
      else if (i == 2)
      {
        signature_bits_received |= bdb<uint8_t>(sign_bits_cnt, image[y][x].blue & 0b00000001);
      }
    }

    if (++x == image.get_width())
    {
      x = 0;
      ++y;
    }
  }

  if (signature_bits_received != signature_bits)
    exit(1);
#ifdef STEG_ENABLE_DEBUG
  std::cout << "\nSIGNATURE CORRECT - " << signature_bits_received << "\n";
#endif // STEG_ENABLE_DEBUG
       //

  typedef enum _color_i
  {
    RED = 0,
    GREEN,
    BLUE
  } _color_i; // last color identifier | 0 - red, 1 - green, 2 - blue
  _color_i color_i = BLUE;

  // GETTING TYPE
  bdb<uint8_t> type_bits_received(DATA_TYPE_BITS_CNT);

  uint64_t type_bit_i = DATA_TYPE_BITS_CNT;

  while (type_bit_i)
  {
    for (uint8_t i = 0; (i < 3) && type_bit_i; ++i, --type_bit_i)
    {
      type_bits_received <<= 1;

      if (color_i == BLUE)
      {
        type_bits_received |= bdb<uint8_t>(DATA_TYPE_BITS_CNT, image[y][x].red & 0b00000001);
        color_i = RED;
      }
      else if (color_i == RED)
      {
        type_bits_received |= bdb<uint8_t>(DATA_TYPE_BITS_CNT, image[y][x].green & 0b00000001);
        color_i = GREEN;
      }
      else if (color_i == GREEN)
      {
        type_bits_received |= bdb<uint8_t>(DATA_TYPE_BITS_CNT, image[y][x].blue & 0b00000001);
        color_i = BLUE;

        if (++x == image.get_width())
        {
          x = 0;
          ++y;
        }
      }
    }
  }
#ifdef STEG_ENABLE_DEBUG
  std::cout << "TYPE - " << type_bits_received << "\n";
#endif // STEG_ENABLE_DEBUG
       //

  // GETTING DATA SIZE
  const uint64_t dss = hider_png_internal::get_dss(image);

  bdb<uint8_t> data_size(dss);

  uint64_t dss_i = dss;

  while (dss_i)
  {
    for (uint8_t i = 0; (i < 3) && dss_i; ++i, --dss_i)
    {
      data_size <<= 1;

      if (color_i == BLUE)
      {
        data_size |= bdb<uint8_t>(dss, image[y][x].red & 0b00000001);
        color_i = RED;
      }
      else if (color_i == RED)
      {
        data_size |= bdb<uint8_t>(dss, image[y][x].green & 0b00000001);
        color_i = GREEN;
      }
      else if (color_i == GREEN)
      {
        data_size |= bdb<uint8_t>(dss, image[y][x].blue & 0b00000001);
        color_i = BLUE;

        if (++x == image.get_width())
        {
          x = 0;
          ++y;
        }
      }
    }
  }
#ifdef STEG_ENABLE_DEBUG
  std::cout << "DSS - " << dss << " | DATA SIZE - " << data_size << "\n";
#endif // STEG_ENABLE_DEBUG

  // GETTING DATA SIZE
  const uint64_t data_size_u64 = data_size.to_ulong();

  bdb<uint8_t> data(data_size_u64);

  uint64_t data_i = data_size_u64;

  while (data_i)
  {
    for (uint8_t i = 0; (i < 3) && data_i; ++i, --data_i)
    {
      data <<= 1;

      if (color_i == BLUE)
      {
        data |= bdb<uint8_t>(data_size_u64, image[y][x].red & 0b00000001);
        color_i = RED;
      }
      else if (color_i == RED)
      {
        data |= bdb<uint8_t>(data_size_u64, image[y][x].green & 0b00000001);
        color_i = GREEN;
      }
      else if (color_i == GREEN)
      {
        data |= bdb<uint8_t>(data_size_u64, image[y][x].blue & 0b00000001);
        color_i = BLUE;

        if (++x == image.get_width())
        {
          x = 0;
          ++y;
        }
      }
    }
  }
#ifdef STEG_ENABLE_DEBUG
  std::cout << "DATA - " << data << "\n";
#endif // STEG_ENABLE_DEBUG

  const std::vector<uint8_t> data_bytes = [&data]() -> std::vector<uint8_t> {
    std::vector<uint8_t> data_v;

    bdb<uint8_t> byte_bs(8);

    uint8_t byte = 0;
    for (int64_t i = data.size() - 1; i >= 0; --i)
    {
      byte_bs <<= 1;
      byte_bs |= bdb<uint8_t>(8, data[i]);

      if (i % 8 == 0)
      {
        data_v.push_back(byte_bs.to_ulong());
      }
    }

    return data_v;
  }();

  return {data_bytes.begin(), data_bytes.end()};
}


} // namespace custom

} // namespace hider_png
