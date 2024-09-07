#include <SDL_events.h>
#include <SDL_render.h>

#include <CGLife/Pixel.h>
#include <CGLife/Util.h>
#include <fmt/format.h>

Pixel::Pixel(Util::Pos pos, PixelState state)
    :pxstate(state), pos{pos} {
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = dim.x;
  rect.h = dim.y;
}

void Pixel::handleEvent(SDL_Event event) {
  switch (event.type) {}
}

bool Pixel::isDead() const{
  if(pxstate == PixelState::Dead)
    return true;
  return false;
}
bool Pixel::isAlive() const {
  if (pxstate == PixelState::Alive)
    return true;
  return false;
}

void Pixel::draw(SDL_Renderer *renderer) {
  // if its alive then colour ffwhite else colour black 
  if(pxstate == PixelState::Dead){
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff,
                         0xff, 255);
  }else if (pxstate == PixelState::Alive){
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55,
                         0x55, 255);
  }
  SDL_RenderFillRect(renderer, &rect);
  SDL_RenderDrawRect(renderer,&rect);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
}


void Pixel::setState(PixelState state){pxstate = state;}
std::string Pixel::getState()const{
  std::string state;
  if(pxstate == PixelState::Alive) state="Alive";
  else if (pxstate == PixelState::Dead)state="Dead";
  return state;
}
Util::Pos Pixel::getPos() const { return pos; }
Util::Dimensions Pixel::getDim() const { return dim; }
int Pixel::getWidth() const { return dim.x; }
int Pixel::getHeight() const { return dim.y; }
SDL_Rect Pixel::getTextBox() { return {pos.x, pos.y, dim.x, dim.y}; }

Util::Pos Pixel::arrIndexToWorld()const{return {pos.x/10,pos.y/10};}


Pixel::Pixel(Pixel &px){
  this->pxstate = px.pxstate;
  this->pos = px.pos;
}

std::ostream& operator<<(std::ostream &out, Pixel &val){
  out << fmt::format("Position: ({},{}), State: {}\n", val.arrIndexToWorld().x, val.arrIndexToWorld().y,val.getState());
  return out;
}
