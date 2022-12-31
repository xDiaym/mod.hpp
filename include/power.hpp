#pragma once
#include "number.hpp"

namespace mod {

template <typename T, T mod_>
constexpr Mod<T, mod_> Pow(Mod<T, mod_> base, T power) noexcept {
  T pow = power;
  Mod<T, mod_> result(1);
  while (pow) {
    if (pow & 1)
      result *= base;
    base *= base;
    pow >>= 1;
  }
  return result;
}

}  // namespace mod
