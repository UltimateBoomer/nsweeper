#pragma once

#include "boardtemplate.h"
#include "vec.h"

namespace nsweeper {
// Standard 2D board
class RegularBoard : public BoardTemplate<RegularBoard, Vec2> {
  Vec2 dim;

public:
  [[nodiscard]] RegularBoard(auto &&...posArgs)
      : BoardTemplate<RegularBoard, Vec2>{std::apply(std::multiplies<size_t>(),
                                                     Vec2{posArgs...})},
        dim{std::forward<decltype(posArgs)>(posArgs)...} {
    connectAdjacent();
  }

  Vec2 getDim() const;

  Vec2 fromIndex(size_t i) const;

  [[nodiscard]] size_t toIndex(auto &&...posArgs) const {
    auto [x, y] = Vec2{posArgs...};
    auto width = getDim().first;
    return static_cast<size_t>(y * width + x);
  }

private:
  // Connect adjacent cells
  void connectAdjacent();
};
} // namespace nsweeper
