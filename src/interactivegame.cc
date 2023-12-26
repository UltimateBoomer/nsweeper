#include "interactivegame.h"
#include "gamesetting.h"
#include "interactivecontroller.h"
#include "interactivedisplay.h"
#include "regularboard.h"
#include <memory>
#include <ncpp/NotCurses.hh>

namespace nsweeper {
template <typename BoardType>
void distribute(BoardType &&board, size_t n, unsigned int seed) {
  std::mt19937_64 rng{seed};
  size_t size = board.size();
  std::vector<size_t> nums(size);
  std::iota(nums.begin(), nums.end(), 0);
  std::shuffle(nums.begin(), nums.end(), rng);
  board.clear();
  size_t i = 0;
  for (auto it = nums.begin(); i < n && it != nums.end(); ++i, ++it) {
    board.setMine(true, *it);
  }
}

InteractiveGame::InteractiveGame(ncpp::NotCurses &nc)
    : board{RegularBoard{9, 9}}, cursor{}, nc{nc},
      display{std::make_unique<InteractiveDisplay>(board, cursor,
                                                   *nc.get_stdplane())},
      controller{std::make_unique<InteractiveController>(board, cursor, nc)} {
  GameSetting s = settings[0].first;
  board.emplace<RegularBoard>(s.dim.x, s.dim.y);
  auto seed = std::random_device{}();
  std::visit([&](auto &&board) { distribute(board, s.numMines, seed); }, board);
  runLoop();
}

void InteractiveGame::runLoop() {
  while (true) {
    display->notify();
    nc.render();
    controller->makeMove();

    auto state = std::visit([](auto &&b) { return b.getState(); }, board);

    if (!std::holds_alternative<std::monostate>(state)) {
      break;
    }
  }
  display->notify();
  nc.render();
  while (nc.get(true) != 'q')
    ;
}
} // namespace nsweeper
