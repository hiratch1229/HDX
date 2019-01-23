#include "IXInput.hpp"

#include "CXInput.hpp"

IXInput* IXInput::Create()
{
  return new CXInput;
}
