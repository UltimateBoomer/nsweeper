#include "controller.h"

namespace nsweeper {
Controller::Controller(Board *board) : board{board} {}

Board *Controller::getBoard() { return board; }

} // namespace nsweeper
