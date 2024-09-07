#include <SDL2/SDL.h>

#include <CGLife/CGLife.h>
#include <CGLife/Util.h>

#include <chrono>
#include <random>


// world pos e.g. 0-1200, 0-800
// user enters position as a pixel pos: e.g. 1,1 or 10,10, 12,16 for top left pos


int main() {
  // 32bit mersenne twister seeded using steady clock for better randomness
  std::mt19937 mt{static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()
  )};
  // reusable uniform rand num generator between 0 and world bounds
  std::uniform_int_distribution<> worldseed{0,winDimensions.x*winDimensions.y};
  Util::Vec2i seed{worldseed(mt), worldseed(mt)};
  CGLife game{"Game of life", seed};
  // game.run();
  return 0;
}
