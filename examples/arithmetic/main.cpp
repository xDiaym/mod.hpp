#include <iostream>
#include <include/mod.hpp>

template <int S>
using IMod = mod::Mod<int, S>;
using IMod256 = IMod<256>;

int main() {
    using namespace mod;
    auto a = IMod256(3);
    std::cout << Pow(a, 1024).Value() << '\n'
              << a.Inverse().value() << '\n';
}