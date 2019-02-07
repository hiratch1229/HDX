#pragma once

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  template<class Type>
  struct Type2
  {
    Type x, y;
  public:
    Type2() = default;

    constexpr Type2(Type _x, Type _y)
      : x(_x)
      , y(_y) {}

    constexpr Type2(Type _xy)
      : x(_xy)
      , y(_xy) {}

    template<class X, class Y>
    constexpr Type2(X _x, Y _y)
      : x(static_cast<Type>(_x))
      , y(static_cast<Type>(_y)) {}

    template<class T>
    constexpr Type2(const Type2<T>& _v)
      : x(static_cast<Type>(_v.x))
      , y(static_cast<Type>(_v.y)) {}
  public:
    constexpr bool operator==(const Type2& _v)const { return x == _v.x && y == _v.y; }

    constexpr bool operator!=(const Type2& _v)const { return !(*this == _v); }

    constexpr Type2 operator+()const { return *this; }

    constexpr Type2 operator-()const { return{ -x, -y }; }

    constexpr Type2 operator+(const Type2& _v)const { return{ x + _v.x, y + _v.y }; }

    constexpr Type2 operator-(const Type2& _v)const { return{ x - _v.x, y - _v.y }; }

    constexpr Type2 operator*(const Type2& _v)const { return{ x * _v.x, y * _v.y }; }

    constexpr Type2 operator/(const Type2& _v)const { return{ x / _v.x, y / _v.y }; }

    const Type2& operator=(const Type2& _v)
    {
      x = _v.x;
      y = _v.y;

      return *this;
    }

    const Type2& operator+=(const Type2& _v)
    {
      x += _v.x;
      y += _v.y;

      return *this;
    }

    const Type2& operator-=(const Type2& _v)
    {
      x -= _v.x;
      y -= _v.y;

      return *this;
    }

    const Type2& operator*=(const Type2& _v)
    {
      x *= _v.x;
      y *= _v.y;

      return *this;
    }

    const Type2& operator/=(const Type2& _v)
    {
      x /= _v.x;
      y /= _v.y;

      return *this;
    }
  };

  using int2 = Type2<int>;
  using float2 = Type2<float>;
}
