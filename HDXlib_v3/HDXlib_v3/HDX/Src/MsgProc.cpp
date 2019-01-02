#include "Src/Engine.hpp"

#include "Src/System/ISystem.hpp"
#include "Src/Input/Mouse/IMouse.hpp"

#include <Windows.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  //  ImGuiのメッセージプロシージャ
  ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

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
    //  マウスホイール回転
  case WM_MOUSEWHEEL:
    Engine::Get<IMouse>()->SetWheel(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)));
    break;
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }

  return 0;
}
