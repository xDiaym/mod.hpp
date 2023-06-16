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
  auto a = IMod256(257);
  std::cout << "257 - 2 = " << a - IMod256(2) << " (mod 256)" << '\n';
  std::cout << "2 * " << Inverse<int, 5>(2) << " = 1 (mod 5)\n";
  std::cout << "257 ^ 1024 = " << Pow(a, 1024) << " (mod 256)\n"
            << "257 ^ -1   = " << Inverse(a)   << " (mod 256)\n";
}
