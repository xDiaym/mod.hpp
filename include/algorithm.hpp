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

// https://e-maxx.ru/algo/extended_euclid_algorithm
constexpr int gcdex(int a, int b, int& x, int& y) noexcept {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }
  int x1, y1;
  int d = gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

}  // namespace mod
