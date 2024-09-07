cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(conway)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_definitions("-Wall" "-g")

include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(${CMAKE_SOURCE_DIR}/libs)

file(GLOB imgui_src ${CMAKE_SOURCE_DIR}/imgui/*.cpp)
file(GLOB imgui_headers ${CMAKE_SOURCE_DIR}/includes/imgui/*.h)
# file(GLOB imgui_renderheaders ${CMAKE_SOURCE_DIR}/libs/imgui/backends/*.h)
# file(GLOB imgui_rendersrc ${CMAKE_SOURCE_DIR}/libs/imgui/backends/*.cpp)

find_package(SDL2 REQUIRED)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 11.0.2
)
FetchContent_MakeAvailable(fmt)
# TODO: sort out imgui late
add_executable(${PROJECT_NAME}
  src/main.cpp 
  ./src/Pixel.cpp
  ./src/CGLife.cpp

  # imgui 
  # ${imgui_src}
  # ./libs/imgui/backends/imgui_impl_sdl2.cpp
  # ./libs/imgui/backends/imgui_impl_sdlrenderer2.cpp
  # ./libs/imgui/backends/imgui_impl_sdlrenderer2.h 
  # ./libs/imgui/backends/imgui_impl_sdl2.h
  # ${imgui_headers}

  ./includes/CGLife/Util.h
  ./includes/CGLife/Pixel.h
  ./includes/CGLife/CGLife.h
)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt ${SDL2_LIBRARIES})
