#pragma once
#include "Type2.hpp"

//  ‘O•ûéŒ¾
namespace hdx
{
  class Radian;
}

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  namespace Math
  {
    //  X‰ñ“]
    //  _Target:‰ñ“]‚·‚é“_
    //  _Center:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    float RotateX(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  X‰ñ“]
    //  _TargetX,_TargetY:‰ñ“]‚·‚é“_
    //  _CenterX,_CenterY:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float RotateX(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateX({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  X‰ñ“]
    //  _Target:‰ñ“]‚·‚é“_
    //  _CenterX,_CenterY:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float RotateX(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateX(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  X‰ñ“]
    //  _TargetX,_TargetY:‰ñ“]‚·‚é“_
    //  _Center:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float RotateX(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateX({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  Y‰ñ“]
    //  _Target:‰ñ“]‚·‚é“_
    //  _Center:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    float RotateY(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  Y‰ñ“]
    //  _TargetX,_TargetY:‰ñ“]‚·‚é“_
    //  _CenterX,_CenterY:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float RotateY(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateY({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  Y‰ñ“]
    //  _Target:‰ñ“]‚·‚é“_
    //  _CenterX,_CenterY:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float RotateY(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateY(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  Y‰ñ“]
    //  _TargetX,_TargetY:‰ñ“]‚·‚é“_
    //  _Center:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float RotateY(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateY({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  XY‰ñ“]
    //  _Target:‰ñ“]‚·‚é“_
    //  _Center:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    float2 RotateXY(const float2& _Target, const float2& _Center, const Radian& _Radian);
    //  XY‰ñ“]
    //  _TargetX,_TargetY:‰ñ“]‚·‚é“_
    //  _CenterX,_CenterY:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float2 RotateXY(float _TargetX, float _TargetY, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateXY({ _TargetX ,_TargetY }, { _CenterX,_CenterY }, _Radian);
    }
    //  XY‰ñ“]
    //  _Target:‰ñ“]‚·‚é“_
    //  _CenterX,_CenterY:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float2 RotateXY(const float2& _Target, float _CenterX, float _CenterY, const Radian& _Radian)
    {
      return RotateXY(_Target, { _CenterX,_CenterY }, _Radian);
    }
    //  XY‰ñ“]
    //  _TargetX,_TargetY:‰ñ“]‚·‚é“_
    //  _Center:‰ñ“]‚Ì’†S“_
    //  _Radian:ŒÊ“x–@
    inline float2 RotateXY(float _TargetX, float _TargetY, const float2& _Center, const Radian& _Radian)
    {
      return RotateXY({ _TargetX ,_TargetY }, _Center, _Radian);
    }

    //  _Num0‚Æ_Num1‚ğ_Epsilon‚ÌŒë·‚ğl—¶‚µ‚½”äŠr
    bool isEqual(float _Num0, float _Num1, float _Epsilon = 1.192092896e-07F);

    //  â‘Î’l‚ğ•Ô‚µ‚Ü‚·
    float GetAbsoluteValue(float _Num);
    //  â‘Î’l‚ğ•Ô‚µ‚Ü‚·
    inline int GetAbsoluteValue(int _Num)
    {
      return static_cast<int>(GetAbsoluteValue(static_cast<float>(_Num)));
    }

    //  “ñŸŠÖ”(ã‚É“Ê)
    //  _Max‚©‚ç_Min‚Ì”ÍˆÍ‚Å“®‚«‚Ü‚·
    float UpQuadraticFunction(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);

    //  “ñŸŠÖ”(‰º‚É“Ê)
    //  _Max‚©‚ç_Min‚Ì”ÍˆÍ‚Å“®‚«‚Ü‚·
    float DownQuadraticFunction(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
  }
}

