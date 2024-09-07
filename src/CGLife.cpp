#include <CGLife/CGLife.h>
#include <CGLife/Pixel.h>
#include <CGLife/Util.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <imgui.h>

#include <memory>

#include "fmt/base.h"

// TODO: Add imgui support later

// #include "imgui.h"
// #include <imgui/backends/imgui_impl_sdl2.h>
// #include <imgui/backends/imgui_impl_sdlrenderer2.h>

CGLife::CGLife(std::string_view title, Util::Vec2i seed)
    : title(title), backCol({0xff, 0xff, 0xff}) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fmt::println(fmt::format("Cannot init video: %s", SDL_GetError()));
    std::exit(-1);
  }

  window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, winDimensions.x,
                            winDimensions.y, SDL_WINDOW_SHOWN);
  if (!window) {
    fmt::println(fmt::format("Cannot create sdl window: %s", SDL_GetError()));
    std::exit(-1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    fmt::println(fmt::format("Cannot create renderer: %s", SDL_GetError()));
    std::exit(-1);
  }
  SDL_RenderSetLogicalSize(renderer, winDimensions.x, winDimensions.y);

  // use the seed to randomly generate alive pixels
  int randx{(seed.x / winDimensions.x) / 10};
  int randy{(seed.y / winDimensions.y) / 10};
  fmt::println(fmt::format("randx {}, randy {}", randx, randy));
  int row{0};
  int column{0};
  for (auto &val : pxls) {
    for (auto &p : val) {
      p = std::unique_ptr<Pixel>(
          new Pixel({row * 10, column * 10}, PixelState::Dead));
      if (column == winDimensions.y)
        column = 0;
      if (row == winDimensions.x)
        row = 0;

      column += 1;
    }
    row += 1;
  }
  // default start for pixels
  // TODO: do bounds checking and wrap around
  pxls[randy][randx]->setState(PixelState::Alive);
  Util::Pos joinedPos{randx + 600, randy};
  if (joinedPos.x + 1 > winDimensions.x) {
    joinedPos.x -= (winDimensions.x + 1);
  } else if (joinedPos.x - 1 < 0) {
    joinedPos.x += (winDimensions.x - 1);
  }
  if (joinedPos.y + 1 > winDimensions.y) {
    joinedPos.y -= (winDimensions.y + 1);
  } else if (joinedPos.y - 1 < 0) {
    joinedPos.y += (winDimensions.y - 1);
  }
  pxls[joinedPos.y - 1][joinedPos.x]->setState(PixelState::Alive);
  pxls[joinedPos.y][joinedPos.x - 1]->setState(PixelState::Alive);
}

CGLife::~CGLife() {
  // delete pxls;
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void CGLife::run() {
  // where the loop happens
  bool mouseActive{false};
  bool shouldRun{false};
  bool quit{false};

  while (!quit) {

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEMOTION:
        mousePos.x = event.motion.x;
        mousePos.y = event.motion.y;
        if (!mouseActive)
          mouseActive = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          Util::Pos pos{mousePos.x / 10, mousePos.y / 10};
          // fmt::println("Left click at: {},{}", pos.x, pos.y);
          if(pxls[pos.x][pos.y]->getState() == "Alive"){ 
            pxls[pos.x][pos.y]->setState(PixelState::Dead);
          }else{
            pxls[pos.x][pos.y]->setState(PixelState::Alive);
          }
          break;
        }
        if(event.button.button == SDL_BUTTON_RIGHT){
            shouldRun = !shouldRun;
          }
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouseHover)
          mouseHover = true;
        else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouseHover)
          mouseHover = false;
        break;
      default:
        break;
      }
    }

    Uint32 start_time, end_time;
    float fps;

    start_time = SDL_GetTicks();
    draw();
    if(shouldRun){
      update(1.0f / 60.0f);
      //SDL_Delay(500);
    }
    end_time = SDL_GetTicks()-start_time;
    fps = (end_time > 0) ? 1000.0f / end_time : 0.0f;
   // fmt::println(fmt::format("fps: {}", fps));
  }
}

void CGLife::update(float dt) {
  int count{0};
  // where all the update stuff happens
  // 1. get current pixels to check state of other pixels

  // current live pixel
  // Pixel *currentLivePixel{nullptr};

  // load mao with each pixel position
  // go through positions checking the bounds and updating the count (value)
  // compare the count and change  state accordingly
  // std::map<Util::Pos, int> map;
  for (auto &val : pxls) {
    for (auto &px : val) {
      // for each pixel i check its neighbours
      //   x
      // x o x
      //   x
      // Rules:
      //  -> 1. Any live cell with fewer than 2 live neighbours dies
      //  -> 2. Any live cell with 2 or 3 live neighbours lives
      //  -> 3. Any live cell with more than 3 live neighbours dies
      //  -> 4. Any dead cell with exactly 3 live neighbours becomes live

      // if(pxls[row][column]->getState() == "Alive"){
      //   currentLivePixel = pxls[row][column].get();
      // }
      // everything is set
      // Util::Pos up{boundsCheck({row-1,column})};
      // Util::Pos down{boundsCheck({row+1,column})};
      // Util::Pos left{boundsCheck({row,column-1})};
      // Util::Pos right{boundsCheck({row,column+1})};
      //// fmt::println(fmt::format("up: ({},{}), Down: ({},{}), Left: ({},{}),
      /// Right: ({},{})",
      /// up.x,up.y,down.x,down.y,left.x,left.y,right.x,right.y)); / NOTE:
      /// doesnt check diagonals
      // if(pxls[row][column]->getState() == "Alive"
      //   && pxls[down.x][down.y]->getState() == "Alive"
      //   && pxls[up.x][up.y]->getState() == "Alive"
      //   && pxls[left.x][left.y]->getState() == "Alive"
      //   && pxls[right.x][right.y]->getState() == "Alive"
      //){
      //   pxls[row][column]->setState(PixelState::Dead);
      // }

      // Rules:
      //  -> 1. Any live cell with fewer than 2 live neighbours dies
      //  -> 2. Any live cell with 2 or 3 live neighbours lives
      //  -> 3. Any live cell with more than 3 live neighbours dies
      //  -> 4. Any dead cell with exactly 3 live neighbours becomes live

      count = checkNeighbour(px->getPos());
      fmt::println(fmt::format("Count: {}", count));
     //if (px->getState() == "Alive" && (count >= 4 || count <2)) {
     //  // alive and has 3 or more alive neighbours so it dies
     //  px->setState(PixelState::Dead);
     //}
     //if (px->getState() == "Alive" && (count == 3)) {
     //  // alive and has 2 or 3 alive neighbours so it stays alive
     //  px->setState(PixelState::Alive);
     //}
     //if (px->getState() == "Dead" && (count == 3 || 2)) {
     //  // dead and has 3 alive neighbours so it stays alive
     //  px->setState(PixelState::Alive);
     //}
     //if (px->getState() == "Alive" && count < 2) {
     //  // dead and has < 2 alive neighbours so it dies
     //  px->setState(PixelState::Dead);
     //}
      //if (px->getState() == "Dead" && checkNeighbour(px->getPos()) == 3) {
      //  // dead and has < 2 alive neighbours so it dies
      //  px->setState(PixelState::Alive);
      //}
      // SDL_Delay(500);
      // if(pxls[row][column]->getState() == "Alive"){
      //  std::cout << *(pxls[row][column]) << "\n";
      //}
     // count = 0;
    }
  }
}

void CGLife::draw() {
  SDL_SetRenderDrawColor(renderer, backCol.r, backCol.g, backCol.b, backCol.a);
  SDL_RenderClear(renderer);

  // loop through the 2d Vec pixels
  for (auto &px_arr : pxls) {
    for (auto &px : px_arr) {
      px->draw(renderer);
      // std::cout << *px;
      // SDL_Delay(50);
    }
  }

  SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xcc);

  // print out the grid
  for (int x{0}; x < winDimensions.x * 10; x += 10) {
    SDL_RenderDrawLine(renderer, x, 0, x, winDimensions.y);
  }
  for (int y{0}; y < winDimensions.y * 10; y += 10) {
    SDL_RenderDrawLine(renderer, 0, y, winDimensions.x, y);
  }

  SDL_RenderPresent(renderer);
}

int CGLife::checkNeighbour(const Util::Pos &pos) {
  int count{0};

  //    x
  //  x o x
  //    x

  // up = boundsCheck({(row - 1)/10, column/10});
  // down = boundsCheck({(row + 1)/10, column/10});
  // left = boundsCheck({row/10, (column - 1)/10});
  // right = boundsCheck({row/10, (column + 1)/10});

  Util::Pos up = boundsCheck({(pos.x - 1) / 10, pos.y / 10});
  Util::Pos down = boundsCheck({(pos.x + 1) / 10, pos.y / 10});
  Util::Pos left = boundsCheck({pos.x / 10, (pos.y - 1) / 10});
  Util::Pos right = boundsCheck({pos.x / 10, (pos.y + 1) / 10});

  Util::Pos diagul = boundsCheck({(pos.x - 1)/10, (pos.y-1)/10}); // up right
  Util::Pos diagur = boundsCheck({(pos.x + 1)/10, (pos.y-1)/10}); // up left
  Util::Pos diagdl = boundsCheck({(pos.x-1)/10, (pos.y + 1)/10}); // down left
  Util::Pos diagdr = boundsCheck({(pos.x+1)/10, (pos.y + 1)/10}); // down right

  if (pxls[down.x][down.y]->getState() == "Alive")
    count += 1;
  if (pxls[up.x][up.y]->getState() == "Alive")
    count += 1;
  if (pxls[left.x][left.y]->getState() == "Alive")
    count += 1;
  if (pxls[right.x][right.y]->getState() == "Alive")
    count += 1;

  if (pxls[diagul.x][diagul.y]->getState() == "Alive")
    count += 1;
  if (pxls[diagur.x][diagur.y]->getState() == "Alive")
    count += 1;
  if (pxls[diagdl.x][diagdl.y]->getState() == "Alive")
    count += 1;
  if (pxls[diagdr.x][diagdr.y]->getState() == "Alive")
    count += 1;

  //fmt::println(fmt::format("Count: {}", count));
  return count;
}

Util::Pos CGLife::boundsCheck(const Util::Pos &p) {
  Util::Pos pos{p};
  // width
  if (pos.x + 1 > winDimensions.x) {
    // too far right
    pos.x -= (winDimensions.x + 1);
  } else if (pos.x - 1 < 0) {
    pos.x += (winDimensions.x - 1);
  }
  // height
  if (pos.y + 1 > winDimensions.y) {
    pos.y -= (winDimensions.y + 1);
  } else if (pos.y - 1 < 0) {
    pos.y += (winDimensions.y - 1);
  }
  return pos;
}

// should be /
Util::Pos CGLife::worldToArrIndex(int row, int column) {
  return {row * 10, column * 10};
}
