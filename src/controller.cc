#include "controller.h"
#include "boardvariant.h"

namespace nsweeper {
Controller::Controller(BoardVariant &board) : board{board} {}

BoardVariant &Controller::getBoard() { return board; }

} // namespace nsweeper
