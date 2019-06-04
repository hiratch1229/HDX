#pragma once
#include "Fwd.hpp"

#include <cmath>
#include <string>
#include <fstream>

#define ARITHMETIC_OPERATOR(Operator)\
template<class T>\
[[nodiscard]] constexpr auto operator##Operator(const Type4<T>& _v)const->Type4<decltype(std::declval(x Operator _v.x))>\
{\
  return{ x Operator _v.x, y Operator _v.y, z Operator _v.z, w Operator _v.w };\
}\
template<class T>\
[[nodiscard]] constexpr auto operator##Operator(T _s)const->Type4<decltype(std::declval(x Operator _s))>\
{\
  return{ x Operator _s, y Operator _s, z Operator _s, w Operator _s };\
}\

#define ASSIGNMENT_OPERATOR(Operator)\
template<class T>\
Type4& operator##Operator(const Type4<T>& _v)\
{\
  x Operator static_cast<Type>(_v.x);\
  y Operator static_cast<Type>(_v.y);\
  z Operator static_cast<Type>(_v.z);\
  w Operator static_cast<Type>(_v.w);\
  \
  return *this;\
}\
template<class T>\
Type4& operator##Operator(T _s)\
{\
  x Operator static_cast<Type>(_s);\
  y Operator static_cast<Type>(_s);\
  z Operator static_cast<Type>(_s);\
  w Operator static_cast<Type>(_s);\
  \
  return *this;\
}\

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

    template<class XY, class Z, class W>
    constexpr Type4(const Type2<XY>& _xy, Z _z, W _w)
      : x(static_cast<Type>(_xy.x))
      , y(static_cast<Type>(_xy.y))
      , z(static_cast<Type>(_z))
      , w(static_cast<Type>(_w)) {}

    template<class X, class YZ, class W>
    constexpr Type4(X _x, const Type2<YZ>& _yz, W _w)
      : x(static_cast<Type>(_x))
      , y(static_cast<Type>(_yz.x))
      , z(static_cast<Type>(_yz.y))
      , w(static_cast<Type>(_w)) {}

    template<class X, class Y, class ZW>
    constexpr Type4(X _x, Y _y, const Type2<ZW>& _zw)
      : x(static_cast<Type>(_x))
      , y(static_cast<Type>(_y))
      , z(static_cast<Type>(_zw.x))
      , w(static_cast<Type>(_zw.y)) {}

    template<class XY, class ZW>
    constexpr Type4(const Type2<XY>& _xy, const Type2<ZW>& _zw)
      : x(static_cast<Type>(_xy.x))
      , y(static_cast<Type>(_xy.y))
      , z(static_cast<Type>(_zw.x))
      , w(static_cast<Type>(_zw.y)) {}

    template<class XYZ, class W>
    constexpr Type4(const Type3<XYZ>& _xyz, W _w)
      : x(static_cast<Type>(_xyz.x))
      , y(static_cast<Type>(_xyz.y))
      , z(static_cast<Type>(_xyz.z))
      , w(static_cast<Type>(_w)) {}

    template<class X, class YZW>
    constexpr Type4(X _x, const Type3<YZW>& _yzw)
      : x(static_cast<Type>(_X))
      , y(static_cast<Type>(_yzw.x))
      , z(static_cast<Type>(_yzw.y))
      , w(static_cast<Type>(_yzw.z)) {}
  public:
    [[nodiscard]] constexpr bool operator==(const Type4& _v)const { return x == _v.x && y == _v.y && z == _v.z && w == _v.w; }

    [[nodiscard]] constexpr bool operator!=(const Type4& _v)const { return !(*this == _v); }

    [[nodiscard]] constexpr Type4 operator+()const { return *this; }

    [[nodiscard]] constexpr Type4 operator-()const { return{ -x, -y, -z, -w }; }

    ARITHMETIC_OPERATOR(+);

    ARITHMETIC_OPERATOR(-);

    ARITHMETIC_OPERATOR(*);

    ARITHMETIC_OPERATOR(/ );

    ASSIGNMENT_OPERATOR(= );

    ASSIGNMENT_OPERATOR(+= );

    ASSIGNMENT_OPERATOR(-= );

    ASSIGNMENT_OPERATOR(*= );

    ASSIGNMENT_OPERATOR(/= );
  public:
    [[nodiscard]] constexpr Type Length()const { return std::sqrt(LengthSq()); }

    [[nodiscard]] constexpr Type LengthSq()const { return x * x + y * y + z * z + w * w; }

    [[nodiscard]] constexpr Type4 Normalize()const { return *this / Length(); }

    template<class T>
    [[nodiscard]] constexpr auto Dot(const Type4<T>& _v)const->decltype(x * _v.x) { return x * _v.x + y * _v.y + z * _v.z + w * _v.w; }
  public:
    [[nodiscard]] constexpr Type2<Type> xy()const { return{ x, y }; }

    [[nodiscard]] constexpr Type2<Type> xz()const { return{ x, z }; }

    [[nodiscard]] constexpr Type2<Type> xw()const { return{ x, w }; }

    [[nodiscard]] constexpr Type2<Type> yz()const { return{ y, z }; }

    [[nodiscard]] constexpr Type2<Type> yw()const { return{ y, w }; }

    [[nodiscard]] constexpr Type2<Type> zw()const { return{ z, w }; }

    [[nodiscard]] constexpr Type3<Type> xyz()const { return{ x, y, z }; }

    [[nodiscard]] constexpr Type3<Type> xyw()const { return{ x, y, w }; }

    [[nodiscard]] constexpr Type3<Type> xzw()const { return{ x, z, w }; }

    [[nodiscard]] constexpr Type3<Type> yzw()const { return{ y, z, w }; }
  };

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator==(T _s, const Type4<Type>& _v) { return _v == _s; }

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator!=(T _s, const Type4<Type>& _v) { return _v != _s; }

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator+(T _s, const Type4<Type>& _v) { return _v + _s; }

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator*(T _s, const Type4<Type>& _v) { return _v * _s; }
}

namespace std
{
  template <class Type>
  [[nodiscard]] inline string to_string(const hdx::Type4<Type>& _v)
  {
    return to_string(_v.x) + "," + to_string(_v.y) + "," + to_string(_v.z) + "," + to_string(_v.w);
  }

  template <class Type>
  [[nodiscard]] inline wstring to_wstring(const hdx::Type4<Type>& _v)
  {
    return to_wstring(_v.x) + L"," + to_wstring(_v.y) + L"," + to_wstring(_v.z) + L"," + to_wstring(_v.w);
  }

  template <class CharType, class Type>
  inline basic_ostream<CharType>& operator<<(basic_ostream<CharType>& _OStream, const hdx::Type4<Type>& _v)
  {
    return _OStream << _v.x << CharType(',') << _v.y << CharType(',') << _v.z << CharType(',') << _v.w;
  }

  template <class CharType, class Type>
  inline basic_istream<CharType>& operator>>(basic_istream<CharType>& _IStream, hdx::Type4<Type>& _v)
  {
    CharType Temp;

    return _IStream >> _v.x >> Temp >> _v.y >> Temp >> _v.z >> Temp >> _v.w;
  }
}

#undef ARITHMETIC_OPERATOR
#undef ASSIGNMENT_OPERATOR
