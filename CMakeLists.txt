cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(conway)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-Wall" "-g")

include_directories(${CMAKE_SOURCE_DIR}/include)

# file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
# file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)

include(FetchContent)

FetchContent_Declare(
   SDL2
   GIT_REPOSITORY  https://github.com/libsdl-org/SDL
   GIT_TAG         release-2.28.3
   GIT_PROGRESS    TRUE
)
FetchContent_MakeAvailable(SDL2)
set(SDL_LIBRARIES ${SDL_LIBRARIES} SDL2main SDL2-static)

# add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
add_executable(${PROJECT_NAME} "./src/main.cpp" "./src/Block.cpp" "./src/App.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL_LIBRARIES})
