#pragma once

namespace nsweeper {
template <typename T>
concept Observer = requires(T a) {
  { a.notify() };
};
}
