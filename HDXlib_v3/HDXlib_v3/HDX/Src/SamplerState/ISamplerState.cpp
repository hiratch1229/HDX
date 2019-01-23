#include "ISamplerState.hpp"

#include "CSamplerState.hpp"

ISamplerState* ISamplerState::Create()
{
  return new CSamplerState;
}
