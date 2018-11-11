#include "../Include/System.hpp"

#include "Engine/Engine.hpp"
#include "../Include/Renderer2D.hpp"

#include <Windows.h>
#include <crtdbg.h>

#include <time.h>
#include <locale>

#include "Resource.hpp"

//  メッセージプロシージャのプロトタイプ宣言
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//  メイン関数のプロトタイプ宣言
void Main();

//  エントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  //  メモリリーク検出
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  //  時間でランダム
  srand(static_cast<UINT>(time(nullptr)));

  //  日本語に設定
  setlocale(LC_CTYPE, "jpn");

  //  ウィンドウクラスの登録
  WNDCLASSEX WindowClass;
  {
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_CLASSDC;
    WindowClass.lpfnWndProc = MsgProc;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = hInstance;
    WindowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    WindowClass.hCursor = nullptr;
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WindowClass.lpszMenuName = nullptr;
    WindowClass.lpszClassName = L"HDXlib";
    WindowClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINI_ICON));
    RegisterClassEx(&WindowClass);
  }

  //  エンジンの作成
  detail::Engine Engine;

  //  シェーダーの初期設定
  {
    //  2D
    {
      hdx::Renderer2D::RestoreVertexShader();
      hdx::Renderer2D::RestorePixelShader();
    }
    //  3D
    {

    }
  }

  //  プログラムの実行
  Main();

  //  ソフト終了
  return 0;
}
