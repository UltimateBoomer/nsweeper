#pragma once

#include "board.h"
#include "vec.h"

namespace nsweeper {
// 2D board
class RegularBoard : public Board<RegularBoard, Vec2> {
  Vec2 dim;

public:
  RegularBoard(size_t width, size_t height);

  size_t getWidth() const;
  size_t getHeight() const;

  size_t toIndex(Vec2 pos) const;
};

/* template <typename... PosArgs> */
/* size_t RegularBoard::toIndex(PosArgs &&...pos) const { */
/*   Vec2 p{std::forward<PosArgs>(pos)...}; */
/*   return p.y * size.x + p.x; */
/* } */

} // namespace nsweeper
