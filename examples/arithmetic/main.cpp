#include <iostream>
#include <ostream>
#include <include/mod.hpp>

template <int S>
using IMod = mod::Mod<int, S>;
using IMod256 = IMod<256>;

template <typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> opt) {
  if (opt)
    os << "Some(" << opt.value() << ")";
  else
    os << "None";
  return os;
}

int main() {
  using namespace mod;
  auto a = IMod256(7);
  std::cout << Pow(a, 1024) << '\n' << a.Inverse() << '\n';
}