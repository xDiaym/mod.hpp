#pragma once
#include <optional>
#include <numeric>
#include <cassert>

#define NOTREACHED() assert(false && "Can't be reached");

namespace mod {

template <typename T, T mod_>
class Mod {
  static_assert(!std::is_reference_v<T>, "Reference types are not supported");

 public:
  using Self = Mod<T, mod_>;

  constexpr Mod(T val) : value_(val % mod_) {
  }

  constexpr Self operator+(const Self& other) {
    return {value_ + other.value_};
  }

  constexpr Self operator-(const Self& other) {
    return {value_ - other.value_};
  }

  constexpr Self operator*(const Self& other) {
    return {value_ * other.value_};
  }

  constexpr Self operator/(const Self& other) {
    return {value_ / other.value_};
  }

  constexpr Self operator%(const Self& other) {
    return {value_ % other.value_};
  }

  constexpr Self& operator+=(const Self& other) {
    value_ = (value_ + other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator-=(const Self& other) {
    value_ = (value_ - other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator*=(const Self& other) {
    value_ = (value_ * other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator/=(const Self& other) {
    value_ = (value_ / other.value_) % mod_;
    return *this;
  }

  constexpr Self& operator%=(const Self& other) {
    value_ = (value_ / other.value_) % mod_;
    return *this;
  }

  template <typename U>  // TODO: concept
  std::strong_ordering operator<=>(U other) {
    return value_.operator<=>(other);
  }

  constexpr operator T() const noexcept {
    return value_;
  }

  constexpr T Value() const noexcept {
    return value_;
  }

  // Use optimal algo
  constexpr std::optional<Self> Inverse() const noexcept {
    if (std::gcd(value_, mod_) != 1)
      return std::nullopt;
    for (int i = 1; i < mod_; ++i) {
      auto val = Self(value_ * i);
      if (val == 1)
        return Self(i);
    }
    NOTREACHED();
  }

 private:
  T value_;
};

}  // namespace mod
