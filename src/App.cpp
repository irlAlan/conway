#include <Conway/App.hpp>
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
  screen_surface = SDL_GetWindowSurface(window);
  if(screen_surface == nullptr){
    Gen::print(std::cerr, "SDL CANNOT CREATE SCREEN SURFACE, SDL ERROR: ", SDL_GetError(), '\n');
    exit(-1); 
  }

  SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
  SDL_UpdateWindowSurface(window);
}

void App::run(){
  // While loop goes here and so does the inits of the different components
  // like generating the drawable window
  // the black cubes etc
  Gen::print("We are running now\n");
}
