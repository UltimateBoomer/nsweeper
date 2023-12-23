#pragma once

#include <variant>

namespace nsweeper {
struct GameWon {};
struct GameLost {};

using GameState = std::variant<std::monostate, GameWon, GameLost>;
} // namespace nsweeper
