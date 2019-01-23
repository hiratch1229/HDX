#pragma once
#include "Include/Types.hpp"

class IRandom
{
public:
  static IRandom* Create();

  IRandom() = default;

  virtual ~IRandom() = default;

  virtual UINT Get() = 0;

  virtual void SetSeed(UINT _Seed) = 0;
};
