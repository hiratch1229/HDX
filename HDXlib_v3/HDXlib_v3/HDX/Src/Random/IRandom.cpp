#include "Src/Random/IRandom.hpp"

#include "Src/Engine.hpp"
#include "Src/Misc.hpp"

#include <random>

IRandom::IRandom()
{
  TIMER_START("Random");

  SetSeed(std::random_device()());

  TIMER_END("Random");
}

UINT IRandom::Get()
{
  unsigned long Temp = (X_ ^ (X_ << 11));
  X_ = Y_;
  Y_ = Z_;
  Z_ = W_;

  return W_ = (W_ ^ (W_ >> 19)) ^ (Temp ^ (Temp >> 8));
}
