#include "Engine.hpp"

#include "System/ISystem.hpp"
#include "Input/Mouse/IMouse.hpp"

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
  case WM_KEYDOWN:      //  キーを押した時
    switch (wParam)
    {
    case VK_ESCAPE:
      Engine::GetSystem()->Exit();
      break;
    case VK_F2:
      Engine::GetSystem()->ScreenShot();
      break;
    case VK_F11:
      Engine::GetSystem()->ChangeWindowMode();
      break;
    }
    break;
  case WM_MOUSEWHEEL:   //  マウスホイール回転
    Engine::GetMouse()->SetWheel(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)));
    break;
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }

  return 0;
}
