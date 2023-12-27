#pragma once

#include "controller.h"
#include "display.h"
#include "game.h"
#include "gamesetting.h"
#include "termcontroller.h"
#include "termdisplay.h"
#include <memory>

namespace nsweeper {
class TermGame : public Game {
  std::unique_ptr<Board> board;
  TermDisplay display;
  TermController controller;
  std::istream &is;
  std::ostream &os;

public:
  [[nodiscard]] TermGame(GameSetting s, std::istream &is, std::ostream &os);

  void run();

private:
  void setup();
  void runLoop();
};

} // namespace nsweeper
