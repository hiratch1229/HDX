#include "CRandom.hpp"

#include "Src/Engine.hpp"
#include "Src/Misc.hpp"
#include "Include/Types.hpp"

#include <random>

CRandom::CRandom()
{
  TIMER_START("Random");

  SetSeed(std::random_device()());

  TIMER_END("Random");
}

UINT CRandom::Get()
{
  ULONG Temp = (X_ ^ (X_ << 11));
  X_ = Y_;
  Y_ = Z_;
  Z_ = W_;
  
  return W_ = (W_ ^ (W_ >> 19)) ^ (Temp ^ (Temp >> 8));
}
