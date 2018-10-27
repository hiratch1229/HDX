#pragma once
#include <HDX/Type2.hpp>

//  前方宣言
namespace hdx
{
  class Radian;
}

//  ライブラリ
namespace hdx
{
  namespace Math
  {
    //  X回転
    //  _Target:回転する点
    //  _Center:回転の中心点
    //  _Radian:弧度法
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  X回転
    //  _TargetX,_TargetY:回転する点
    //  _CenterX,_CenterY:回転の中心点
    //  _Radian:弧度法
    inline float RotateX(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateX({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  X回転
    //  _Target:回転する点
    //  _CenterX,_CenterY:回転の中心点
    //  _Radian:弧度法
    inline float RotateX(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateX(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  X回転
    //  _TargetX,_TargetY:回転する点
    //  _Center:回転の中心点
    //  _Radian:弧度法
    inline float RotateX(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateX({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  Y回転
    //  _Target:回転する点
    //  _Center:回転の中心点
    //  _Radian:弧度法
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  Y回転
    //  _TargetX,_TargetY:回転する点
    //  _CenterX,_CenterY:回転の中心点
    //  _Radian:弧度法
    inline float RotateY(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateY({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  Y回転
    //  _Target:回転する点
    //  _CenterX,_CenterY:回転の中心点
    //  _Radian:弧度法
    inline float RotateY(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateY(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  Y回転
    //  _TargetX,_TargetY:回転する点
    //  _Center:回転の中心点
    //  _Radian:弧度法
    inline float RotateY(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateY({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  XY回転
    //  _Target:回転する点
    //  _Center:回転の中心点
    //  _Radian:弧度法
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  XY回転
    //  _TargetX,_TargetY:回転する点
    //  _CenterX,_CenterY:回転の中心点
    //  _Radian:弧度法
    inline float2 RotateXY(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateXY({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  XY回転
    //  _Target:回転する点
    //  _CenterX,_CenterY:回転の中心点
    //  _Radian:弧度法
    inline float2 RotateXY(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateXY(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  XY回転
    //  _TargetX,_TargetY:回転する点
    //  _Center:回転の中心点
    //  _Radian:弧度法
    inline float2 RotateXY(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateXY({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  _Num0と_Num1を_Epsilonの誤差を考慮した比較
    bool isEqual(float _Num0, float _Num1, float _Epsilon = 1.192092896e-07F);

    //  絶対値を返します
    float GetAbsoluteValue(float _Num);
    //  絶対値を返します
    inline int GetAbsoluteValue(int _Num)
    {
      return static_cast<int>(GetAbsoluteValue(static_cast<float>(_Num)));
    }

    //  二次関数(上に凸)
    //  _Maxから_Minの範囲で動きます
    float UpQuadraticFunction(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);

    //  二次関数(下に凸)
    //  _Maxから_Minの範囲で動きます
    float DownQuadraticFunction(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
  }
}

