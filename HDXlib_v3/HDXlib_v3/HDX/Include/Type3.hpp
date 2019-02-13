#pragma once

#define ARITHMETIC_OPERATOR(Operator)\
template<class T>\
constexpr auto operator##Operator(const Type3<T>& _v)const->Type3<decltype(x Operator _v.x)>\
{\
  return{ x Operator _v.x, y Operator _v.y, z Operator _v.z };\
}\
template<class T>\
constexpr auto operator##Operator(T _s)const->Type3<decltype(x Operator _s)>\
{\
  return{ x Operator _s, y Operator _s, z Operator _s };\
}\

#define ASSIGNMENT_OPERATOR(Operator)\
template<class T>\
const Type3& operator##Operator(const Type3<T>& _v)\
{\
  x Operator static_cast<Type>(_v.x);\
  y Operator static_cast<Type>(_v.y);\
  z Operator static_cast<Type>(_v.z);\
  \
  return *this;\
}\
template<class T>\
const Type3& operator##Operator(T _s)\
{\
  x Operator static_cast<Type>(_s);\
  y Operator static_cast<Type>(_s);\
  z Operator static_cast<Type>(_s);\
  \
  return *this;\
}\

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
  inline constexpr auto operator==(T _s, const Type3<Type>& _v) { return _v == _s; }

  template<class T, class Type>
  inline constexpr auto operator!=(T _s, const Type3<Type>& _v) { return _v != _s; }

  template<class T, class Type>
  inline constexpr auto operator+(T _s, const Type3<Type>& _v) { return _v + _s; }

  template<class T, class Type>
  inline constexpr auto operator-(T _s, const Type3<Type>& _v) { return _v - _s; }

  template<class T, class Type>
  inline constexpr auto operator*(T _s, const Type3<Type>& _v) { return _v * _s; }

  using int3 = Type3<int>;
  using float3 = Type3<float>;
}

#undef ARITHMETIC_OPERATOR
#undef ASSIGNMENT_OPERATOR
