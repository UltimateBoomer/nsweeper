#pragma once

#include "display.h"
#include "vec.h"
#include <ncpp/Plane.hh>

namespace nsweeper {
class InteractiveDisplay : public Display {
  const size_t &cursor;
  ncpp::Plane statDisp;
  ncpp::Plane boardDisp;

public:
  [[nodiscard]] InteractiveDisplay(const Board *board, const size_t &cursor,
                                   ncpp::Plane &parent);

  virtual void notify() override;

private:
  void drawStat();
  void drawBoard();
};
} // namespace nsweeper
