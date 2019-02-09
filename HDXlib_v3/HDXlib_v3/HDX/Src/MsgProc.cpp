#include "Src/Engine.hpp"

#include "Src/System/ISystem.hpp"
#include "Src/Input/Mouse/IMouse.hpp"

#include "imgui.h"

#include <Windows.h>

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_PAINT:
    ValidateRect(hWnd, NULL);
    break;
    //  キーを押した時
  case WM_KEYDOWN:
    switch (wParam)
    {
    case VK_ESCAPE:
      Engine::Get<ISystem>()->Exit();
      break;
    case VK_F2:
      Engine::Get<ISystem>()->ScreenShot();
      break;
    case VK_F11:
      Engine::Get<ISystem>()->ChangeWindowMode();
      break;
    }
    break;
    //  マウスホイール垂直回転
  case WM_MOUSEWHEEL:
    Engine::Get<IMouse>()->SetWheel(hdx::int2(0, static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam))));
    break;
    //  マウスホイール水平回転
  case WM_MOUSEHWHEEL:
    Engine::Get<IMouse>()->SetWheel(hdx::int2(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)), 0));
    break;
  case WM_CHAR:
    // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
    if (wParam > 0 && wParam < 0x10000)
    {
      ImGui::GetIO().AddInputCharacter((unsigned short)wParam);
    }
    break;
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }

  return 0;
}
