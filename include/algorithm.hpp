#pragma once
#include "number.hpp"

namespace mod {

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T, T mod_> requires Integral<T>
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
template <Integral T>
constexpr T gcdex(T a, T b, T& x, T& y) noexcept {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }
  T x1, y1;
  T d = gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

template <typename T, T mod_> requires Integral<T>
constexpr std::optional<Mod<T, mod_>> Inverse(Mod<T, mod_> val) noexcept {
  T x, y;
  T g = gcdex(val.Value(), mod_, x, y);
  if (g != 1)
    return std::nullopt;
  return {Mod<T, mod_>(x)};
}

template <typename T, T mod_> requires Integral<T>
constexpr std::optional<T> Inverse(T val) noexcept {
  std::optional<Mod<T, mod_>> inv = Inverse(Mod<T, mod_>(val));
  if (!inv)
    return std::nullopt;
  return inv.value().Value();
}

}  // namespace mod
