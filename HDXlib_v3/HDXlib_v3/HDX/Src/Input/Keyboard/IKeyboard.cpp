#include "IKeyboard.hpp"

#include "../../Engine.hpp"

#include <Windows.h>

IKeyboard::IKeyboard()
{
  Engine::End("Keyboard");
}

//  状態の更新
void IKeyboard::Update()
{
  BYTE buf[256];
  //  全てのキーの情報を取得
  ::GetKeyboardState(buf);

  //  全てのキーの情報を更新
  for (int i = 0; i < kKeyNum; ++i)
  {
    InputStatus_[i].Update((buf[i] & 0x8000) != 0);
  }
}
