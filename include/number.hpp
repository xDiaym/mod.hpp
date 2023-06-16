#pragma once
#include <optional>
#include <numeric>
#include <cassert>

namespace mod {

template <typename T, T mod_>
class Mod;

template <typename T, T mod_>
constexpr std::optional<Mod<T, mod_>> Inverse(Mod<T, mod_> val) noexcept;

template <typename T, T mod_>
constexpr std::optional<T> Inverse(T val) noexcept;

}

namespace mod {

template <typename T, T mod_>
class Mod {
  static_assert(std::is_integral_v<T>, "T must be integral type");
  static_assert(mod_ > 1, "mod_ must be >= 0");
  static_assert(mod_ <= std::numeric_limits<T>::max(),
    "mod_ cant be greater than std::numeric_limits<T>::max()");
  static_assert(!std::is_reference_v<T>, "Reference types are not supported");

 public:
  using Self = Mod<T, mod_>;

  constexpr Mod(T val) : value_(val % mod_) {
    if constexpr (std::is_signed_v<T>) {
      // FIXME: Can avoid branching
      if (value_ < 0)
        value_ += mod_;
    }
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

  constexpr std::optional<Self> operator/(const Self& other) const noexcept {
    auto inv = Inverse(other.value_);
    if (!inv)
      return std::nullopt;
    return {value_ * inv};
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

  constexpr std::optional<Self&> operator/=(const Self& other) noexcept {
    auto inv = Inverse(other.value_);
    if (!inv)
      return std::nullopt;
    value_ *= inv;
    return {*this};
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

 private:
  T value_;
};

}  // namespace mod
