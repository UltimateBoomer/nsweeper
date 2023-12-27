#pragma once

#include "controller.h"
#include "display.h"
#include "game.h"
#include "gamesetting.h"
#include "interactivecontroller.h"
#include "interactivedisplay.h"
#include <ncpp/NotCurses.hh>

namespace nsweeper {
class InteractiveGame : public Game {
  std::unique_ptr<Board> board;
  size_t cursor;
  ncpp::NotCurses &nc;
  InteractiveDisplay display;
  InteractiveController controller;
  /* std::unique_ptr<Controller> controller; */

public:
  [[nodiscard]] InteractiveGame(GameSetting s, ncpp::NotCurses &nc);

  /* virtual void run() override; */

private:
  void runLoop();
};
} // namespace nsweeper
