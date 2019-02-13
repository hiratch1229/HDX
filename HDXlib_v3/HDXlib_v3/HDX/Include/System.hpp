#pragma once
#include "Type2.hpp"
#include "Color.hpp"

//  ライブラリ
namespace hdx
{
  //  システム
  class System
  {
    System() = delete;
    System(const System&) = delete;
    System& operator=(const System&) = delete;
  public:
    //  画面幅を取得
    static int GetWindowWidth();
    //  画面高を取得
    static int GetWindowHeight();
    //  画面サイズを取得
    static const int2& GetWindowSize();
    //  経過時間を取得
    static float GetDeltaTime();
    //  現在のフレームレートを取得
    static int GetFPS();
  public:
    //  ウィンドウの設定
    //  _LeftPos:左上座標X
    //  _TopPos:左上座標Y
    static void SetWindowLeftTopPos(int _LeftPos, int _TopPos);
    //  ウィンドウの設定
    //  _LeftTopPos:左上座標
    static void SetWindowLeftTopPos(const int2& _LeftTopPos);
    //  ウィンドウの設定
    //  _Width:ウィンドウ幅
    //  _Height:ウィンドウ高
    static void SetWindowSize(int _Width, int _Height);
    //  ウィンドウの設定
    //  _Size:ウィンドウ縦横幅
    static void SetWindowSize(const int2& _Size);
    //  ウィンドウの設定
    //  _isFullScreen:画面モード(true:フルスクリーン,false:ウィンドウモード)
    static void SetWindowMode(bool _isFullScreen);
    //  ウィンドウの設定
    //  _LeftPos:左上座標X
    //  _TopPos:左上座標Y
    //  _Width:ウィンドウ幅
    //  _Height:ウィンドウ高
    //  _isFullScreen:画面モード(true:フルスクリーン,false:ウィンドウモード)
    static void SettingWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen = false);
    //  ウィンドウの設定
    //  _LeftTopPos:左上座標
    //  _Size:ウィンドウ縦横幅
    //  _isFullScreen:画面モード(true:フルスクリーン,false:ウィンドウモード)
    static void SettingWindow(const int2& _LeftTopPos, const int2& _Size, bool _isFullScreen = false);
    //  カーソル表示設定(true:表示,false:非表示)
    static void ShowCursor(bool _isShowCursor);
    //  ウィンドウのタイトルを設定
    static void SetTitle(const char* _Title);
    //  背景の色変更
    static void SetBackColor(const ColorF& _Color);
    //  フレームレート制御
    //  0で無制御
    static void SetFPS(UINT _MaxFPS);

    ////  ウィンドウのサイズを変更
    ////  _Width:ウィンドウ幅
    ////  _Height:ウィンドウ高 
    //static inline void ResizeWindow(int _Width, int _Height)
    //{
    //  detail::System::Get()->ResizeWindow(_Width, _Height);
    //}

    //  ウィンドウのモードを変更
    //  ウィンドウモード⇔フルスクリーン
    static void ChangeWindowMode();
    //  ウィンドウのタイトルを変更
    static void RenameTitle(const char* _Title);
    //  スクリーンショット
    //  SCREENSHOTフォルダに保存
    static void ScreenShot();
    //  出力に文字を描画
    static void OutputDebug(const char* _Str);
    //  ソフトを終了
    static void Exit();
  public:
    //  更新
    static int Update();
  };
};
