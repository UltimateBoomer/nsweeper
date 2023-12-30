#include "interactivegame/interactivecontroller.h"
#include "board/boardstate.h"
#include "board/boardvisitor.h"
#include "board/pressresult.h"
#include "board/regularboard.h"
#include "board/vec.h"
#include "controller.h"
#include <ncpp/NotCurses.hh>
#include <notcurses/notcurses.h>

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
  ncinput in;
  nc.get(true, &in);
  if (in.evtype == NCTYPE_PRESS) {
    getBoard()->accept(MakeMoveVisitor{in.id, cursor});
  }
}
} // namespace nsweeper
