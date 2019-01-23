#include "IGamepad.hpp"

#include "CGamepad.hpp"

IGamepad* IGamepad::Create()
{
  return new CGamepad;
}
