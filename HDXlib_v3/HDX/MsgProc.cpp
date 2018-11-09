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
  case WM_KEYDOWN:      //  キーを押した時
    switch (wParam)
    {
    case VK_ESCAPE:
      GetSystem()->Exit();
      break;
    case VK_F2:
      GetSystem()->ScreenShot();
      break;
    case VK_F11:
      GetSystem()->ChangeWindowMode();
      break;
    }
    break;
  case WM_LBUTTONDOWN:  //  マウス左ボタンを押した時
    GetMouse()->ButtonPressed(detail::MouseButtons::Left);
    break;
  case WM_LBUTTONUP:    //  マウス左ボタンを離した時
    GetMouse()->ButtonReleased(detail::MouseButtons::Left);
    break;
  case WM_RBUTTONDOWN:  //  マウス右ボタンを押した時
    GetMouse()->ButtonPressed(detail::MouseButtons::Right);
    break;
  case WM_RBUTTONUP:    //  マウス右ボタンを離した時
    GetMouse()->ButtonReleased(detail::MouseButtons::Right);
    break;
  case WM_MBUTTONDOWN:  //  マウス中ボタンを押した時
    GetMouse()->ButtonPressed(detail::MouseButtons::Middle);
    break;
  case WM_MBUTTONUP:    //  マウス中ボタンを離した時
    GetMouse()->ButtonReleased(detail::MouseButtons::Middle);
    break;
  case WM_MOUSEWHEEL:   //  マウスホイール回転
    GetMouse()->SetWheel(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)));
    break;
  case WM_XBUTTONDOWN:  //  マウスXボタンのどちらかを押した時
    switch (GET_XBUTTON_WPARAM(wParam))
    {
    case XBUTTON1:  //  X1ボタン
      GetMouse()->ButtonPressed(detail::MouseButtons::X1);
      break;
    case XBUTTON2:  //  X2ボタン
      GetMouse()->ButtonPressed(detail::MouseButtons::X2);
      break;
    }
    break;
  case WM_XBUTTONUP:    //  マウスXボタンのどちらかを離した時
    switch (GET_XBUTTON_WPARAM(wParam))
    {
    case XBUTTON1:  //  X1ボタン
      GetMouse()->ButtonReleased(detail::MouseButtons::X1);
      break;
    case XBUTTON2:  //  X2ボタン
      GetMouse()->ButtonReleased(detail::MouseButtons::X2);
      break;
    }
    break;
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }

  return 0;
}
