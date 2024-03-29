#pragma once
#include "IRandom.hpp"

class CRandom : public IRandom
{
  static constexpr UINT kInitX = 123456789U;
  static constexpr UINT kInitY = 362436069U;
  static constexpr UINT kInitZ = 521288629U;
  static constexpr UINT kInitW = 88675123U;
private:
  UINT X_ = kInitX;
  UINT Y_ = kInitY;
  UINT Z_ = kInitZ;
  UINT W_ = kInitW;
public:
  CRandom();

  UINT Get()override;

  void SetSeed(UINT _Seed)override
  {
    X_ = kInitX;
    Y_ = kInitY;
    Z_ = kInitZ;
    W_ = _Seed;
  }
};