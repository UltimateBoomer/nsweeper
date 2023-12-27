#pragma once

namespace nsweeper {
class RegularBoard;

struct BoardVisitor {
  virtual void operator()(RegularBoard &board) = 0;
};

struct ConstBoardVisitor {
  virtual void operator()(const RegularBoard &board) = 0;
};
} // namespace nsweeper
