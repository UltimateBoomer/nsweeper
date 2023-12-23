#pragma once

#include "cell.h"
#include "gamestate.h"
#include "pressresult.h"
#include "subject.h"
#include <variant>

namespace nsweeper {
// Abstract board with linear cell storage
template <typename T, typename PosType> class Board {
  std::vector<Cell> cells;
  size_t numMines = 0;
  size_t numRevealed = 0;
  size_t numFlagged = 0;
  GameState state;

public:
  // Press the cell at pos
  PressResult press(size_t i);
  template <typename... PosArgs> PressResult press(PosArgs &&...pos);

  // Flag the cell at pos
  PressResult flag(size_t i);
  template <typename... PosArgs> PressResult flag(PosArgs &&...pos);

  // Set whether cell at pos has mine or not
  void setMine(bool mine, size_t i);
  template <typename... PosArgs> void setMine(bool mine, PosArgs &&...pos);

  // Get cell at pos
  Cell &getCell(size_t i);
  const Cell &getCell(size_t i) const;
  template <typename... PosArgs> Cell &getCell(PosArgs &&...pos);
  template <typename... PosArgs> const Cell &getCell(PosArgs &&...pos) const;

  GameState &getState();
  const GameState &getState() const;

  void clear();

  size_t size() const;
  size_t getNumMines() const;
  size_t getNumRevealed() const;
  size_t getNumFlagged() const;

  size_t toIndex(PosType pos) const;

  using Pos = PosType;

  // Convert pos to index
protected:
  Board(size_t numCells);
};

template <typename T, typename PosType>
PressResult Board<T, PosType>::press(size_t i) {
  auto [result, n] = getCell(i).press();
  numRevealed += n;
  if (std::holds_alternative<PressMine>(result)) {
    getState().template emplace<GameLost>();
  } else if (numRevealed + numMines == size()) {
    getState().template emplace<GameWon>();
  }
  return result;
}

template <typename T, typename PosType>
template <typename... PosArgs>
PressResult Board<T, PosType>::press(PosArgs &&...pos) {
  return press(toIndex(PosType{std::forward<PosArgs>(pos)...}));
}

template <typename T, typename PosType>
PressResult Board<T, PosType>::flag(size_t i) {
  auto [result, n] = getCell(i).flag();
  numFlagged += n;
  return result;
}

template <typename T, typename PosType>
template <typename... PosArgs>
PressResult Board<T, PosType>::flag(PosArgs &&...pos) {
  return flag(toIndex(PosType{std::forward<PosArgs>(pos)...}));
}

template <typename T, typename PosType>
void Board<T, PosType>::setMine(bool mine, size_t i) {
  numMines += getCell(i).setMine(mine);
}

template <typename T, typename PosType>
template <typename... PosArgs>
void Board<T, PosType>::setMine(bool mine, PosArgs &&...pos) {
  setMine(toIndex(PosType{std::forward<PosArgs>(pos)...}));
}

template <typename T, typename PosType>
Cell &Board<T, PosType>::getCell(size_t i) {
  return cells[i];
}

template <typename T, typename PosType>
const Cell &Board<T, PosType>::getCell(size_t i) const {
  return cells[i];
}

template <typename T, typename PosType>
template <typename... PosArgs>
Cell &Board<T, PosType>::getCell(PosArgs &&...pos) {
  return cells[toIndex(PosType{std::forward<PosArgs>(pos)...})];
}

template <typename T, typename PosType>
template <typename... PosArgs>
const Cell &Board<T, PosType>::getCell(PosArgs &&...pos) const {
  return cells[toIndex(PosType{std::forward<PosArgs>(pos)...})];
}

template <typename T, typename PosType>
GameState &Board<T, PosType>::getState() {
  return state;
}

template <typename T, typename PosType>
const GameState &Board<T, PosType>::getState() const {
  return state;
}

template <typename T, typename PosType> void Board<T, PosType>::clear() {
  for (auto &c : cells) {
    c.setMine(false);
  }
  numMines = 0;
}

template <typename T, typename PosType> size_t Board<T, PosType>::size() const {
  return cells.size();
}

template <typename T, typename PosType>
size_t Board<T, PosType>::getNumMines() const {
  return numMines;
}

template <typename T, typename PosType>
size_t Board<T, PosType>::getNumRevealed() const {
  return numRevealed;
}

template <typename T, typename PosType>
size_t Board<T, PosType>::getNumFlagged() const {
  return numFlagged;
}

template <typename T, typename PosType>
size_t Board<T, PosType>::toIndex(PosType pos) const {
  return static_cast<const T *>(this)->toIndex(pos);
}

template <typename T, typename PosType>
Board<T, PosType>::Board(size_t numCells) : cells(numCells), numMines{0} {}
} // namespace nsweeper
