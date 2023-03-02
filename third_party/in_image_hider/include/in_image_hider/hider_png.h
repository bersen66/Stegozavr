#pragma once

#include <algorithm>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <iostream>
#include <png++/png.hpp>
#include <vector>

template <typename T> using bdb = boost::dynamic_bitset<T>;

namespace hider_png
{

void encode(const std::string& filename, const std::vector<uint8_t>& data, const uint8_t& data_type);
std::vector<uint8_t> decode(const std::string& filename);

namespace custom
{
void encode(std::istream& content, const std::string& path_to_output, const std::vector<uint8_t>& data);
} // namespace custom

} // namespace hider_png