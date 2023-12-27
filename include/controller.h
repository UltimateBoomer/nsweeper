#pragma once

#include "display.h"
#include "pressresult.h"
#include "regularboard.h"
#include <algorithm>
#include <random>

namespace nsweeper {
class Controller {
  Board *board;

public:
  [[nodiscard]] Controller(Board *board);
  virtual ~Controller() = default;

  // Make move on board
  virtual void makeMove() = 0;

protected:
  [[nodiscard]] Board *getBoard();
};
} // namespace nsweeper
