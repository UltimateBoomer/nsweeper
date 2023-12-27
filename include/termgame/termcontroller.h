#pragma once

#include "board/pressresult.h"
#include "controller.h"
#include <algorithm>
#include <iostream>
#include <random>

namespace nsweeper {
class TermController : public Controller {
  std::istream &is;
  std::ostream &os;

public:
  [[nodiscard]] TermController(Board *board, std::istream &is,
                               std::ostream &os);

  void makeMove() override;
};
} // namespace nsweeper
