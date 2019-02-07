#include "CMouse.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Keyboard/IKeyboard.hpp"

#include <Windows.h>

CMouse::CMouse()
{
  HDC hdc = ::GetDC(::GetDesktopWindow());
  DpiScale_ = { ::GetDeviceCaps(hdc , LOGPIXELSX), ::GetDeviceCaps(hdc , LOGPIXELSY) };
  DpiScale_ /= 96.0f;
}

//  �X�V
void CMouse::Update()
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
    const hdx::int2 CursorPos = hdx::int2(Point.x / DpiScale_.x, Point.y / DpiScale_.y);

    //  �ړ��ʂ�ۑ�
    Delta_ = CursorPos - Pos_;

    //  ���W��ۑ�
    Pos_ = CursorPos;

    Wheel_ = 0;
  }
}

//  ���W��ύX
void CMouse::SetPos(const hdx::int2& _Pos)
{
  Pos_ = _Pos;

  //  �E�B���h�E�̒��S�ɃJ�[�\�����Z�b�g
  ::SetCursorPos(Pos_.x, Pos_.y);
}
