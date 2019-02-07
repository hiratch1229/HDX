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

//  更新
void CMouse::Update()
{
  static constexpr int kVirtualCodes[kButtonNum] = { VK_LBUTTON, VK_MBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

  for (int i = 0; i < kButtonNum; ++i)
  {
    InputStatus_[i].Update(Engine::Get<IKeyboard>()->Press(kVirtualCodes[i]));
  }

  //  カーソルの移動量と座標を保存
  {
    //  現在のカーソルの位置
    POINT Point;
    ::GetCursorPos(&Point);

    //  現在のカーソルの位置
    const hdx::int2 CursorPos = hdx::int2(Point.x / DpiScale_.x, Point.y / DpiScale_.y);

    //  移動量を保存
    Delta_ = CursorPos - Pos_;

    //  座標を保存
    Pos_ = CursorPos;

    Wheel_ = 0;
  }
}

//  座標を変更
void CMouse::SetPos(const hdx::int2& _Pos)
{
  Pos_ = _Pos;

  //  ウィンドウの中心にカーソルをセット
  ::SetCursorPos(Pos_.x, Pos_.y);
}
