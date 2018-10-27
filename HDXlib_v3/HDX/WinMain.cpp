#include <HDX/System.hpp>

#include <HDX/Engine.hpp>
#include <HDX/ISystem.hpp>

#include <Windows.h>
#include <crtdbg.h>

#include <time.h>
#include <locale>

//  メイン関数のプロトタイプ宣言
void Main();

//  メッセージプロシージャ
//LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//  return detail::Engine::GetSystem()->MsgProc(hWnd, msg, wParam, lParam);
//}

namespace detail
{
  LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

//  エントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  //  メモリリーク検出
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  //  時間でランダム
  srand(static_cast<unsigned int>(time(nullptr)));

  //  日本語に設定
  setlocale(LC_CTYPE, "jpn");

  //  ウィンドウクラスの登録
  WNDCLASSEX WindowClass;
  {
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_CLASSDC;
    WindowClass.lpfnWndProc = detail::MsgProc;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = hInstance;
    WindowClass.hIcon = nullptr;
    WindowClass.hCursor = nullptr;
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WindowClass.lpszMenuName = nullptr;
    WindowClass.lpszClassName = L"HDXlib";
    WindowClass.hIconSm = nullptr;
    RegisterClassEx(&WindowClass);
  }

  //  ウィンドウ&デバイス&スワップチェーン生成
  //detail::System::Get()->CreateWindowAndDeviceAndSwapChain(hInstance);

  detail::Engine Engine;

  //  プログラムの実行
  Main();

  //  ソフト終了
  return 0;
}
