#pragma once

#include "cellstate.h"
#include "pressresult.h"
#include <optional>
#include <vector>

namespace nsweeper {
// Cell on board with state
// Connected to adjacent cells
class Cell {
  bool mine;
  CellState state;

  std::vector<Cell *> adjacentCells;

public:
  [[nodiscard]] Cell();
  [[nodiscard]] explicit Cell(size_t expNumAdjacent);

  [[nodiscard]] bool hasMine() const;

  // Set whether the cell contains a mine
  // Return the change in num of mines on board
  int setMine(bool mine);

  // Press the cell
  // Return press result and change in num of cells revealed
  std::pair<PressResult, int> press();

  // Flag the cell
  // Return press result and change in num of cells flagged
  std::pair<PressResult, int> flag();

  [[nodiscard]] CellState &getState();
  [[nodiscard]] const CellState &getState() const;

  // Set the other cell as
  void addAdjacentCell(Cell &other);

private:
  // Reveal cell
  std::pair<PressResult, int> reveal();

  // Reveal adjacent cells if possible
  // Assume cell is revealed
  std::pair<PressResult, int> revealAdjacent();
};
} // namespace nsweeper
