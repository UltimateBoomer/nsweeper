#pragma once

#include <variant>
namespace nsweeper {
// Cell is flagged
struct CellFlagged {};

// Cell is revealed
struct CellRevealed {
  int numAdjacentMines;
};

// Represent current state of cell
using CellState = std::variant<std::monostate, CellFlagged, CellRevealed>;

} // namespace nsweeper
