#pragma once
#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <array>
#include <cstdlib>
#include <memory>
#include <string>

#include <CGLife/Pixel.h>
#include <CGLife/Util.h>

// y - column
// x - row 

class CGLife {
  using Arr2p = std::array<std::array<std::unique_ptr<Pixel>,winDimensions.y>,winDimensions.x>;
public:
  CGLife(std::string_view title, Util::Vec2i seed);
  ~CGLife();
  void run();
  // dont need this after swapping from vec to 2d vec
  Util::Pos worldToArrIndex(int row, int column);

private:
  void draw();
  void update(float dt);
  Util::Pos boundsCheck(const Util::Pos &p);
  int checkNeighbour(const Util::Pos &pos);

private:
  SDL_Window *window{nullptr};
  SDL_Renderer *renderer{nullptr};
  Pixel *px;
  Arr2p pxls;
  SDL_Event event;
  bool mouseActive{false};
  bool mouseHover{false};
  Util::Pos mousePos;
  std::string title;
  Util::RGBA backCol;
};
