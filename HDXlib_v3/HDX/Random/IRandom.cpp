#include <HDX/Random/IRandom.hpp>

#include <random>

namespace detail
{
  IRandom::IRandom()
  {
    SetSeed(std::random_device()());
  }

  uint IRandom::Get()
  {
    unsigned long Temp = (X_ ^ (X_ << 11));
    X_ = Y_;
    Y_ = Z_;
    Z_ = W_;

    return W_ = (W_ ^ (W_ >> 19)) ^ (Temp ^ (Temp >> 8));
  }
}
