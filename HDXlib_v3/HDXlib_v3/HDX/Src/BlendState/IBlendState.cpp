#include "IBlendState.hpp"

#include "CBlendState.hpp"

IBlendState* IBlendState::Create()
{
  return new CBlendState;
}
