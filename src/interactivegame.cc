#include "interactivegame.h"
#include "gamesetting.h"
#include "interactivecontroller.h"
#include "interactivedisplay.h"
#include "regularboard.h"
#include <memory>
#include <ncpp/NotCurses.hh>

namespace nsweeper {
void distribute(Board *board, size_t n, unsigned int seed) {
  std::mt19937_64 rng{seed};
  size_t size = board->size();
  std::vector<size_t> nums(size);
  std::iota(nums.begin(), nums.end(), 0);
  std::shuffle(nums.begin(), nums.end(), rng);
  board->clear();
  size_t i = 0;
  for (auto it = nums.begin(); i < n && it != nums.end(); ++i, ++it) {
    board->setMine(true, *it);
  }
}

InteractiveGame::InteractiveGame(GameSetting s, ncpp::NotCurses &nc)
    : board{std::make_unique<RegularBoard>(s.dim)}, cursor{0}, nc{nc},
      display{board.get(), cursor, *nc.get_stdplane()},
      controller{board.get(), cursor, nc} {
  auto seed = std::random_device{}();
  distribute(board.get(), s.numMines, seed);
  runLoop();
}

void InteractiveGame::runLoop() {
  while (true) {
    display.notify();
    nc.render();
    controller.makeMove();

    if (!std::holds_alternative<std::monostate>(board->getState())) {
      break;
    }
  }
  display.notify();
  nc.render();
  while (nc.get(true) != 'q')
    ;
}
} // namespace nsweeper
