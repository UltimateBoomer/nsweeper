#pragma once

#include "board/board.h"

namespace nsweeper {
// Abstract board display that can handle multiple board variants
class Display {
  const Board *board;

public:
  [[nodiscard]] Display(const Board *board);
  virtual ~Display() = default;

  // Update display
  virtual void notify() = 0;

protected:
  [[nodiscard]] const Board *getBoard() const;
};
} // namespace nsweeper
