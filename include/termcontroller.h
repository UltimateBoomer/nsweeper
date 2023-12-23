#pragma once

#include "controller.h"
#include "pressresult.h"
#include <algorithm>
#include <iostream>
#include <random>

namespace nsweeper {
class TermController : public Controller {
  std::istream &is;
  std::ostream &os;

public:
  TermController(BoardVariant &board, std::istream &is, std::ostream &os);

  PressResult makeMove() override;
};
} // namespace nsweeper
