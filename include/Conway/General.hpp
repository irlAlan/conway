#include <iostream>

#ifndef GENERAL_HPP
#define GENERAL_HPP

// For function declerations
namespace Gen{
// Generic print functions so i dont need to keep calling std::cout/cerr
  template<typename ...T>
  void print(const T &...args);

  template<typename ...T>
  void print(std::ostream &out, const T &...args);
}

// for struct declerations
namespace Gen {
  template<typename T> 
  struct Vec2{
    T x; T y;
  };
}

#endif // GENERAL_HPP
