#include "IKeyboard.hpp"

#include "CKeyboard.hpp"

IKeyboard* IKeyboard::Create()
{
  return new CKeyboard;
}
