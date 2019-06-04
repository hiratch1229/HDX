#pragma once
#include "Fwd.hpp"

#include <cmath>
#include <string>
#include <fstream>

#define ARITHMETIC_OPERATOR(Operator)\
template<class T>\
[[nodiscard]] constexpr auto operator##Operator(const Type2<T>& _v)const->Type2<decltype(x Operator _v.x)>\
{\
  return{ x Operator _v.x, y Operator _v.y };\
}\
template<class T>\
[[nodiscard]] constexpr auto operator##Operator(T _s)const->Type2<decltype(x Operator _s)>\
{\
  return{ x Operator _s, y Operator _s };\
}\

#define ASSIGNMENT_OPERATOR(Operator)\
template<class T>\
Type2& operator##Operator(const Type2<T>& _v)\
{\
  x Operator static_cast<Type>(_v.x);\
  y Operator static_cast<Type>(_v.y);\
  \
  return *this;\
}\
template<class T>\
Type2& operator##Operator(T _s)\
{\
  x Operator static_cast<Type>(_s);\
  y Operator static_cast<Type>(_s);\
  \
  return *this;\
}\

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
    [[nodiscard]] constexpr bool operator==(const Type2& _v)const { return x == _v.x && y == _v.y; }

    [[nodiscard]] constexpr bool operator!=(const Type2& _v)const { return !(*this == _v); }

    [[nodiscard]] constexpr Type2 operator+()const { return *this; }

    [[nodiscard]] constexpr Type2 operator-()const { return{ -x, -y }; }

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

    [[nodiscard]] constexpr Type LengthSq()const { return x * x + y * y; }

    [[nodiscard]] constexpr Type2 Normalize()const { return *this / Length(); }

    template<class T>
    [[nodiscard]] constexpr auto Dot(const Type2<T>& _v)const->decltype(x * _v.x) { return x * _v.x + y * _v.y; }

    template<class T>
    [[nodiscard]] constexpr auto Cross(const Type2<T>& _v)const->decltype(x * _v.x) { return x * _v.y - y * _v.x; }
  };

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator==(T _s, const Type2<Type>& _v) { return _v == _s; }

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator!=(T _s, const Type2<Type>& _v) { return _v != _s; }

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator+(T _s, const Type2<Type>& _v) { return _v + _s; }

  template<class T, class Type>
  [[nodiscard]] inline constexpr auto operator*(T _s, const Type2<Type>& _v) { return _v * _s; }
}

namespace std
{
  template <class Type>
  [[nodiscard]] inline string to_string(const hdx::Type2<Type>& _v)
  {
    return to_string(_v.x) + "," + to_string(_v.y);
  }

  template <class Type>
  [[nodiscard]] inline wstring to_wstring(const hdx::Type2<Type>& _v)
  {
    return to_wstring(_v.x) + L"," + to_wstring(_v.y);
  }

  template <class CharType, class Type>
  inline basic_ostream<CharType>& operator<<(basic_ostream<CharType>& _OStream, const hdx::Type2<Type>& _v)
  {
    return _OStream << _v.x << CharType(',') << _v.y;
  }

  template <class CharType, class Type>
  inline basic_istream<CharType>& operator>>(basic_istream<CharType>& _IStream, hdx::Type2<Type>& _v)
  {
    CharType Temp;

    return _IStream >> _v.x >> Temp >> _v.y;
  }
}

#undef ARITHMETIC_OPERATOR
#undef ASSIGNMENT_OPERATOR
