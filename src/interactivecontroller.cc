#include "interactivecontroller.h"
#include "boardvisitor.h"
#include "controller.h"
#include "gamestate.h"
#include "pressresult.h"
#include "regularboard.h"
#include "vec.h"
#include <ncpp/NotCurses.hh>

namespace nsweeper {
InteractiveController::InteractiveController(Board *board, size_t &cursor,
                                             ncpp::NotCurses &nc)
    : Controller{board}, cursor{cursor}, nc{nc} {}

struct MakeMoveVisitor : public BoardVisitor {
  uint32_t k;
  size_t &cursor;

  MakeMoveVisitor(uint32_t k, size_t &cursor) : k{k}, cursor{cursor} {}

  virtual void operator()(RegularBoard &board) override {
    auto [cx, cy] = board.fromIndex(cursor);
    auto [width, height] = board.getDim();
    switch (k) {
    case 'h':
      cx = std::clamp(cx - 1, 0, width - 1);
      cursor = board.toIndex(cx, cy);
      break;
    case 'l':
      cx = std::clamp(cx + 1, 0, width - 1);
      cursor = board.toIndex(cx, cy);
      break;
    case 'k':
      cy = std::clamp(cy - 1, 0, height - 1);
      cursor = board.toIndex(cx, cy);
      break;
    case 'j':
      cy = std::clamp(cy + 1, 0, height - 1);
      cursor = board.toIndex(cx, cy);
      break;
    case ' ':
      board.Board::press(cursor);
      break;
    case 'f':
      board.Board::flag(cursor);
      break;
    case 'q':
      board.getState().emplace<GameLost>();
      break;
    }
  }
};

void InteractiveController::makeMove() {
  auto k = nc.get(true);
  getBoard()->accept(MakeMoveVisitor{k, cursor});
}
} // namespace nsweeper
