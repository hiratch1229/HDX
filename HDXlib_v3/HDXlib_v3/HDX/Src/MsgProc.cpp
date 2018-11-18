#include "Engine.hpp"

#include "System/ISystem.hpp"
#include "Input/Mouse/IMouse.hpp"

#include <Windows.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  //  ImGui�̃��b�Z�[�W�v���V�[�W��
  ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

  switch (msg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_PAINT:
    ValidateRect(hWnd, NULL);
    break;
    //  �L�[����������
  case WM_KEYDOWN:
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
    //  �}�E�X�z�C�[����]
  case WM_MOUSEWHEEL:
    Engine::GetMouse()->SetWheel(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)));
    break;
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }

  return 0;
}
