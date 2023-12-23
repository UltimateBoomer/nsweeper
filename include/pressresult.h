#pragma once

#include <cstddef>
#include <variant>

namespace nsweeper {

// Successful press
class PressSuccessful {};

// Invalid press (flagged or already revealed)
class PressInvalid {};

// Cell has mine
class PressMine {};

using PressResult = std::variant<PressSuccessful, PressInvalid, PressMine>;
} // namespace nsweeper
