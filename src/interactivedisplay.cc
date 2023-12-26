#include "interactivedisplay.h"
#include "boardvariant.h"
#include "cellstate.h"
#include "display.h"
#include "gamestate.h"
#include "regularboard.h"
#include "textchar.h"
#include "visitor.h"
#include <format>
#include <ncpp/CellStyle.hh>
#include <ncpp/NCAlign.hh>
#include <ncpp/Plane.hh>
#include <variant>

namespace nsweeper {
struct BoardDimVisitor {
  std::pair<int, int> operator()(const RegularBoard &board) const {
    return {board.getWidth() * 2, board.getHeight()};
  }
};

InteractiveDisplay::InteractiveDisplay(const BoardVariant &board,
                                       const Vec2 &cursor, ncpp::Plane &parent)
    : Display{board}, cursor{cursor},
      statDisp{parent, 3, 80, 0, ncpp::NCAlign::Center},
      boardDisp{parent, 80, 80, 4, ncpp::NCAlign::Center} {}

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
    statDisp.putstr(
        2, 0, std::format("Pos: {}, {}", cursor.x + 1, cursor.y + 1).c_str());
  }
};

struct CellCharVisitor {
  std::string operator()(const std::monostate &state) { return emptyChar; }

  std::string operator()(const CellFlagged &state) { return flagChar; }

  std::string operator()(const CellRevealed &state) {
    return numDisplayTable[state.numAdjacentMines];
  }
};

struct PrintBoardVisitor {
  ncpp::Plane &boardDisp;
  const Vec2 &cursor;

  void operator()(const RegularBoard &board) {
    boardDisp.erase();
    boardDisp.resize(board.getHeight(), board.getWidth() * 2);
    for (int y = 0; y < board.getHeight(); ++y) {
      for (int x = 0; x < board.getWidth(); ++x) {
        auto &state = board.getCell(x, y).getState();
        auto c = std::visit(CellCharVisitor{}, state);
        boardDisp.styles_set(y == cursor.y && x == cursor.x
                                 ? ncpp::CellStyle::Underline
                                 : ncpp::CellStyle::None);
        boardDisp.putstr(y, x * 2, c.c_str());
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

struct PrintRevealedBoardVisitor {
  ncpp::Plane &boardDisp;
  const Vec2 &cursor;

  void operator()(const RegularBoard &board) {
    boardDisp.erase();
    boardDisp.resize(board.getHeight(), board.getWidth() * 2);
    for (int y = 0; y < board.getHeight(); ++y) {
      for (int x = 0; x < board.getWidth(); ++x) {
        auto &cell = board.getCell(x, y);
        auto c = std::visit(RevealedCellCharVisitor{cell}, cell.getState());
        boardDisp.putstr(y, x * 2, c.c_str());
      }
    }
  }
};

void InteractiveDisplay::notify() {
  std::visit(PrintStatVisitor{statDisp, cursor}, getBoard());
  auto state =
      std::visit([](auto &board) { return board.getState(); }, getBoard());
  if (std::holds_alternative<GameLost>(state)) {
    std::visit(PrintRevealedBoardVisitor{boardDisp, cursor}, getBoard());
  } else {
    std::visit(PrintBoardVisitor{boardDisp, cursor}, getBoard());
  }
}

} // namespace nsweeper
