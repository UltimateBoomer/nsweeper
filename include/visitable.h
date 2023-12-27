#pragma once

namespace nsweeper {
template <typename Visitor> struct Visitable {
  virtual void accept(const Visitor &visitor) const = 0;
};

template <typename Visitor, typename Derived>
struct VisitableImpl : public Visitable<Visitor> {
  virtual void accept(const Visitor &visitor) const override {
    visitor.visit(static_cast<Derived &>(*this));
  }
};
} // namespace nsweeper
