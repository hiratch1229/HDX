#include "Src/Input/Mouse/IMouse.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Keyboard/IKeyboard.hpp"

#include <Windows.h>

IMouse::IMouse()
{
  HDC hdc = ::GetDC(::GetDesktopWindow());
  DpiScale_ = { ::GetDeviceCaps(hdc , LOGPIXELSX), ::GetDeviceCaps(hdc , LOGPIXELSY) };
  DpiScale_ /= 96.0f;
}

//  �X�V
void IMouse::Update()
{
  static constexpr int kVirtualCodes[kButtonNum] = { VK_LBUTTON, VK_MBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

  for (int i = 0; i < kButtonNum; ++i)
  {
    InputStatus_[i].Update(Engine::Get<IKeyboard>()->Press(kVirtualCodes[i]));
  }

  //  �J�[�\���̈ړ��ʂƍ��W��ۑ�
  {
    //  ���݂̃J�[�\���̈ʒu
    POINT Point;
    ::GetCursorPos(&Point);

    //  ���݂̃J�[�\���̈ʒu
    const hdx::int2 CursorPos = hdx::int2(static_cast<int>(Point.x), static_cast<int>(Point.y)) / DpiScale_;

    //  �ړ��ʂ�ۑ�
    Delta_ = CursorPos - Pos_;

    //  ���W��ۑ�
    Pos_ = CursorPos;

    Wheel_ = 0;
  }
}


//--------------------------------------------------

//  ���W��ύX
void IMouse::SetPos(const hdx::int2& _Pos)
{
  Pos_ = _Pos;

  //  �E�B���h�E�̒��S�ɃJ�[�\�����Z�b�g
  ::SetCursorPos(Pos_.X, Pos_.Y);
}
