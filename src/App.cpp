#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include <Conway/App.hpp>
#include <Conway/Block.hpp>
#include <mutex>

App *App::pInstance{nullptr};
std::mutex App::mutex;

// first time we call GetInstance we lock the storage location
// we make sure the variable is null then we set the variable
// to a new instance
App *App::GetInstance(Gen::Vec2<float> dimensions){
  std::lock_guard<std::mutex> lock(mutex);
  if(pInstance == nullptr){
    pInstance = new App(dimensions);
  }
  return pInstance;
}

App::~App(){
  // Destroy window
  // SDL_DestroyWindow(window);
  // Destroy SDL subsystems
  // SDL_Quit();
  // delete pInstance;
  // pInstance = nullptr;
}

void App::DestroyApp(){
  // Destroy window
  SDL_DestroyWindow(window);
  // Destroy SDL subsystems
  SDL_Quit();
  delete pInstance;
  pInstance = nullptr;
  // this->~App();
}

App::App(Gen::Vec2<float> dimensions)
  : AppDimension(dimensions)
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    Gen::print(std::cerr, "SDL CANNOT OUTPUT VIDEO, SDL ERROR: ", SDL_GetError(), '\n');
    exit(-1);
  }

  window = SDL_CreateWindow("Conways Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            (int)dimensions.x, (int)dimensions.y, SDL_WINDOW_SHOWN);
  if(window == nullptr){
    Gen::print(std::cerr, "SDL CANNOT CREATE WINDOW, SDL ERROR: ", SDL_GetError(), '\n');
    exit(-1); 
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == nullptr){
    Gen::print(std::cerr, "SDL CANNOT CREATE RENDERER, SDL ERROR: ", SDL_GetError(), '\n');
    exit(-1); 
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // WHITE

  SDL_RenderClear(renderer);
}

void App::run(){
  // While loop goes here and so does the inits of the different components
  // like generating the drawable window
  // the black cubes etc
  Gen::print("We are running now\n");

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  block.makeBlock(getDimensions() / 2.f);
  SDL_RenderFillRect(renderer, &block.rect);

  bool quit{false};
  while(!quit){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT) quit = true;
    }
    // TODO: issues iguess
    block.move(1);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

Gen::Vec2<float> App::getDimensions()const{return AppDimension;}
