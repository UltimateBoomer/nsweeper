#pragma once

#include "vec.h"
#include <array>

namespace nsweeper {
struct GameSetting {
  Vec2 dim;
  size_t numMines;
};

constexpr std::array settings{
    std::pair{GameSetting{{9, 9}, 10}, "Beginner"},
    std::pair{GameSetting{{16, 16}, 40}, "Intermediate"},
    std::pair{GameSetting{{30, 16}, 99}, "Advanced"}};

} // namespace nsweeper
