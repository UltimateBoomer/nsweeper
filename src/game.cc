#include "game.h"
#include "gamestate.h"
#include "pressresult.h"
#include "regularboard.h"
#include "termcontroller.h"
#include "termdisplay.h"
#include "visitor.h"
#include <array>
#include <format>
#include <memory>
#include <sstream>
#include <variant>

namespace nsweeper {
struct GameSetting {
  Vec2 dim;
  size_t numMines;
};

constexpr std::array settings{GameSetting{{9, 9}, 10},
                              GameSetting{{16, 16}, 40},
                              GameSetting{{30, 16}, 99}};

Game::Game(std::istream &is, std::ostream &os)
    : board{RegularBoard{8, 8}},
      display{std::make_unique<TermDisplay>(board, os)},
      controller{std::make_unique<TermController>(board, is, os)}, is{is},
      os{os} {}

struct PosReader {
  std::istream &is;

  template <typename BoardType>
  BoardType::Pos operator()(const BoardType &board);
};

template <>
RegularBoard::Pos
PosReader::operator()<RegularBoard>(const RegularBoard &board) {
  size_t x, y;
  is >> x >> y;
  return {x, y};
}

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

void Game::run() {
  os << "Welcome to NSweeper!" << std::endl;
  os << "Select type of game: " << std::endl;
  for (auto it = settings.begin(); it != settings.end(); ++it) {
    os << std::format("{}: ({}x{}, {} mines)",
                      std::distance(settings.begin(), it), it->dim.x, it->dim.y,
                      it->numMines)
       << std::endl;
  }
  std::string mode;
  GameSetting s;
  while (is) {
    os << "> ";
    is >> mode;

    size_t num;
    if (std::istringstream{mode} >> num) {
      if (num < settings.size()) {
        s = settings[num];
        break;
      }
    }
  }

  auto seed = std::random_device{}();
  os << "Seed: " << seed << std::endl;
  board.emplace<RegularBoard>(s.dim.x, s.dim.y);
  std::visit([&](auto &&board) { distribute(board, s.numMines, seed); }, board);

  /* setup(); */
  runLoop();
}

void Game::setup() {
  std::string cmd;
  bool cont = true;
  while (cont) {
    try {
      /* int gameType = 0; */
      /* os << "Welcome to NSweeper!" << std::endl; */
      /* os << "Select type of game:" << std::endl; */
      /* os << "0: Beginner (9x9/10)" << std::endl; */
      /* os << "1: Intermediate (16x16/40)" << std::endl; */
      /* os << "2: Advanced ()" << std::endl; */
      os << "SETUP > ";
      is >> cmd;

      if (cmd == "s" || cmd == "set") {
        auto pos = std::visit(PosReader{is}, board);
        std::visit([&](auto &&board) { board.setMine(true, pos); }, board);
      } else if (cmd == "u" || cmd == "unset") {
        auto pos = std::visit(PosReader{is}, board);
        std::visit([&](auto &&board) { board.setMine(false, pos); }, board);
      } else if (cmd == "r" || cmd == "random") {
        size_t n;
        is >> n;
        auto seed = std::random_device{}();
        os << "Seed: " << seed << std::endl;
        std::visit([&](auto &&board) { distribute(board, n, seed); }, board);
      } else if (cmd == "rs" || cmd == "random_seed") {
        size_t n;
        unsigned int seed;
        is >> n >> seed;
        std::visit([&](auto &&board) { distribute(board, n, seed); }, board);
      } else if (cmd == "d" || cmd == "done") {
        cont = false;
      }
    } catch (std::iostream::failure &) {
      os << "Exiting" << std::endl;
      cont = false;
    }
  }
}

void Game::runLoop() {
  std::string cmd;
  while (is) {
    display->notify();
    controller->makeMove();
    auto state = std::visit([](auto &&b) { return b.getState(); }, board);
    if (std::holds_alternative<GameWon>(state)) {
      os << "You won!" << std::endl;
      break;
    } else if (std::holds_alternative<GameLost>(state)) {
      os << "You lost!" << std::endl;
      break;
    }
  }
}
} // namespace nsweeper
