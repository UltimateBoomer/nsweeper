#pragma once

#include "boardvariant.h"
#include "display.h"
#include "pressresult.h"
#include "regularboard.h"
#include <algorithm>
#include <random>

namespace nsweeper {
class Controller {
  BoardVariant &board;

public:
  [[nodiscard]] Controller(BoardVariant &board);
  virtual ~Controller() = default;

  // Make move on board
  virtual PressResult makeMove() = 0;

  // Randomly distribute n mines
  /* void distribute(size_t n, unsigned int seed); */

protected:
  [[nodiscard]] BoardVariant &getBoard();
};

/* template <typename BoardType> */
/* Controller<BoardType>::Controller(BoardType &board, Display<BoardType>
 * &display) */
/*     : board{board}, display{display} {} */
/**/
/* template <typename BoardType> */
/* void Controller<BoardType>::distribute(size_t n, unsigned int seed) { */
/*   std::mt19937_64 rng{seed}; */
/*   size_t size = this->getBoard().size(); */
/*   std::vector<size_t> nums(size); */
/*   std::iota(nums.begin(), nums.end(), 0); */
/*   std::shuffle(nums.begin(), nums.end(), rng); */
/**/
/*   size_t i = 0; */
/*   for (auto it = nums.begin(); i < n && it != nums.end(); ++i, ++it) { */
/*     this->getBoard().setMine(true, *it); */
/*   } */
/* } */
/**/
/* template <typename BoardType> BoardType &Controller<BoardType>::getBoard() {
 */
/*   return board; */
/* } */
/**/
/* template <typename BoardType> */
/* Display<BoardType> &Controller<BoardType>::getDisplay() { */
/*   return display; */
/* } */
} // namespace nsweeper
