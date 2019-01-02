#include "Include/Easing.hpp"

#include "Include/MathConstants.hpp"

#include <cmath>

namespace hdx
{
  namespace Easing
  {
    float Linear(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return ((_Time / _TotalTime)*_Max + _Min);
    }

    float Sine::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return -_Max * cosf(_Time / _TotalTime * Math::HalfPI) + _Max + _Min;
    }

    float Sine::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max * sinf(_Time / _TotalTime * Math::HalfPI) + _Min;
    }

    float Sine::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return -_Max / 2.0f * (std::cos(Math::PI*_Time / _TotalTime) - 1.0f) + _Min;
    }

    float Quad::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max*(_Time /= _TotalTime)*_Time + _Min;
    }

    float Quad::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return -_Max *(_Time /= _TotalTime)*(_Time - 2.0f) + _Min;
    }

    float Quad::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if ((_Time /= _TotalTime*0.5f) < 1.0f) return ((_Max*0.5f)*(_Time*_Time)) + _Min;
      return -_Max*0.5f * (((_Time - 2.0f)*(--_Time)) - 1.0f) + _Min;
    }

    float Cubic::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max*(_Time /= _TotalTime)*_Time*_Time + _Min;
    }

    float Cubic::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max*((_Time = _Time / _TotalTime - 1.0f)*_Time*_Time + 1.0f) + _Min;
    }

    float Cubic::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if ((_Time /= _TotalTime*0.5f) < 1.0f) return _Max*0.5f * _Time*_Time*_Time + _Min;
      return _Max*0.5f * ((_Time -= 2.0f)*_Time*_Time + 2.0f) + _Min;
    }

    float Quart::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max*(_Time /= _TotalTime)*_Time*_Time*_Time + _Min;
    }

    float Quart::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return -_Max * ((_Time = _Time / _TotalTime - 1)*_Time*_Time*_Time - 1) + _Min;
    }

    float Quart::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if ((_Time /= _TotalTime*0.5f) < 1.0f) return _Max*0.5f * _Time*_Time*_Time*_Time + _Min;
      return -_Max*0.5f * ((_Time -= 2.0f)*_Time*_Time*_Time - 2.0f) + _Min;
    }

    float Quint::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max*(_Time /= _TotalTime)*_Time*_Time*_Time*_Time + _Min;
    }

    float Quint::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max*((_Time = _Time / _TotalTime - 1)*_Time*_Time*_Time*_Time + 1) + _Min;
    }

    float Quint::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if ((_Time /= _TotalTime*0.5f) < 1.0f) return _Max*0.5f * _Time*_Time*_Time*_Time*_Time + _Min;
      return _Max*0.5f * ((_Time -= 2.0f)*_Time*_Time*_Time*_Time + 2.0f) + _Min;
    }

    float Expo::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return (_Time == 0.0f) ? _Min : _Max * std::pow(2.0f, 10.0f * (_Time / _TotalTime - 1.0f)) + _Min;
    }

    float Expo::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return (_Time == _TotalTime) ? _Min + _Max : _Max * (-std::pow(2.0f, -10.0f * _Time / _TotalTime) + 1.0f) + _Min;
    }

    float Expo::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if (_Time == 0.0f) return _Min;
      if (_Time == _TotalTime) return _Min + _Max;
      if ((_Time /= _TotalTime*0.5f) < 1) return _Max*0.5f * std::pow(2.0f, 10.0f * (_Time - 1.0f)) + _Min;
      return _Max*0.5f * (-std::pow(2.0f, -10.0f * --_Time) + 2.0f) + _Min;
    }

    float Circ::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return -_Max * (std::sqrt(1.0f - (_Time /= _TotalTime)*_Time) - 1.0f) + _Min;
    }

    float Circ::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max * std::sqrt(1.0f - (_Time = _Time / _TotalTime - 1)*_Time) + _Min;
    }

    float Circ::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if ((_Time /= _TotalTime*0.5f) < 1.0f) return -_Max*0.5f * (std::sqrt(1.0f - _Time*_Time) - 1.0f) + _Min;
      return _Max*0.5f * (std::sqrt(1.0f - _Time*(_Time -= 2.0f)) + 1.0f) + _Min;
    }

    float Back::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      const float s = 1.70158f;
      const float postFix = _Time /= _TotalTime;
      return _Max*postFix*_Time*((s + 1.0f)*_Time - s) + _Min;
    }

    float Back::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      const float s = 1.70158f;
      return _Max*((_Time = _Time / _TotalTime - 1.0f)*_Time*((s + 1.0f)*_Time + s) + 1.0f) + _Min;
    }

    float Back::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      float s = 1.70158f;
      if ((_Time /= _TotalTime*0.5f) < 1.0f) return _Max*0.5f * (_Time*_Time*(((s *= 1.525f) + 1.0f)*_Time - s)) + _Min;
      const float postFix = _Time -= 2.0f;
      return _Max*0.5f * (postFix*_Time*(((s *= 1.525f) + 1.0f)*_Time + s) + 2.0f) + _Min;
    }

    float Elastic::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if (_Time == 0.0f) return _Min;  if ((_Time /= _TotalTime) == 1.0f) return _Min + _Max;
      const float p = _TotalTime*0.3f;
      const float a = _Max;
      const float s = p / 4.0f;
      const float postFix = a*std::pow(2.0f, 10.0f * (_Time -= 1.0f));
      return -(postFix * std::sin((_Time*_TotalTime - s)*Math::TwoPI / p)) + _Min;
    }

    float Elastic::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if (_Time == 0) return _Min;  if ((_Time /= _TotalTime) == 1) return _Min + _Max;
      const float p = _TotalTime*0.3f;
      const float a = _Max;
      const float s = p / 4.0f;
      return (a*std::pow(2.0f, -10.0f * _Time) * std::sin((_Time*_TotalTime - s)*Math::TwoPI / p) + _Max + _Min);
    }

    float Elastic::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if (_Time == 0.0f) return _Min;  if ((_Time /= _TotalTime*0.5f) == 2.0f) return _Min + _Max;
      const float p = _TotalTime*(0.3f*1.5f);
      const float a = _Max;
      const float s = p / 4.0f;

      if (_Time < 1)
      {
        const float postFix = a*std::pow(2.0f, 10.0f * (_Time -= 1.0f));
        return -0.5f*(postFix* sin((_Time*_TotalTime - s)*Math::TwoPI / p)) + _Min;
      }
      const float postFix = a*std::pow(2.0f, -10.0f * (_Time -= 1.0f));
      return postFix * sin((_Time*_TotalTime - s)*Math::TwoPI / p)*0.5f + _Max + _Min;
    }

    float Bounce::In(float _Time, float _TotalTime, float _Max, float _Min)
    {
      return _Max - Out(_TotalTime - _Time, _TotalTime, _Max, 0.0f) + _Min;
    }

    float Bounce::Out(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if ((_Time /= _TotalTime) < (1.0f / 2.75f))
      {
        return _Max*(7.5625f*_Time*_Time) + _Min;
      }
      else if (_Time < (2.0f / 2.75f))
      {
        const float postFix = _Time -= (1.5f / 2.75f);
        return _Max*(7.5625f*postFix*_Time + 0.75f) + _Min;
      }
      else if (_Time < (2.5 / 2.75))
      {
        const float postFix = _Time -= (2.25f / 2.75f);
        return _Max*(7.5625f*postFix*_Time + 0.9375f) + _Min;
      }
      else
      {
        const float postFix = _Time -= (2.625f / 2.75f);
        return _Max*(7.5625f*postFix*_Time + 0.984375f) + _Min;
      }
    }

    float Bounce::InOut(float _Time, float _TotalTime, float _Max, float _Min)
    {
      if (_Time < _TotalTime*0.5f) return In(_Time * 2.0f, _TotalTime, _Max, _TotalTime)*0.5f + _Min;
      else return Out(_Time * 2.0f - _TotalTime, _TotalTime, _Max, _TotalTime)*0.5f + _Max*0.5f + _Min;
    }
  }
}
