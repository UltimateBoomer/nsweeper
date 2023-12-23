#include "display.h"
#include "boardvariant.h"

namespace nsweeper {
Display::Display(const BoardVariant &board) : board{board} {}

const BoardVariant &Display::getBoard() const { return board; }
} // namespace nsweeper
