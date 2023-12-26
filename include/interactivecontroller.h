#pragma once

#include "controller.h"
#include "vec.h"
#include <ncpp/NotCurses.hh>
#include <ncpp/Plane.hh>

namespace nsweeper {
class InteractiveController : public Controller {
  Vec2 &cursor;
  ncpp::NotCurses &nc;

public:
  [[nodiscard]] InteractiveController(BoardVariant &board, Vec2 &cursor,
                                      ncpp::NotCurses &nc);

  void makeMove() override;
};
} // namespace nsweeper
