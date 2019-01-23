#include "IRandom.hpp"

#include "CRandom.hpp"

IRandom* IRandom::Create()
{
  return new CRandom;
}
