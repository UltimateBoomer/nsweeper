#include "termdisplay.h"
#include "cellstate.h"
#include "display.h"
#include "gamestate.h"
#include "regularboard.h"
#include "textchar.h"
#include "visitor.h"
#include <array>
#include <format>
#include <variant>

namespace nsweeper {

TermDisplay::TermDisplay(const BoardVariant &board, std::ostream &os)
    : Display{board}, os{os} {}

struct BoardVisitor {
  std::ostream &os;

  template <typename BoardType> void operator()(const BoardType &board) const;
};

template <>
void BoardVisitor::operator()<RegularBoard>(const RegularBoard &board) const {
  os << "+" << std::string(board.getWidth() * 2, '-') << "+" << std::endl;
  for (size_t y = 0; y < board.getHeight(); ++y) {
    os << "|";
    for (size_t x = 0; x < board.getWidth(); ++x) {
      auto &state = board.getCell(x, y).getState();
      std::visit(Visitor{[&](auto) { os << emptyChar; },
                         [&](CellFlagged) { os << flagChar; },
                         [&](CellRevealed v) {
                           os << numDisplayTable[v.numAdjacentMines];
                         }},
                 state);
    }
    os << "|" << std::endl;
  }
  os << "+" << std::string(board.getWidth() * 2, '-') << "+" << std::endl;
}

struct RevealedBoardVisitor {
  std::ostream &os;

  template <typename BoardType> void operator()(const BoardType &board);
};

template <>
void RevealedBoardVisitor::operator()<RegularBoard>(const RegularBoard &board) {
  os << "+" << std::string(board.getWidth() * 2, '-') << "+" << std::endl;
  for (size_t y = 0; y < board.getHeight(); ++y) {
    os << "|";
    for (size_t x = 0; x < board.getWidth(); ++x) {
      auto &cell = board.getCell(x, y);
      auto &state = cell.getState();
      std::visit(
          Visitor{[&](auto) { os << (cell.hasMine() ? mineChar : emptyChar); },
                  [&](CellFlagged) {
                    os << (cell.hasMine() ? mineChar : flagChar);
                  },
                  [&](CellRevealed v) {
                    os << numDisplayTable[v.numAdjacentMines];
                  }},
          state);
    }
    os << "|" << std::endl;
  }
  os << "+" << std::string(board.getWidth() * 2, '-') << "+" << std::endl;
}

void TermDisplay::notify() {
  std::visit(
      [&](auto &&b) {
        os << std::format("Mines: {}/{}", b.getNumFlagged(), b.getNumMines())
           << std::endl;
        os << std::format("Board: {}/{}", b.getNumRevealed(), b.size())
           << std::endl;
      },
      getBoard());

  bool revealMines = std::visit(
      [](auto &&b) {
        return !std::holds_alternative<std::monostate>(b.getState());
      },
      getBoard());
  if (revealMines) {
    std::visit(RevealedBoardVisitor{os}, getBoard());
  } else {
    std::visit(BoardVisitor{os}, getBoard());
  }
}

} // namespace nsweeper
