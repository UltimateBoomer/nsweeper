#include "regularboard.h"
#include <algorithm>

namespace nsweeper {
RegularBoard::RegularBoard(size_t width, size_t height)
    : Board{width * height}, dim{width, height} {
  // Connect adjacent cells
  for (size_t y = 0; y < getHeight(); ++y) {
    for (size_t x = 0; x < getWidth(); ++x) {
      auto &cell = getCell(x, y);
      for (size_t ny = std::max(y, static_cast<size_t>(1)) - 1;
           ny <= std::min(y, getHeight() - 2) + 1; ++ny) {
        for (size_t nx = std::max(x, static_cast<size_t>(1)) - 1;
             nx <= std::min(x, getWidth() - 2) + 1; ++nx) {
          cell.addAdjacentCell(getCell(nx, ny));
        }
      }
    }
  }
}

size_t RegularBoard::getWidth() const { return dim.x; }

size_t RegularBoard::getHeight() const { return dim.y; }

size_t RegularBoard::toIndex(Vec2 pos) const {
  return pos.y * getWidth() + pos.x;
}
} // namespace nsweeper
