#pragma once
#include "Include/Types.hpp"

class IRandom
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
  void SetSeed(UINT _Seed)
  {
    X_ = kInitX;
    Y_ = kInitY;
    Z_ = kInitZ;
    W_ = _Seed;
  }
public:
  IRandom();
  ~IRandom() {}
  UINT Get();
};
