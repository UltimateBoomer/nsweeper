#pragma once

#include "display.h"
#include <ostream>

namespace nsweeper {
// Display that prints to terminal on updates
class TermDisplay : public Display {
  std::ostream &os;

public:
  TermDisplay(const BoardVariant &board, std::ostream &os);

  virtual void notify() override;
};
} // namespace nsweeper
