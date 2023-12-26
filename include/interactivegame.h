#pragma once

#include "boardvariant.h"
#include "controller.h"
#include "display.h"
#include "game.h"
#include <ncpp/NotCurses.hh>

#define NCPP_EXCEPTIONS_PLEASE

namespace nsweeper {
class InteractiveGame : public Game {
  BoardVariant board;
  Vec2 cursor;
  ncpp::NotCurses &nc;
  std::unique_ptr<Display> display;
  std::unique_ptr<Controller> controller;

public:
  [[nodiscard]] InteractiveGame(ncpp::NotCurses &nc);

  /* virtual void run() override; */

private:
  void runLoop();
};
} // namespace nsweeper
