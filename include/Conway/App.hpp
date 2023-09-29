#include <iostream>
#include <Conway/General.hpp>
#include <Conway/Block.hpp>
#include <mutex>

#include "SDL.h"

#ifndef APP_HPP
#define APP_HPP


// Singleton class
class App{
public:
  static App *GetInstance(Gen::Vec2<float> dimensions);
  void DestroyApp();
  void run();
  Gen::Vec2<float> getDimensions()const;

  // Singletons must not be cloneable 
  App(App &other) = delete;
  // Singletons must not be asignable 
  void operator=(const App&) = delete;

protected:
  App(Gen::Vec2<float> dimensions);
  ~App();
private: 
  SDL_Window *window{nullptr};
  SDL_Renderer *renderer{nullptr};
  SDL_Event event;
  Block block;


  Gen::Vec2<float> AppDimension;

  static App *pInstance;
  static std::mutex mutex;
};

#endif // APP_HPP
