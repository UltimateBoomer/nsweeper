#pragma once

#include "boardvariant.h"
#include "controller.h"
#include "display.h"
#include "game.h"
#include <memory>

namespace nsweeper {
class TermGame : public Game {
  BoardVariant board;
  std::unique_ptr<Display> display;
  std::unique_ptr<Controller> controller;
  std::istream &is;
  std::ostream &os;

public:
  [[nodiscard]] TermGame(std::istream &is, std::ostream &os);

  void run();

private:
  void setup();
  void runLoop();
};

} // namespace nsweeper
