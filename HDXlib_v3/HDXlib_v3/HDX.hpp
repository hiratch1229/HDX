#pragma once

//*************************
//  システム系
//*************************

//  システム
//  2018.07.31  作成
//  TODO:前バージョンからほとんど持ってきたので、色々改善
#include "HDX/Include/System.hpp"


//*************************
//  入力系
//*************************

//  ボタンやキーの入力
//  2018.08.25  作成
//  2018.08.26  組み合わせを実装
//  TODO:組み合わせを3つ以上指定出来るように
#include "HDX/Include/Button.hpp"

//  キーボード
//  2018.08.25  作成
#include "HDX/Include/Keyboard.hpp"

//  マウス
//  2018.08.26  作成 
#include "HDX/Include/Mouse.hpp"

//  XInputコントローラ
//  2018.09.20  作成
#include "HDX/Include/XInput.hpp"

//  DirectInputコントローラ
//  2018.09.02  作成 
#include "HDX/Include/Gamepad.hpp"


//*************************
//  グラフィック系
//*************************

//  色
//  2018.08.09  作成
#include "HDX/Include/Color.hpp"

//  2D画像
//  2018.08.09  作成
//  TODO:もっと簡単に描画出来るように
//  TODO:バッチ処理
#include "HDX/Include/Texture.hpp"

////  3D基本形オブジェクト
////  2018.09.26  作成
////  TODO:前バージョンからほとんど持ってきたので、色々改善
//#include "HDX/Include/GeometricPrimitive.hpp"

//  3Dモデル
//  2018.09.26  作成
//  TODO:前バージョンからほとんど持ってきたので、色々改善
#include "HDX/Include/Model.hpp"

////  FBXモデル
////  2018.09.28  作成
////  TODO:授業課題から改善
//#include "HDX/Include/GeometricPrimitive.hpp"

//  レンダラー2D
//  2018.10.28  作成
#include "HDX/Include/Renderer2D.hpp"

//  ブレンドステート
//  2018.10.29  作成
#include "HDX/Include/BlendState.hpp"

//  サンプラーステート
//  2018.11.06  作成
#include "HDX/Include/SamplerState.hpp"

//  ラスタライーザーステート
//  2018.11.07  作成
#include "HDX/Include/RasterizerState.hpp"

//  デプスステンシルステート
//  2018.11.07  作成
#include "HDX/Include/DepthStencilState.hpp"

//  レンダーターゲット
//  2018.11.07  作成
#include "HDX/Include/RenderTarget.hpp"


//*************************
//  シェーダー系
//*************************

//  コンスタントバッファ
#include "HDX/Include/ConstantBuffer.hpp"

//  インプットレイアウト
//  2018.10.04  作成
#include "HDX/Include/InputElementDesc.hpp"

//  頂点シェーダー
//  2018.09.30  作成
#include "HDX/Include/VertexShader.hpp"

//  ピクセルシェーダー
//  2018.09.30  作成
#include "HDX/Include/PixelShader.hpp"


//*************************
//  サウンド系
//*************************

//  サウンド
//  2018.09.02  作成
//  TODO:前バージョンからほとんど持ってきたので、色々改善
#include "HDX/Include/Sound.hpp"


//*************************
//  数学系
//*************************

//  数学定数
//  2018.08.09  作成
#include "HDX/Include/MathConstants.hpp"

//  数学
//  2018.08.09  作成
#include "HDX/Include/Math.hpp"


//*************************
//  基本系
//*************************

//  float,int2つの型
//  2018.08.09  作成
#include "HDX/Include/Type2.hpp"

//  float,int3つの型
//  2018.08.09  作成
#include "HDX/Include/Type3.hpp"

//  角度自動正規化クラス
//  2018.08.09  作成
#include "HDX/Include/Angle.hpp"

//  行列クラス
//  2018.11.19  作成
#include "HDX/Include/Matrix.hpp"


//*************************
//  便利系
//*************************

//  ランダム(Xorshift)クラス
//  2018.09.23  作成
#include "HDX/Include/Random.hpp"

//  コピー禁止クラス
//  2018.07.31  作成
#include "HDX/Include/NonCopy.hpp"

//  シングルトン(デザインパターン)
//  2018.07.31  作成
#include "HDX/Include/Singleton.hpp"

//  イージング
//  2018.09.02  作成
#include "HDX/Include/Easing.hpp"

//  マクロ
//  2018.09.03  作成
#include "HDX/Include/Macro.hpp"

//  GUI
//  2018.11.18  作成
//  TODO:サンプルのままなので使い勝手向上
#include "HDX/Include/GUI.hpp"

//--------------------------------------------------

//  メモリリーク詳細表示
#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


//--------------------------------------------------

//  文字列系の警告を無効化
#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE
