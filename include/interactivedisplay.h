#pragma once

#include "display.h"
#include <ncpp/Plane.hh>

namespace nsweeper {
class InteractiveDisplay : public Display {
  const Vec2 &cursor;
  ncpp::Plane statDisp;
  ncpp::Plane boardDisp;

public:
  [[nodiscard]] InteractiveDisplay(const BoardVariant &board,
                                   const Vec2 &cursor, ncpp::Plane &parent);

  virtual void notify() override;
};
} // namespace nsweeper
