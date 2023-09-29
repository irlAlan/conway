#include <iostream>

#ifndef GENERAL_HPP
#define GENERAL_HPP

// For function declerations
namespace Gen{
// Generic print functions so i dont need to keep calling std::cout/cerr
  template<typename ...T>
  void print(const T &...args){
    auto printArg{
      [](const auto &arg){std::cout << arg;}
    };
    (printArg(args), ...);
  }

  template<typename ...T>
  void print(std::ostream &out, const T &...args){
    auto printArg{
      [&out](const auto &arg){out << arg;}
    };
    (printArg(args), ...);
  }
}

// for struct declerations
namespace Gen {
  template<typename T> 
  struct Vec2{
    T x; T y;
  };
}

#endif // GENERAL_HPP
