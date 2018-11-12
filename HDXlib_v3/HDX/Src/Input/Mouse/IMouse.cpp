#include "../../Input/Mouse/IMouse.hpp"

#include "../../Engine.hpp"
#include "../../Input/Keyboard/IKeyboard.hpp"

#include <Windows.h>

//  更新
void IMouse::Update()
{
  static constexpr int kVirtualCodes[kButtonNum] = { VK_LBUTTON, VK_MBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

  for (int i = 0; i < kButtonNum; ++i)
  {
    InputStatus_[i].Update(Engine::GetKeyboard()->Press(kVirtualCodes[i]));
  }

  //  カーソルの移動量と座標を保存
  {
    //  現在のカーソルの位置
    POINT Point;
    ::GetCursorPos(&Point);

    //  現在のカーソルの位置
    const hdx::int2 CursorPos = { static_cast<int>(Point.x), static_cast<int>(Point.y) };

    //  移動量を保存
    Delta_ = CursorPos - Pos_;

    //  座標を保存
    Pos_ = CursorPos;

    Wheel_ = 0;
  }
}


//--------------------------------------------------

//  座標を変更
void IMouse::SetPos(const hdx::int2& _Pos)
{
  Pos_ = _Pos;

  //  ウィンドウの中心にカーソルをセット
  ::SetCursorPos(Pos_.X, Pos_.Y);
}
