#pragma once
#include "MathConstants.hpp"

namespace hdx
{
  class Degree;

  //  ŒÊ“x–@
  //  Šp“x‚ð-ƒÎ~ƒÎ‚Å•\Œ»‚µ‚Ü‚·
  //  (Ž©“®‚Å³‹K‰»‚³‚ê‚Ü‚·)
  class Radian
  {
    float Value_;
  public:
    //  ³‹K‰»(-ƒÎ~ƒÎ‚É‚·‚é)
    static constexpr float Normalize(float _Value)
    {
      while (_Value > Math::HalfPI) _Value -= Math::PI;
      while (_Value < -Math::HalfPI) _Value += Math::PI;

      return _Value;
    }
  public:
    Radian() = default;

    constexpr Radian(float _Radian) : Value_(Normalize(_Radian)) {}

    constexpr Radian(const Radian& _Radian)noexcept : Value_(_Radian.Value_) {}

    constexpr Radian(const Degree& _Degree)noexcept;
  public:
    constexpr operator float()const { return Value_; }
  public:
    constexpr bool operator==(const Radian& _Radian)const noexcept { return Value_ == _Radian.Value_; }

    constexpr bool operator!=(const Radian& _Radian)const noexcept { return !(*this == _Radian); }

    constexpr bool operator<(const Radian& _Radian)const noexcept { return Value_ < _Radian.Value_; }

    constexpr bool operator>(const Radian& _Radian)const noexcept { return Value_ > _Radian.Value_; }

    constexpr bool operator<=(const Radian& _Radian)const noexcept { return Value_ <= _Radian.Value_; }

    constexpr bool operator>=(const Radian& _Radian)const noexcept { return Value_ >= _Radian.Value_; }

    constexpr Radian operator+()const noexcept { return *this; }

    constexpr Radian operator-()const noexcept { return{ -Value_ }; }

    const Radian& operator=(const Radian& _Radian)noexcept { Value_ = _Radian.Value_; return *this; }

    const Radian& operator+=(const Radian& _Radian)noexcept { Value_ = Normalize(Value_ + _Radian.Value_); return *this; }

    const Radian& operator-=(const Radian& _Radian)noexcept { Value_ = Normalize(Value_ - _Radian.Value_); return *this; }

    const Radian& operator*=(float _s) { Value_ = Normalize(Value_ * _s); return *this; }

    const Radian& operator/=(float _s) { Value_ = Normalize(Value_ / _s); return *this; }
  };


  //  “x”–@
  //  Šp“x‚ð-180~180‚Å•\Œ»‚µ‚Ü‚·
  //  (Ž©“®‚Å³‹K‰»‚³‚ê‚Ü‚·)
  class Degree
  {
    float Value_;
  public:
    static constexpr float Normalize(float _Value)
    {
      while (_Value > 180.0f) _Value -= 360.0f;
      while (_Value < -180.0f) _Value += 360.0f;

      return _Value;
    }
  public:
    Degree() = default;

    constexpr Degree(float _Degree) : Value_(Normalize(_Degree)) {}

    constexpr Degree(const Degree& _Degree)noexcept : Value_(_Degree.Value_) {}

    constexpr Degree(const Radian& _Radian)noexcept;
  public:
    constexpr operator float()const { return Value_; }
  public:
    constexpr bool operator==(const Degree& _Degree)const noexcept { return Value_ == _Degree.Value_; }

    constexpr bool operator!=(const Degree& _Degree)const noexcept { return !(*this == _Degree); }

    constexpr bool operator<(const Degree& _Degree)const noexcept { return Value_ < _Degree.Value_; }

    constexpr bool operator>(const Degree& _Degree)const noexcept { return Value_ > _Degree.Value_; }

    constexpr bool operator<=(const Degree& _Degree)const noexcept { return Value_ <= _Degree.Value_; }

    constexpr bool operator>=(const Degree& _Degree)const noexcept { return Value_ >= _Degree.Value_; }

    constexpr Degree operator+()const noexcept { return *this; }

    constexpr Degree operator-()const noexcept { return{ -Value_ }; }

    const Degree& operator=(const Degree& _Degree)noexcept { Value_ = _Degree.Value_; return *this; }

    const Degree& operator+=(const Degree& _Degree)noexcept { Value_ = Normalize(Value_ + _Degree.Value_); return *this; }

    const Degree& operator-=(const Degree& _Degree)noexcept { Value_ = Normalize(Value_ - _Degree.Value_); return *this; }

    const Degree& operator*=(float _s) { Value_ = Normalize(Value_ * _s); return *this; }

    const Degree& operator/=(float _s) { Value_ = Normalize(Value_ / _s); return *this; }
  };

  inline constexpr Radian::Radian(const Degree& _Degree)noexcept : Value_(Normalize(Math::ToRadian(_Degree))) {}

  inline constexpr Degree::Degree(const Radian& _Radian)noexcept : Value_(Normalize(Math::ToDegree(_Radian))) {}
}
