#include "interactivecontroller.h"
#include "boardvariant.h"
#include "controller.h"
#include "gamestate.h"
#include "pressresult.h"
#include "regularboard.h"
#include "vec.h"
#include <ncpp/NotCurses.hh>

namespace nsweeper {
InteractiveController::InteractiveController(BoardVariant &board, Vec2 &cursor,
                                             ncpp::NotCurses &nc)
    : Controller{board}, cursor{cursor}, nc{nc} {}

struct MakeMoveVisitor {
  uint32_t k;
  Vec2 &cursor;

  void operator()(RegularBoard &board) {
    switch (k) {
    case 'h':
      cursor.x -= 1;
      cursor.x = std::clamp(cursor.x, 0, board.getWidth() - 1);
      break;
    case 'l':
      cursor.x += 1;
      cursor.x = std::clamp(cursor.x, 0, board.getWidth() - 1);
      break;
    case 'k':
      cursor.y -= 1;
      cursor.y = std::clamp(cursor.y, 0, board.getHeight() - 1);
      break;
    case 'j':
      cursor.y += 1;
      cursor.y = std::clamp(cursor.y, 0, board.getHeight() - 1);
      break;
    case ' ':
      board.press(cursor);
      break;
    case 'f':
      board.flag(cursor);
      break;
    case 'q':
      board.getState().emplace<GameLost>();
      break;
    }
  }
};

void InteractiveController::makeMove() {
  auto k = nc.get(true);
  std::visit(MakeMoveVisitor{k, cursor}, getBoard());
}
} // namespace nsweeper
