#include "cell.h"
#include "cellstate.h"
#include "pressresult.h"
#include "visitor.h"
#include <variant>

namespace nsweeper {
Cell::Cell() : Cell{false} {}

Cell::Cell(bool mine) : mine{false} {}

bool Cell::hasMine() const { return mine; }

int Cell::setMine(bool mine) {
  int diff = static_cast<int>(mine) - static_cast<int>(this->mine);
  this->mine = mine;
  return diff;
}

std::pair<PressResult, int> Cell::press() {
  if (std::holds_alternative<std::monostate>(getState())) {
    return reveal();
  } else if (std::holds_alternative<CellRevealed>(getState())) {
    return revealAdjacent();
  };
  return {PressInvalid{}, 0};
}

std::pair<PressResult, int> Cell::flag() {
  if (std::holds_alternative<std::monostate>(getState())) {
    getState().emplace<CellFlagged>();
    return {PressSuccessful{}, 1};
  } else if (std::holds_alternative<CellFlagged>(getState())) {
    getState().emplace<std::monostate>();
    return {PressSuccessful{}, -1};
  }
  return {PressInvalid{}, 0};
}

CellState &Cell::getState() { return state; }

const CellState &Cell::getState() const { return state; }

void Cell::addAdjacentCell(Cell &other) {
  if (&other == this) {
    return;
  }
  adjacentCells.emplace_back(&other);
}

std::pair<PressResult, int> Cell::reveal() {
  if (!std::holds_alternative<std::monostate>(getState())) {
    return {PressInvalid{}, 0};
  };
  if (hasMine()) {
    return {PressMine(), 0};
  }
  // Determine adjacent mines
  int count = 0;
  for (auto &c : adjacentCells) {
    if (c->hasMine()) {
      ++count;
    }
  }
  getState().emplace<CellRevealed>(count);
  int numRevealed = 1;
  if (count > 0) {
    return {PressSuccessful{}, numRevealed};
  }
  // Propagate press
  for (auto &c : adjacentCells) {
    auto [result, n] = c->reveal();
    numRevealed += n;
  }
  return {PressSuccessful{}, numRevealed};
}

std::pair<PressResult, int> Cell::revealAdjacent() {
  // Determine adjacent flags
  auto numAdjacentMines = std::get<CellRevealed>(getState()).numAdjacentMines;
  int count = 0;
  for (auto &c : adjacentCells) {
    if (std::holds_alternative<CellFlagged>(c->getState())) {
      ++count;
    }
  }
  if (count < numAdjacentMines) {
    return {PressInvalid{}, 0};
  }

  int numRevealed = 0;
  bool mineFound = false;
  for (auto &c : adjacentCells) {
    auto [result, n] = c->reveal();
    numRevealed += n;
    if (std::holds_alternative<PressMine>(result)) {
      mineFound = true;
    }
  }
  if (mineFound) {
    return {PressMine{}, numRevealed};
  }
  return {PressSuccessful{}, numRevealed};
}
} // namespace nsweeper
