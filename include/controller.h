#pragma once

#include "boardvariant.h"
#include "display.h"
#include "pressresult.h"
#include "regularboard.h"
#include <algorithm>
#include <random>

namespace nsweeper {
class Controller {
  BoardVariant &board;

public:
  [[nodiscard]] Controller(BoardVariant &board);
  virtual ~Controller() = default;

  // Make move on board
  virtual void makeMove() = 0;

protected:
  [[nodiscard]] BoardVariant &getBoard();
};
} // namespace nsweeper
