#include "regularboard.h"
#include <algorithm>

namespace nsweeper {
Vec2 RegularBoard::getDim() const { return dim; }

Vec2 RegularBoard::fromIndex(size_t i) const {
  auto width = getDim().first;
  return {i % width, i / width};
}

void RegularBoard::connectAdjacent() {
  auto [width, height] = getDim();
  for (int y = 0; y < width; ++y) {
    for (int x = 0; x < height; ++x) {
      auto &cell = getCell(x, y);
      for (int ny = std::max(y, 1) - 1; ny <= std::min(y, height - 2) + 1;
           ++ny) {
        for (int nx = std::max(x, 1) - 1; nx <= std::min(x, width - 2) + 1;
             ++nx) {
          cell.addAdjacentCell(getCell(nx, ny));
        }
      }
    }
  }
}
} // namespace nsweeper
