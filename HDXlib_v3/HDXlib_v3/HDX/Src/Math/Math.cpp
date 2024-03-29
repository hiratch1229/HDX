#include "Include/Math.hpp"

#include "Include/Angle.hpp"

#include <math.h>

//  ライブラリ
namespace hdx
{
  namespace Math
  {
    //  X回転
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.x - _Center.x, _Target.y - _Center.y };

      return Vector.x*cosf(_Radian) - Vector.y*sinf(_Radian) + _Center.x;
    }

    //  Y回転
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.x - _Center.x, _Target.y - _Center.y };

      return Vector.y*cosf(_Radian) + Vector.x*sinf(_Radian) + _Center.y;
    }

    //  XY回転
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.x - _Center.x, _Target.y - _Center.y };

      return float2{ Vector.x*cosf(_Radian) - Vector.y*sinf(_Radian),Vector.y*cosf(_Radian) + Vector.x*sinf(_Radian) } +_Center;
    }

    //  二次関数(上に凸)
    float UpQuadraticFunction(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return (1.0f - (_Time / (_TotalTime / 2.0f) - 1.0f)*(_Time / (_TotalTime / 2.0f) - 1.0f))*(_Max - _Min) + _Min;
    }

    //  二次関数(下に凸)
    float DownQuadraticFunction(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return (_Time / (_TotalTime / 2.0f) - 1.0f)*(_Time / (_TotalTime / 2.0f) - 1.0f)*(_Max - _Min) + _Min;
    }
  }
}
