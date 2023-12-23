#pragma once

#include "cellstate.h"
#include "pressresult.h"
#include <optional>
#include <vector>

namespace nsweeper {
// Cell on board with state
class Cell {
  bool mine;
  CellState state;

  std::vector<Cell *> adjacentCells;

public:
  Cell();
  Cell(bool mine);

  bool hasMine() const;

  // Set whether the cell contains a mine
  // Return the change in num of mines on board
  int setMine(bool mine);

  std::pair<PressResult, int> press();
  std::pair<PressResult, int> flag();

  CellState &getState();
  const CellState &getState() const;

  void addAdjacentCell(Cell &other);

private:
  // Reveal cell
  std::pair<PressResult, int> reveal();

  // Reveal adjacent cells if possible
  // Assume cell is revealed
  std::pair<PressResult, int> revealAdjacent();
};
} // namespace nsweeper
