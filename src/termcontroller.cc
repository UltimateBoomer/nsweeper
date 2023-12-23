#include "termcontroller.h"
#include "pressresult.h"
#include "regularboard.h"
#include "visitor.h"
#include <istream>
#include <variant>

namespace nsweeper {

TermController::TermController(BoardVariant &board, std::istream &is,
                               std::ostream &os)
    : Controller{board}, is{is}, os{os} {}

PressResult TermController::makeMove() {
  std::string cmd;
  os << "> ";
  is >> cmd;

  if (cmd == "p" || cmd == "press") {
    size_t x, y;
    is >> x >> y;
    return std::visit([&](auto &&board) { return board.press(x, y); },
                      getBoard());
  } else if (cmd == "f" || cmd == "flag") {
    size_t x, y;
    is >> x >> y;
    return std::visit([&](auto &&board) { return board.flag(x, y); },
                      getBoard());
  }
  return PressInvalid();
}

} // namespace nsweeper
