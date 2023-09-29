#include "SDL_rect.h"
#include <Conway/Block.hpp>
  
Block::Block(){}

void Block::setState(State blockState){
  this->blockState = blockState;
}

Block::State Block::getState()const{return blockState;}
  
void Block::makeBlock(Gen::Vec2<float> pos){
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = dimension.x;
  rect.h = dimension.y;
}
  
void Block::move(int x){
  // position += speed;
  rect.x += x;
  // rect.y += speed.y;
}

SDL_Rect Block::getBlock()const{return rect;}

Gen::Vec2<float> Block::getDimensions()const {return dimension;}
Gen::Vec2<float> Block::getPosition()const {return position;}
