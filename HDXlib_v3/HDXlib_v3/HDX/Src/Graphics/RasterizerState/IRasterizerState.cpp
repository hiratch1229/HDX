#include "IRasterizerState.hpp"

#include "CRasterizerState.hpp"

IRasterizerState* IRasterizerState::Create()
{
  return new CRasterizerState;
}
