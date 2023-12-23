#pragma once

#include "boardvariant.h"

namespace nsweeper {
// Abstract board display that can handle multiple board variants
class Display {
  const BoardVariant &board;

public:
  Display(const BoardVariant &board);
  virtual ~Display() = default;

  // Update display
  virtual void notify() = 0;

protected:
  const BoardVariant &getBoard() const;
};

/* template <typename BoardType> */
/* Display<BoardType>::Display(const BoardType &board) : board{board} {} */
/**/
/* template <typename BoardType> */
/* const BoardType &Display<BoardType>::getBoard() const { */
/*   return board; */
/* } */
} // namespace nsweeper
