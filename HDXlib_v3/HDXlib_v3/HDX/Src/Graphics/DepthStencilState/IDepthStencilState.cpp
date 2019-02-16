#include "IDepthStencilState.hpp"

#include "CDepthStencilState.hpp"

IDepthStencilState* IDepthStencilState::Create()
{
  return new CDepthStecilState;
}
