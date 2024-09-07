#pragma once

#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <cstdlib>
#include <ostream>

#include "Util.h"

enum class PixelState { Dead = 0, Alive = 1, };

class Pixel {
public:
  Pixel(Util::Pos pos, PixelState state);
  void handleEvent(SDL_Event event);
  void setState(PixelState state);
  std::string getState()const;
  bool isDead() const;
  bool isAlive() const;
  Util::Pos getPos() const;
  Util::Dimensions getDim() const;
  int getWidth() const;
  int getHeight() const;
  SDL_Rect getTextBox();
  void draw(SDL_Renderer *render);
  Util::Pos arrIndexToWorld()const;

private:
 //  SDL_Surface *surface;
  SDL_Rect rect;
  PixelState pxstate{PixelState::Dead};
  Util::Pos pos;
  Util::Dimensions dim{10, 10};
  Util::RGBA background_col;
public:
  Pixel(Pixel &px); // copy constructor
  friend std::ostream& operator<<(std::ostream &out, Pixel &val);
};
