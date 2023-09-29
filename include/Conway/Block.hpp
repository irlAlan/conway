#include "SDL_rect.h"
#include <Conway/General.hpp>

#ifndef BLOCK_HPP
#define BLOCK_HPP


class Block{
public:

  enum class State{
    Alive = 0,
    Dead = 1,
  };

public:
  Block();
  void setState(State blockState);
  State getState()const;
  void makeBlock(Gen::Vec2<float> pos);
  SDL_Rect getBlock()const;
  void move(int x);
  Gen::Vec2<float> getDimensions()const;
  Gen::Vec2<float> getPosition()const;
  SDL_Rect rect;
private:
  Gen::Vec2<float> position;
  const Gen::Vec2<float> dimension{10.f,10.f};
  State blockState;
};
#endif
