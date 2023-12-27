#include "display.h"

namespace nsweeper {
Display::Display(const Board *board) : board{board} {}

const Board *Display::getBoard() const { return board; }
} // namespace nsweeper
