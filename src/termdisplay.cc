#include "termdisplay.h"
#include "cellstate.h"
#include "display.h"
#include "regularboard.h"
#include "visitor.h"
#include <array>
#include <format>
#include <variant>

namespace nsweeper {
constexpr std::string emptyChar = "・";
constexpr std::array<std::string, 10> numDisplayTable{
    "＋", "１", "２", "３", "４", "５", "６", "７", "８", "９"};
constexpr std::string flagChar = "🚩";

TermDisplay::TermDisplay(const BoardVariant &board, std::ostream &os)
    : Display{board}, os{os} {}

struct BoardVisitor {
  std::ostream &os;

  template <typename BoardType> void operator()(const BoardType &board);
};

template <>
void BoardVisitor::operator()<RegularBoard>(const RegularBoard &board) {
  os << "+" << std::string(board.getWidth() * 2, '-') << "+" << std::endl;
  for (size_t y = 0; y < board.getHeight(); ++y) {
    os << "|";
    for (size_t x = 0; x < board.getWidth(); ++x) {
      auto &state = board.getCell(x, y).getState();
      std::visit(Visitor{[this](auto v) { os << emptyChar; },
                         [this](CellFlagged v) { os << flagChar; },
                         [this](CellRevealed v) {
                           os << numDisplayTable[v.numAdjacentMines];
                         }},
                 state);
    }
    os << "|" << std::endl;
  }
  os << "+" << std::string(board.getWidth() * 2, '-') << "+" << std::endl;
}

void TermDisplay::notify() {
  /* size_t size = */
  /*     std::visit([](auto &&b) { return b.getNumFlagged(); }, getBoard()); */
  /* size_t numMines = */
  /*     std::visit([](auto &&b) { return b.getNumMines(); }, getBoard()); */
  /* size_t numRevealed = */
  /*     std::visit([](auto &&b) { return b.getNumRevealed(); }, getBoard()); */
  /* size_t numFlagged = */
  /*     std::visit([](auto &&b) { return b.getNumFlagged(); }, getBoard()); */
  std::visit(
      [&](auto &&b) {
        os << std::format("Mines: {}/{}", b.getNumFlagged(), b.getNumMines())
           << std::endl;
        os << std::format("Board: {}/{}", b.getNumRevealed(), b.size())
           << std::endl;
      },
      getBoard());

  std::visit(BoardVisitor{os}, getBoard());

  /* os << "+" << std::string(getBoard().getWidth() * 2, '-') << "+" <<
   * std::endl; */
  /**/
  /* for (size_t y = 0; y < getBoard().getHeight(); ++y) { */
  /*   os << "|"; */
  /*   for (size_t x = 0; x < getBoard().getWidth(); ++x) { */
  /*     auto &state = getBoard().getCell(x, y).getState(); */
  /*     std::visit(Visitor{[this](auto v) { os << emptyChar; }, */
  /*                        [this](CellFlagged v) { os << flagChar; }, */
  /*                        [this](CellRevealed v) { */
  /*                          os << numDisplayTable[v.numAdjacentMines]; */
  /*                        }}, */
  /*                state); */
  /*   } */
  /*   os << "|" << std::endl; */
}

} // namespace nsweeper
