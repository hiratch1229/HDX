#include "IKeyboard.hpp"

#include <Windows.h>

//  ��Ԃ̍X�V
void IKeyboard::Update()
{
  BYTE buf[256];
  //  �S�ẴL�[�̏����擾
  ::GetKeyboardState(buf);

  //  �S�ẴL�[�̏����X�V
  for (int i = 0; i < kKeyNum; ++i)
  {
    InputStatus_[i].Update((buf[i] & 0x80) != 0);
  }
}
