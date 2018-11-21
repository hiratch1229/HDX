#include "../../Include/Random.hpp"

#include "../Engine.hpp"
#include "../Random/IRandom.hpp"

#include <climits>

namespace hdx
{
  int Random::Range(int _Max, int _Min)
  {
    const UINT R = Engine::Get<IRandom>()->Get();

    if (_Min > _Max)
    {
      const int Temp = _Min;
      _Min = _Max;
      _Max = Temp;
    }

    const int Value = _Max - _Min;

    return R % Value + _Min;
  }

  float Random::Range(float _Max, float _Min)
  {
    const UINT R = Engine::Get<IRandom>()->Get();

    if (_Min > _Max)
    {
      const float Temp = _Min;
      _Min = _Max;
      _Max = Temp;
    }

    const float Value = _Max - _Min;

    return (static_cast<float>(R) / UINT_MAX)*Value + _Min;
  }

  void Random::SetSeed(UINT _Seed)
  {
    Engine::Get<IRandom>()->SetSeed(_Seed);
  }
}
