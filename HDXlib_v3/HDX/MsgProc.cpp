#include <Windows.h>

#include <HDX/Engine.hpp>

#include <HDX/System/ISystem.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>

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
  case WM_KEYDOWN:      //  �L�[����������
    switch (wParam)
    {
    case VK_ESCAPE:
      detail::Engine::GetSystem()->Exit();
      break;
    case VK_F2:
      detail::Engine::GetSystem()->ScreenShot();
      break;
    case VK_F11:
      detail::Engine::GetSystem()->ChangeWindowMode();
      break;
    }
    break;
  case WM_LBUTTONDOWN:  //  �}�E�X���{�^������������
    detail::Engine::GetMouse()->ButtonPressed(detail::MouseButtons::Left);
    break;
  case WM_LBUTTONUP:    //  �}�E�X���{�^���𗣂�����
    detail::Engine::GetMouse()->ButtonReleased(detail::MouseButtons::Left);
    break;
  case WM_RBUTTONDOWN:  //  �}�E�X�E�{�^������������
    detail::Engine::GetMouse()->ButtonPressed(detail::MouseButtons::Right);
    break;
  case WM_RBUTTONUP:    //  �}�E�X�E�{�^���𗣂�����
    detail::Engine::GetMouse()->ButtonReleased(detail::MouseButtons::Right);
    break;
  case WM_MBUTTONDOWN:  //  �}�E�X���{�^������������
    detail::Engine::GetMouse()->ButtonPressed(detail::MouseButtons::Middle);
    break;
  case WM_MBUTTONUP:    //  �}�E�X���{�^���𗣂�����
    detail::Engine::GetMouse()->ButtonReleased(detail::MouseButtons::Middle);
    break;
  case WM_MOUSEWHEEL:   //  �}�E�X�z�C�[����]
    detail::Engine::GetMouse()->SetWheel(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)));
    break;
  case WM_XBUTTONDOWN:  //  �}�E�XX�{�^���̂ǂ��炩����������
    switch (GET_XBUTTON_WPARAM(wParam))
    {
    case XBUTTON1:  //  X1�{�^��
      detail::Engine::GetMouse()->ButtonPressed(detail::MouseButtons::X1);
      break;
    case XBUTTON2:  //  X2�{�^��
      detail::Engine::GetMouse()->ButtonPressed(detail::MouseButtons::X2);
      break;
    }
    break;
  case WM_XBUTTONUP:    //  �}�E�XX�{�^���̂ǂ��炩�𗣂�����
    switch (GET_XBUTTON_WPARAM(wParam))
    {
    case XBUTTON1:  //  X1�{�^��
      detail::Engine::GetMouse()->ButtonReleased(detail::MouseButtons::X1);
      break;
    case XBUTTON2:  //  X2�{�^��
      detail::Engine::GetMouse()->ButtonReleased(detail::MouseButtons::X2);
      break;
    }
    break;
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }

  return 0;
}
