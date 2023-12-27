#include "board.h"
#include "pressresult.h"

namespace nsweeper {
PressResult Board::press(size_t i) {
  auto [result, n] = getCell(i).press();
  numRevealed += n;
  if (std::holds_alternative<PressMine>(result)) {
    getState().emplace<GameLost>();
  } else if (numRevealed + numMines == size()) {
    getState().emplace<GameWon>();
  }
  return result;
}

PressResult Board::flag(size_t i) {
  auto [result, n] = getCell(i).flag();
  numFlagged += n;
  return result;
}

void Board::setMine(bool mine, size_t i) {
  numMines += getCell(i).setMine(mine);
}

Cell &Board::getCell(size_t i) { return cells[i]; }

const Cell &Board::getCell(size_t i) const { return cells[i]; }

GameState &Board::getState() { return state; }

const GameState &Board::getState() const { return state; }

void Board::clear() {
  for (auto &c : cells) {
    c.setMine(false);
  }
  numMines = 0;
  numRevealed = 0;
  numFlagged = 0;
}

size_t Board::size() const { return cells.size(); }

size_t Board::getNumMines() const { return numMines; }

size_t Board::getNumRevealed() const { return numRevealed; }

size_t Board::getNumFlagged() const { return numFlagged; }

Board::Board(size_t numCells) : cells(numCells) {}

Board::Board(size_t numCells, size_t expNumAdjacent)
    : cells(numCells, Cell{expNumAdjacent}) {}

} // namespace nsweeper
