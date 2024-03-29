#include "Include/System.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Constants.hpp"

#include "Include/Type2.hpp"

#include <Windows.h>

namespace hdx
{
  //**************************************************
  //**************************************************
  //  Systemクラス
  //**************************************************
  //**************************************************

  //  更新
  int System::Update()
  {
    return Engine::Get<ISystem>()->Update();
  }

  //  画面幅を取得
  int System::GetWindowWidth()
  {
    return Engine::Get<ISystem>()->GetWindowSize().x;
  }

  //  画面高を取得
  int System::GetWindowHeight()
  {
    return Engine::Get<ISystem>()->GetWindowSize().y;
  }

  //  画面サイズを取得
  const int2& System::GetWindowSize()
  {
    return Engine::Get<ISystem>()->GetWindowSize();
  }

  //  経過時間を取得
  float System::GetDeltaTime()
  {
    return Engine::Get<ISystem>()->GetDeltaTime();
  }

  //  現在のフレームレートを取得
  int System::GetFPS()
  {
    return Engine::Get<ISystem>()->GetFPS();
  }

  //  ウィンドウの設定
  void System::SetWindowLeftTopPos(int _LeftPos, int _TopPos)
  {
    Engine::Get<ISystem>()->SetWindowLeftTopPos({ _LeftPos, _TopPos });
  }

  //  ウィンドウの設定
  void System::SetWindowLeftTopPos(const int2& _LeftTopPos)
  {
    Engine::Get<ISystem>()->SetWindowLeftTopPos(_LeftTopPos);
  }

  //  ウィンドウの設定
  void System::SetWindowSize(int _Width, int _Height)
  {
    Engine::Get<ISystem>()->SetWindowSize({ _Width, _Height });
  }

  //  ウィンドウの設定
  void System::SetWindowSize(const int2& _Size)
  {
    Engine::Get<ISystem>()->SetWindowSize(_Size);
  }

  //  ウィンドウの設定
  void System::SetWindowMode(bool _isFullScreen)
  {
    Engine::Get<ISystem>()->SetWindowMode(_isFullScreen);
  }

  //  ウィンドウの設定
  void System::SettingWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen)
  {
    Engine::Get<ISystem>()->SetWindow({ _LeftPos, _TopPos }, { _Width, _Height }, _isFullScreen);
  }

  //  ウィンドウの設定
  void System::SettingWindow(const int2& _LeftTopPos, const int2& _Size, bool _isFullScreen)
  {
    Engine::Get<ISystem>()->SetWindow(_LeftTopPos, _Size, _isFullScreen);
  }

  //  カーソル表示設定
  void System::ShowCursor(bool _isShowCursor)
  {
    Engine::Get<ISystem>()->ShowCursor(_isShowCursor);
  }

  //  ウィンドウのタイトルを設定
  void System::SetTitle(const char* _Title)
  {
    Engine::Get<ISystem>()->SetTitle(_Title);
  }

  //  背景の色変更
  void System::SetBackColor(const ColorF& _Color)
  {
    Engine::Get<ISystem>()->SetBackColor(_Color);
  }

  void System::SetFPS(UINT _MaxFPS)
  {
    Engine::Get<ISystem>()->SetFPS(_MaxFPS);
  }

  //  ウィンドウのモードを変更
  void System::ChangeWindowMode()
  {
    Engine::Get<ISystem>()->ChangeWindowMode();
  }

  //  ウィンドウのタイトルを変更
  void System::RenameTitle(const char* _Title)
  {
    Engine::Get<ISystem>()->RenameTitle(_Title);
  }

  //  スクリーンショット
  void System::ScreenShot()
  {
    Engine::Get<ISystem>()->ScreenShot();
  }

  //  出力に文字を描画
  void System::OutputDebug(const char* _Str)
  {
    wchar_t Str[kCharMaxNum];
    mbstowcs_s(nullptr, Str, _Str, kCharMaxNum);
    OutputDebugString(Str);
  }

  //  ソフトを終了
  void System::Exit()
  {
    Engine::Get<ISystem>()->Exit();
  }
}
