#include "IKeyboard.hpp"

#include <Windows.h>

//  状態の更新
void IKeyboard::Update()
{
  BYTE buf[256];
  //  全てのキーの情報を取得
  ::GetKeyboardState(buf);

  //  全てのキーの情報を更新
  for (int i = 0; i < kKeyNum; ++i)
  {
    InputStatus_[i].Update((buf[i] & 0x80) != 0);
  }
}
