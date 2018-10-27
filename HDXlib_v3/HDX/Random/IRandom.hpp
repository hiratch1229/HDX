#pragma once
#include <HDX/Types.hpp>

namespace detail
{
  class IRandom
  {
    static constexpr uint kInitX = 123456789U;
    static constexpr uint kInitY = 362436069U;
    static constexpr uint kInitZ = 521288629U;
    static constexpr uint kInitW = 88675123U;
  private:
    uint X_ = kInitX;
    uint Y_ = kInitY;
    uint Z_ = kInitZ;
    uint W_ = kInitW;
  public:
    void SetSeed(uint _Seed)
    {
      X_ = kInitX;
      Y_ = kInitY;
      Z_ = kInitZ;
      W_ = _Seed;
    }
  public:
    IRandom();
    ~IRandom() {}
    uint Get();
  };
}
