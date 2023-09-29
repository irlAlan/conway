#include <iostream>
#include <Conway/App.hpp>

int main(int argc, char **argv){
  App *Conway{App::GetInstance({1200.f, 800.f})};
  Conway->run();
  Conway->DestroyApp();

  return 0;
}



// Generic print functions so i dont need to keep calling std::cout/cerr
// template<typename ...T>
// void print(const T &...args){
//   auto printArg{[](const auto &arg){std::cout << arg;}};
//   (printArg(args), ...);
// }
// template<typename ...T>
// void print(std::ostream &out, const T &...args){
//   auto printArg{[&out](const auto &arg){out << arg;}};
//   (printArg(args), ...);
// }
// 
// 
// constexpr int WIDTH{1200};
// constexpr int HEIGHT{800};
// 
// int main(int argc, char **argv){
// 
//   SDL_Window *window{nullptr};
//   SDL_Surface *screen_surface{nullptr};
// 
//   if(SDL_Init(SDL_INIT_VIDEO) < 0){
//     print(std::cerr, "SDL CANNOT OUTPUT VIDEO, SDL ERROR: ", SDL_GetError(), '\n');
//     exit(-1);
//   }
// 
//   window = SDL_CreateWindow("Conways Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//   if(window == nullptr){
//     print(std::cerr, "SDL CANNOT CREATE WINDOW, SDL ERROR: ", SDL_GetError(), '\n');
//     exit(-1); 
//   }
//   screen_surface = SDL_GetWindowSurface(window);
//   if(screen_surface == nullptr){
//     print(std::cerr, "SDL CANNOT CREATE SCREEN SURFACE, SDL ERROR: ", SDL_GetError(), '\n');
//     exit(-1); 
//   }
// 
//   SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
//   SDL_UpdateWindowSurface(window);
// 
//   SDL_Event event;
//   bool quit{false};
//   while(!quit){
//     while(SDL_PollEvent(&event)){
//       if(event.type == SDL_QUIT) quit = true;
//     }
//   }
// 
//   SDL_DestroyWindow(window);
//   SDL_Quit();
//   return 0;
// }
