#pragma once

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  template<class Type>
  struct Type3
  {
    Type x, y, z;
  public:
    Type3() = default;

    constexpr Type3(Type _x, Type _y, Type _z)
      : x(_x)
      , y(_y)
      , z(_z) {}

    constexpr Type3(Type _xyz)
      : x(_xyz)
      , y(_xyz)
      , z(_xyz) {}

    template<class X, class Y, class Z>
    constexpr Type3(X _x, Y _y, Z _z)
      : x(static_cast<Type>(_x))
      , y(static_cast<Type>(_y))
      , z(static_cast<Type>(_z)) {}

    template<class T>
    constexpr Type3(const Type3<T>& _v)
      : x(static_cast<Type>(_v.x))
      , y(static_cast<Type>(_v.y))
      , z(static_cast<Type>(_v.z)) {}
  public:
    constexpr bool operator==(const Type3& _v)const { return x == _v.x && y == _v.y && z == _v.z; }

    constexpr bool operator!=(const Type3& _v)const { return !(*this == _v); }

    constexpr Type3 operator+()const { return *this; }

    constexpr Type3 operator-()const { return{ -x, -y, -z }; }

    constexpr Type3 operator+(const Type3& _v)const { return{ x + _v.x, y + _v.y, z + _v.z }; }

    constexpr Type3 operator-(const Type3& _v)const { return{ x - _v.x, y - _v.y, z - _v.z }; }

    constexpr Type3 operator*(const Type3& _v)const { return{ x * _v.x, y * _v.y, z * _v.z }; }

    constexpr Type3 operator/(const Type3& _v)const { return{ x / _v.x, y / _v.y, z / _v.z }; }

    const Type3& operator=(const Type3& _v)
    {
      x = _v.x;
      y = _v.y;
      z = _v.z;

      return *this;
    }

    const Type3& operator+=(const Type3& _v)
    {
      x += _v.x;
      y += _v.y;
      z += _v.z;

      return *this;
    }

    const Type3& operator-=(const Type3& _v)
    {
      x -= _v.x;
      y -= _v.y;
      z -= _v.z;

      return *this;
    }

    const Type3& operator*=(const Type3& _v)
    {
      x *= _v.x;
      y *= _v.y;
      z *= _v.z;

      return *this;
    }

    const Type3& operator/=(const Type3& _v)
    {
      x /= _v.x;
      y /= _v.y;
      z /= _v.z;

      return *this;
    }
  };

  using int3 = Type3<int>;
  using float3 = Type3<float>;
}
