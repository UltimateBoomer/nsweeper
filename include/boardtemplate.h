#pragma once

#include "board.h"
#include "boardvisitor.h"
#include "pressresult.h"
#include <concepts>

namespace nsweeper {
// Basic template for board implementations with specific coordinate systems
template <typename Derived, typename PosType>
class BoardTemplate : public Board {
  static_assert(std::is_trivially_copy_constructible_v<PosType>);

public:
  PressResult press(auto &&...posArgs) {
    return Board::press(toIndex(posArgs...));
  }

  PressResult flag(auto &&...posArgs) {
    return Board::flag(toIndex(posArgs...));
  }

  void setMine(bool mine, auto &&...posArgs) {
    Board::setMine(toIndex(posArgs...));
  }

  [[nodiscard]] Cell &getCell(auto &&...posArgs) {
    return Board::getCell(toIndex(posArgs...));
  }

  [[nodiscard]] const Cell &getCell(auto &&...posArgs) const {
    return Board::getCell(toIndex(posArgs...));
  }

  // Convert from pos to index
  size_t toIndex(auto &&...posArgs) const {
    return static_cast<const Derived &>(*this).toIndex(posArgs...);
  }

  PosType fromIndex(size_t i) const {
    return static_cast<const Derived &>(*this).fromIndex(i);
  }

  virtual void accept(BoardVisitor &&visitor) override {
    visitor(static_cast<Derived &>(*this));
  }

  virtual void accept(ConstBoardVisitor &&visitor) const override {
    visitor(static_cast<const Derived &>(*this));
  }

protected:
  using Board::Board;
};
} // namespace nsweeper
