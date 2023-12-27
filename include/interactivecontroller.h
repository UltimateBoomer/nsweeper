#pragma once

#include "controller.h"
#include "vec.h"
#include <ncpp/NotCurses.hh>
#include <ncpp/Plane.hh>

namespace nsweeper {
class InteractiveController : public Controller {
  size_t &cursor;
  ncpp::NotCurses &nc;

public:
  [[nodiscard]] InteractiveController(Board *board, size_t &cursor,
                                      ncpp::NotCurses &nc);

  void makeMove() override;
};
} // namespace nsweeper
