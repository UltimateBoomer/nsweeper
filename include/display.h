#pragma once

#include "boardvariant.h"

namespace nsweeper {
// Abstract board display that can handle multiple board variants
class Display {
  const BoardVariant &board;

public:
  [[nodiscard]] Display(const BoardVariant &board);
  virtual ~Display() = default;

  // Update display
  virtual void notify() = 0;

protected:
  [[nodiscard]] const BoardVariant &getBoard() const;
};
} // namespace nsweeper
