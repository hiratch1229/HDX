#pragma once

namespace hdx
{
  //-------------------------
  //  Angle.hpp
  //-------------------------
  class Radian;
  class Degree;

  //-------------------------
  //  Type.hpp
  //-------------------------
  template<class Type> struct Type2;
  template<class Type> struct Type3;
  template<class Type> struct Type4;

  using int2 = Type2<int>;
  using float2 = Type2<float>;
  using int3 = Type3<int>;
  using float3 = Type3<float>;
  using int4 = Type4<int>;
  using float4 = Type4<float>;

  //-------------------------
  //  Color.hpp
  //-------------------------
  struct Color;
  struct ColorF;
}
