#pragma once

#define ARITHMETIC_OPERATOR(Operator)\
template<class T>\
constexpr auto operator##Operator(const Type2<T>& _v)const->Type2<decltype(x Operator _v.x)>\
{\
  return{ x Operator _v.x, y Operator _v.y };\
}\
template<class T>\
constexpr auto operator##Operator(T _s)const->Type2<decltype(x Operator _s)>\
{\
  return{ x Operator _s, y Operator _s };\
}\

#define ASSIGNMENT_OPERATOR(Operator)\
template<class T>\
const Type2& operator##Operator(const Type2<T>& _v)\
{\
  x Operator static_cast<Type>(_v.x);\
  y Operator static_cast<Type>(_v.y);\
  \
  return *this;\
}\
template<class T>\
const Type2& operator##Operator(T _s)\
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
    constexpr bool operator==(const Type2& _v)const { return x == _v.x && y == _v.y; }

    constexpr bool operator!=(const Type2& _v)const { return !(*this == _v); }

    constexpr Type2 operator+()const { return *this; }

    constexpr Type2 operator-()const { return{ -x, -y }; }

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
  inline constexpr auto operator+(T _s, const Type2<Type>& _v) { return _v + _s; }

  template<class T, class Type>
  inline constexpr auto operator-(T _s, const Type2<Type>& _v) { return _v - _s; }

  template<class T, class Type>
  inline constexpr auto operator*(T _s, const Type2<Type>& _v) { return _v * _s; }

  template<class T, class Type>
  inline constexpr auto operator/(T _s, const Type2<Type>& _v) { return _v / _s; }

  using int2 = Type2<int>;
  using float2 = Type2<float>;
}

#undef ARITHMETIC_OPERATOR
#undef ASSIGNMENT_OPERATOR
