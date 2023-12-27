#pragma once

#include "boardstate.h"
#include "boardvisitor.h"
#include "cell.h"
#include "pressresult.h"
#include <variant>

namespace nsweeper {
// Abstract board with linear cell storage
// Subclasses should implement connection between cells in constructor
class Board {
  std::vector<Cell> cells;
  size_t numMines;
  size_t numRevealed;
  size_t numFlagged;
  BoardState state;

public:
  virtual ~Board() = default;
  // Press the cell at pos
  PressResult press(size_t i);
  // Flag the cell at pos
  PressResult flag(size_t i);
  // Set whether cell at pos has mine or not
  void setMine(bool mine, size_t i);
  // Get cell at pos
  [[nodiscard]] Cell &getCell(size_t i);
  [[nodiscard]] const Cell &getCell(size_t i) const;

  BoardState &getState();
  const BoardState &getState() const;

  void clear();

  [[nodiscard]] size_t size() const;
  [[nodiscard]] size_t getNumMines() const;
  [[nodiscard]] size_t getNumRevealed() const;
  [[nodiscard]] size_t getNumFlagged() const;

  virtual void accept(BoardVisitor &&visitor) = 0;
  virtual void accept(ConstBoardVisitor &&visitor) const = 0;

protected:
  [[nodiscard]] explicit Board(size_t numCells);
  [[nodiscard]] explicit Board(size_t numCells, size_t expNumAdjacent);
};
} // namespace nsweeper
