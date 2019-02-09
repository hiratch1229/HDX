#pragma once

#define ARITHMETIC_OPERATOR(Operator)\
template<class T>\
constexpr auto operator##Operator(const Type4<T>& _v)const->Type4<decltype(x Operator _v.x)>\
{\
  return{ x Operator _v.x, y Operator _v.y, z Operator _v.z, w Operator _v.w };\
}\
template<class T>\
constexpr auto operator##Operator(T _s)const->Type4<decltype(x Operator _s)>\
{\
  return{ x Operator _s, y Operator _s, z Operator _s, w Operator _s };\
}\

#define ASSIGNMENT_OPERATOR(Operator)\
template<class T>\
const Type4& operator##Operator(const Type4<T>& _v)\
{\
  x Operator static_cast<Type>(_v.x);\
  y Operator static_cast<Type>(_v.y);\
  z Operator static_cast<Type>(_v.z);\
  w Operator static_cast<Type>(_v.w);\
  \
  return *this;\
}\
template<class T>\
const Type4& operator##Operator(T _s)\
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
  public:
    constexpr bool operator==(const Type4& _v)const { return x == _v.x && y == _v.y && z == _v.z && w == _v.w; }

    constexpr bool operator!=(const Type4& _v)const { return !(*this == _v); }

    constexpr Type4 operator+()const { return *this; }

    constexpr Type4 operator-()const { return{ -x, -y, -z, -w }; }

    ARITHMETIC_OPERATOR(+);

    ARITHMETIC_OPERATOR(-);

    ARITHMETIC_OPERATOR(*);

    ARITHMETIC_OPERATOR(/ );

    ASSIGNMENT_OPERATOR(= );

    ASSIGNMENT_OPERATOR(+= );

    ASSIGNMENT_OPERATOR(-= );

    ASSIGNMENT_OPERATOR(*= );

    ASSIGNMENT_OPERATOR(/= );
  };

  template<class T, class Type>
  inline constexpr auto operator+(T _s, const Type4<Type>& _v) { return _v + _s; }

  template<class T, class Type>
  inline constexpr auto operator-(T _s, const Type4<Type>& _v) { return _v - _s; }

  template<class T, class Type>
  inline constexpr auto operator*(T _s, const Type4<Type>& _v) { return _v * _s; }

  template<class T, class Type>
  inline constexpr auto operator/(T _s, const Type4<Type>& _v) { return _v / _s; }

  using int4 = Type4<int>;
  using float4 = Type4<float>;
}

#undef ARITHMETIC_OPERATOR
#undef ASSIGNMENT_OPERATOR
