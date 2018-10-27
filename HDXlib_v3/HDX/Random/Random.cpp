#include <HDX/Random/Random.hpp>
#include <stdlib.h>
#include <Windows.h>

#include <random>

namespace hdx
{
  Random::Random()
    : W_(rand())
  {
    std::mt19937 mt = std::mt19937(std::random_device()());

    std::uniform_int_distribution<int>(0, 100)(mt);

    std::uniform_real_distribution<float>(0.0f, 100.0f)(mt);
  }

  int Random::Range(int _Max, int _Min)const
  {
    const unsigned int R = Rand();

    if (_Min > _Max)
    {
      const int Temp = _Min;
      _Min = _Max;
      _Max = Temp;
    }

    const int Value = _Max - _Min;

    return R % Value + _Min;
  }

  float Random::Range(float _Max, float _Min)const
  {
    const unsigned int R = Rand();

    if (_Min > _Max)
    {
      const float Temp = _Min;
      _Min = _Max;
      _Max = Temp;
    }

    const float Value = _Max - _Min;

    return (static_cast<float>(R) / UINT_MAX)*Value + _Min;
  }

  inline unsigned int Random::Rand()const
  {
    unsigned long Temp = (X_ ^ (X_ << 11));
    X_ = Y_;
    Y_ = Z_;
    Z_ = W_;

    return W_ = (W_ ^ (W_ >> 19)) ^ (Temp ^ (Temp >> 8));
  }
}
