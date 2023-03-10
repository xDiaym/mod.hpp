#pragma once
#include <optional>
#include <numeric>
#include <cassert>

namespace mod {
  constexpr int gcdex(int, int, int&, int&) noexcept;
}

namespace mod {

template <typename T, T mod_>
class Mod {
  static_assert(!std::is_reference_v<T>, "Reference types are not supported");

 public:
  using Self = Mod<T, mod_>;

  constexpr Mod(T val) : value_(val % mod_) {
  }

  constexpr Self operator+(const Self& other) const noexcept {
    return {value_ + other.value_};
  }

  constexpr Self operator-(const Self& other) const noexcept {
    return {value_ - other.value_};
  }

  constexpr Self operator*(const Self& other) const noexcept {
    return {value_ * other.value_};
  }

  constexpr Self operator/(const Self& other) const noexcept {
    return {value_ / other.value_};
  }

  constexpr Self operator%(const Self& other) const noexcept {
    return {value_ % other.value_};
  }

  constexpr Self& operator+=(const Self& other) noexcept {
    value_ = (value_ + other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator-=(const Self& other) noexcept {
    value_ = (value_ - other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator*=(const Self& other) noexcept {
    value_ = (value_ * other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator/=(const Self& other) noexcept {
    value_ = (value_ / other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator%=(const Self& other) noexcept {
    value_ = (value_ / other.value_) % mod_;
    return *this;
  }

  template <typename U>
  auto operator<=>(U other) const noexcept {
    return value_ <=> other;
  }

  constexpr operator T() const noexcept {
    return value_;
  }

  constexpr T Value() const noexcept {
    return value_;
  }

  constexpr T GetMod() const noexcept {
    return mod_;
  }

  constexpr std::optional<Self> Inverse() const noexcept {
    int x, y;
    T g = gcdex(value_, mod_, x, y);
    if (g != 1)
      return std::nullopt;
    return Self(x % mod_ + mod_);
  }

 private:
  T value_;
};

}  // namespace mod
