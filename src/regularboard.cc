#include "regularboard.h"
#include <algorithm>

namespace nsweeper {
RegularBoard::RegularBoard(int width, int height)
    : Board{static_cast<size_t>(width * height)}, dim{width, height} {
  // Connect adjacent cells
  for (int y = 0; y < getHeight(); ++y) {
    for (int x = 0; x < getWidth(); ++x) {
      auto &cell = getCell(x, y);
      for (int ny = std::max(y, 1) - 1; ny <= std::min(y, getHeight() - 2) + 1;
           ++ny) {
        for (int nx = std::max(x, 1) - 1; nx <= std::min(x, getWidth() - 2) + 1;
             ++nx) {
          cell.addAdjacentCell(getCell(nx, ny));
        }
      }
    }
  }
}

int RegularBoard::getWidth() const { return dim.x; }

int RegularBoard::getHeight() const { return dim.y; }

size_t RegularBoard::toIndex(Vec2 pos) const {
  return static_cast<size_t>(pos.y * getWidth() + pos.x);
}
} // namespace nsweeper
