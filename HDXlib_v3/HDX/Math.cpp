#include <HDX/Math.hpp>

#include <HDX/Angle.hpp>
#include <math.h>

//  ライブラリ
namespace hdx
{
  namespace Math
  {
    //  X回転
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.X - _Center.X, _Target.Y - _Center.Y };

      return Vector.X*cosf(_Radian.GetValue()) - Vector.Y*sinf(_Radian.GetValue()) + _Center.X;
    }

    //  Y回転
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.X - _Center.X, _Target.Y - _Center.Y };

      return Vector.Y*cosf(_Radian.GetValue()) + Vector.X*sinf(_Radian.GetValue()) + _Center.Y;
    }

    //  XY回転
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian)
    {
      const float2 Vector{ _Target.X - _Center.X, _Target.Y - _Center.Y };

      return float2{ Vector.X*cosf(_Radian.GetValue()) - Vector.Y*sinf(_Radian.GetValue()),Vector.Y*cosf(_Radian.GetValue()) + Vector.X*sinf(_Radian.GetValue()) } +_Center;
    }

    //  絶対値を返します
    float GetAbsoluteValue(float _Num)
    {
      return (_Num < 0.0f) ? -_Num : _Num;
    }

    //  _Num0と_Num1を_Epsilonの誤差を考慮した比較
    bool isEqual(float _Num0, float _Num1, float _Epsilon)
    {
      return (((_Num1 - _Epsilon) < _Num0) && (_Num0 < (_Num1 + _Epsilon)));
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
