#pragma once

#include "regularboard.h"
#include <variant>

namespace nsweeper {
using BoardVariant = std::variant<RegularBoard>;
}
