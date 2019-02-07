#pragma once

namespace hdx
{
  template<class Type>
  struct Type4
  {
    Type x, y, z, w;
  public:
    Type4() = default;

    constexpr Type4(Type _x, Type _y, Type _z, Type _w)
      : x(_x)
      , y(_y)
      , z(_z)
      , w(_w) {}

    constexpr Type4(Type _xyzw)
      : x(_xyzw)
      , y(_xyzw)
      , z(_xyzw)
      , w(_xyzw) {}

    template<class X, class Y, class Z, class W>
    constexpr Type4(X _x, Y _y, Z _z, W _w)
      : x(static_cast<Type>(_x))
      , y(static_cast<Type>(_y))
      , z(static_cast<Type>(_z))
      , w(static_cast<Type>(_w)) {}

    template<class T>
    constexpr Type4(const Type4<T>& _v)
      : x(static_cast<Type>(_v.x))
      , y(static_cast<Type>(_v.y))
      , z(static_cast<Type>(_v.z))
      , w(static_cast<Type>(_v.w)) {}
  public:
    constexpr bool operator==(const Type4& _v)const { return x == _v.x && y == _v.y && z == _v.z && w == _v.w; }

    constexpr bool operator!=(const Type4& _v)const { return !(*this == _v); }

    constexpr Type4 operator+()const { return *this; }

    constexpr Type4 operator-()const { return{ -x, -y, -z, -w }; }

    constexpr Type4 operator+(const Type4& _v)const { return{ x + _v.x, y + _v.y, z + _v.z, w + _v.w }; }

    constexpr Type4 operator-(const Type4& _v)const { return{ x - _v.x, y - _v.y, z - _v.z, w - _v.w }; }

    constexpr Type4 operator*(const Type4& _v)const { return{ x * _v.x, y * _v.y, z * _v.z, w * _v.w }; }

    constexpr Type4 operator/(const Type4& _v)const { return{ x / _v.x, y / _v.y, z / _v.z, w / _v.w }; }

    const Type4& operator=(const Type4& _v)
    {
      x = _v.x;
      y = _v.y;
      z = _v.z;
      w = _v.w;

      return *this;
    }

    const Type4& operator+=(const Type4& _v)
    {
      x += _v.x;
      y += _v.y;
      z += _v.z;
      w += _v.w;

      return *this;
    }

    const Type4& operator-=(const Type4& _v)
    {
      x -= _v.x;
      y -= _v.y;
      z -= _v.z;
      w -= _v.w;

      return *this;
    }

    const Type4& operator*=(const Type4& _v)
    {
      x *= _v.x;
      y *= _v.y;
      z *= _v.z;
      w *= _v.w;

      return *this;
    }

    const Type4& operator/=(const Type4& _v)
    {
      x /= _v.x;
      y /= _v.y;
      z /= _v.z;
      w /= _v.w;

      return *this;
    }
  };

  using int4 = Type4<int>;
  using float4 = Type4<float>;
}
