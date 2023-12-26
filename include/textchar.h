#pragma once

#include <array>
#include <string>

namespace nsweeper {
constexpr std::string emptyChar = "・";
constexpr std::array<std::string, 10> numDisplayTable{
    "＋", "１", "２", "３", "４", "５", "６", "７", "８", "９"};
constexpr std::string flagChar = "🚩";
constexpr std::string mineChar = "＊";
} // namespace nsweeper
