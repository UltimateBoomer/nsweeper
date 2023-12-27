#include "interactivegame/interactivedisplay.h"
#include "board/boardstate.h"
#include "board/boardvisitor.h"
#include "board/cellstate.h"
#include "board/regularboard.h"
#include "display.h"
#include "textchar.h"
#include "visitor.h"
#include <format>
#include <ncpp/CellStyle.hh>
#include <ncpp/NCAlign.hh>
#include <ncpp/Plane.hh>
#include <variant>

namespace nsweeper {
InteractiveDisplay::InteractiveDisplay(const Board *board, const size_t &cursor,
                                       ncpp::Plane &parent)
    : Display{board}, cursor{cursor},
      statDisp{parent, 3, 80, 0, ncpp::NCAlign::Center},
      boardDisp{parent, 1, 1, 3, ncpp::NCAlign::Center} {}

struct PrintStatVisitor {
  ncpp::Plane &statDisp;
  const Vec2 &cursor;

  void operator()(const auto &board) {
    statDisp.erase();
    statDisp.putstr(
        0, 0,
        std::format("Mines: {}/{}", board.getNumFlagged(), board.getNumMines())
            .c_str());
    statDisp.putstr(
        1, 0,
        std::format("Board: {}/{}", board.getNumRevealed(), board.size())
            .c_str());
    auto &state =
        std::visit([](auto &board) { return board.getState(); }, board);
  }
};

struct CellCharVisitor {
  std::string operator()(const std::monostate &state) { return emptyChar; }

  std::string operator()(const CellFlagged &state) { return flagChar; }

  std::string operator()(const CellRevealed &state) {
    return numDisplayTable[state.numAdjacentMines];
  }
};

struct PrintBoardVisitor : public ConstBoardVisitor {
  ncpp::Plane &boardDisp;
  const size_t &cursor;

  PrintBoardVisitor(ncpp::Plane &boardDisp, const size_t &cursor)
      : boardDisp{boardDisp}, cursor{cursor} {}

  virtual void operator()(const RegularBoard &board) override {
    boardDisp.erase();
    auto [width, height] = board.getDim();
    auto [cx, cy] = board.fromIndex(cursor);
    boardDisp.resize(height, width * 2);
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        auto &state = board.getCell(x, y).getState();
        auto cellChar = std::visit(CellCharVisitor{}, state);
        boardDisp.styles_set(y == cy && x == cx ? ncpp::CellStyle::Underline
                                                : ncpp::CellStyle::None);
        boardDisp.putstr(y, x * 2, cellChar.c_str());
      }
    }
  }
};

struct RevealedCellCharVisitor {
  const Cell &cell;

  std::string operator()(const std::monostate &state) {
    return cell.hasMine() ? mineChar : emptyChar;
  }

  std::string operator()(const CellFlagged &state) {
    return cell.hasMine() ? mineChar : flagChar;
  }

  std::string operator()(const CellRevealed &state) {
    return numDisplayTable[state.numAdjacentMines];
  }
};

struct PrintRevealedBoardVisitor : public ConstBoardVisitor {
  ncpp::Plane &boardDisp;

  PrintRevealedBoardVisitor(ncpp::Plane &boardDisp) : boardDisp{boardDisp} {}

  virtual void operator()(const RegularBoard &board) override {
    boardDisp.erase();
    auto [width, height] = board.getDim();
    boardDisp.resize(height, width * 2);
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        auto &cell = board.getCell(x, y);
        auto c = std::visit(RevealedCellCharVisitor{cell}, cell.getState());
        boardDisp.putstr(y, x * 2, c.c_str());
      }
    }
  }
};

void InteractiveDisplay::notify() {
  drawStat();
  drawBoard();
}

void InteractiveDisplay::drawStat() {
  statDisp.erase();
  statDisp.putstr(0, 0,
                  std::format("Mines: {}/{}", getBoard()->getNumFlagged(),
                              getBoard()->getNumMines())
                      .c_str());
  statDisp.putstr(0, 30,
                  std::format("Revealed: {}/{}", getBoard()->getNumRevealed(),
                              getBoard()->size())
                      .c_str());
  std::visit(Visitor{
                 [&](std::monostate) {},
                 [&](GameWon) { statDisp.putstr(1, 0, "You Win!"); },
                 [&](GameLost) { statDisp.putstr(1, 0, "You Lost!"); },
             },
             getBoard()->getState());
}

void InteractiveDisplay::drawBoard() {
  boardDisp.erase();
  std::visit(Visitor{[&](std::monostate) {
                       getBoard()->accept(PrintBoardVisitor{boardDisp, cursor});
                     },
                     [&](auto) {
                       getBoard()->accept(PrintRevealedBoardVisitor{boardDisp});
                     }},
             getBoard()->getState());
}

} // namespace nsweeper
