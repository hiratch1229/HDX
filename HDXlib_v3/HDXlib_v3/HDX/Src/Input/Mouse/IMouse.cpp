#include "Src/Input/Mouse/IMouse.hpp"

#include "CMouse.hpp"

IMouse* IMouse::Create()
{
  return new CMouse;
}
