#include "Include/Math.hpp"

#include "Include/Angle.hpp"

#include <math.h>

//  ���C�u����
namespace hdx
{
  namespace Math
  {
    //  X��]
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.x - _Center.x, _Target.y - _Center.y };

      return Vector.x*cosf(_Radian.GetValue()) - Vector.y*sinf(_Radian.GetValue()) + _Center.x;
    }

    //  Y��]
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.x - _Center.x, _Target.y - _Center.y };

      return Vector.y*cosf(_Radian.GetValue()) + Vector.x*sinf(_Radian.GetValue()) + _Center.y;
    }

    //  XY��]
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.x - _Center.x, _Target.y - _Center.y };

      return float2{ Vector.x*cosf(_Radian.GetValue()) - Vector.y*sinf(_Radian.GetValue()),Vector.y*cosf(_Radian.GetValue()) + Vector.x*sinf(_Radian.GetValue()) } +_Center;
    }

    //  �񎟊֐�(��ɓ�)
    float UpQuadraticFunction(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return (1.0f - (_Time / (_TotalTime / 2.0f) - 1.0f)*(_Time / (_TotalTime / 2.0f) - 1.0f))*(_Max - _Min) + _Min;
    }

    //  �񎟊֐�(���ɓ�)
    float DownQuadraticFunction(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return (_Time / (_TotalTime / 2.0f) - 1.0f)*(_Time / (_TotalTime / 2.0f) - 1.0f)*(_Max - _Min) + _Min;
    }
  }
}
