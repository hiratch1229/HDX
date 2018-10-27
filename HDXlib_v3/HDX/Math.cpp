#include <HDX/Math.hpp>

#include <HDX/Angle.hpp>
#include <math.h>

//  ���C�u����
namespace hdx
{
  namespace Math
  {
    //  X��]
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.X - _Center.X, _Target.Y - _Center.Y };

      return Vector.X*cosf(_Radian.GetValue()) - Vector.Y*sinf(_Radian.GetValue()) + _Center.X;
    }

    //  Y��]
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.X - _Center.X, _Target.Y - _Center.Y };

      return Vector.Y*cosf(_Radian.GetValue()) + Vector.X*sinf(_Radian.GetValue()) + _Center.Y;
    }

    //  XY��]
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.X - _Center.X, _Target.Y - _Center.Y };

      return float2{ Vector.X*cosf(_Radian.GetValue()) - Vector.Y*sinf(_Radian.GetValue()),Vector.Y*cosf(_Radian.GetValue()) + Vector.X*sinf(_Radian.GetValue()) } +_Center;
    }

    //  ��Βl��Ԃ��܂�
    float GetAbsoluteValue(float _Num)
    {
      return (_Num < 0.0f) ? -_Num : _Num;
    }

    //  _Num0��_Num1��_Epsilon�̌덷���l��������r
    bool isEqual(float _Num0, float _Num1, float _Epsilon)
    {
      return (((_Num1 - _Epsilon) < _Num0) && (_Num0 < (_Num1 + _Epsilon)));
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
