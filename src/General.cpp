#include <Conway/General.hpp>

// for function defenitions
namespace  Gen{
  template<typename ...T>
  void print(const T &...args){
    auto printArg{[](const auto &arg){std::cout << arg;}};
    (printArg(args), ...);
  }
  template<typename ...T>
  void print(std::ostream &out, const T &...args){
    auto printArg{[&out](const auto &arg){out << arg;}};
    (printArg(args), ...);
  }
}
