#pragma once

#include "board.h"
#include "vec.h"

namespace nsweeper {
// 2D board
class RegularBoard : public Board<RegularBoard, Vec2> {
  Vec2 dim;

public:
  [[nodiscard]] RegularBoard(int width, int height);

  [[nodiscard]] int getWidth() const;
  [[nodiscard]] int getHeight() const;

  [[nodiscard]] size_t toIndex(Vec2 pos) const;
};
} // namespace nsweeper
