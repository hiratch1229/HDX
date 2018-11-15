#include "IKeyboard.hpp"

#include "../../Engine.hpp"

#include <Windows.h>

IKeyboard::IKeyboard()
{
  Engine::End("Keyboard");
}

//  ��Ԃ̍X�V
void IKeyboard::Update()
{
  BYTE buf[256];
  //  �S�ẴL�[�̏����擾
  ::GetKeyboardState(buf);

  //  �S�ẴL�[�̏����X�V
  for (int i = 0; i < kKeyNum; ++i)
  {
    InputStatus_[i].Update((buf[i] & 0x8000) != 0);
  }
}
