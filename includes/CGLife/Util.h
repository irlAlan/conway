#pragma once
#include <cstdint>



namespace Util {
struct RGBA {
  uint8_t r, g, b, a;
};

struct Vec2i {
  int x, y;
};

using Pos = Vec2i;
using Dimensions = Vec2i;
}  // namespace Util
//

constexpr Util::Dimensions winDimensions{100,100};
