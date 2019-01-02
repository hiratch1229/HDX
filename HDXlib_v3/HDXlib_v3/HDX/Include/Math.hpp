#pragma once
#include "Type2.hpp"

//  �O���錾
namespace hdx
{
  class Radian;
}

//  ���C�u����
namespace hdx
{
  namespace Math
  {
    //  X��]
    //  _Target:��]����_
    //  _Center:��]�̒��S�_
    //  _Radian:�ʓx�@
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  X��]
    //  _TargetX,_TargetY:��]����_
    //  _CenterX,_CenterY:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float RotateX(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateX({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  X��]
    //  _Target:��]����_
    //  _CenterX,_CenterY:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float RotateX(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateX(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  X��]
    //  _TargetX,_TargetY:��]����_
    //  _Center:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float RotateX(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateX({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  Y��]
    //  _Target:��]����_
    //  _Center:��]�̒��S�_
    //  _Radian:�ʓx�@
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  Y��]
    //  _TargetX,_TargetY:��]����_
    //  _CenterX,_CenterY:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float RotateY(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateY({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  Y��]
    //  _Target:��]����_
    //  _CenterX,_CenterY:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float RotateY(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateY(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  Y��]
    //  _TargetX,_TargetY:��]����_
    //  _Center:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float RotateY(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateY({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  XY��]
    //  _Target:��]����_
    //  _Center:��]�̒��S�_
    //  _Radian:�ʓx�@
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  XY��]
    //  _TargetX,_TargetY:��]����_
    //  _CenterX,_CenterY:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float2 RotateXY(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateXY({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  XY��]
    //  _Target:��]����_
    //  _CenterX,_CenterY:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float2 RotateXY(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateXY(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  XY��]
    //  _TargetX,_TargetY:��]����_
    //  _Center:��]�̒��S�_
    //  _Radian:�ʓx�@
    inline float2 RotateXY(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateXY({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  _Num0��_Num1��_Epsilon�̌덷���l��������r
    inline constexpr bool isEqual(float _V0, float _V1, float _Epsilon = 1.192092896e-07F)
    {
      return ((_V1 - _Epsilon) < _V0) && (_V0 < (_V1 + _Epsilon));
    }

    //  ��Βl��Ԃ��܂�
    template <class T>
    inline constexpr T GetAbsoluteValue(T _Num)
    {
      return (_Num < static_cast<T>(0)) ? -_Num : _Num;
    }

    //  �l��͈͓��Ɏ��߂܂�
    template <class T>
    inline constexpr const T& Clamp(const T& _V, const T& _Low, const T& _High)
    {
      return (_Low <= _V && _V <= _High) ? _V : (_V < _Low) ? _Low : _High;
    }
    
    //  �񎟊֐�(��ɓ�)
    //  _Max����_Min�͈̔͂œ����܂�
    float UpQuadraticFunction(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);

    //  �񎟊֐�(���ɓ�)
    //  _Max����_Min�͈̔͂œ����܂�
    float DownQuadraticFunction(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
  }
}

