#pragma once

//*************************
//  システム系
//*************************

//  システム
//  2018.07.31  作成
//  2018.10.29  エンジンと分割して管理に変更
#include "Include/System.hpp"


//*************************
//  入力系
//*************************

//  ボタンやキーの入力
//  2018.08.25  作成
//  2018.08.26  組み合わせを実装
//  TODO:組み合わせを3つ以上指定出来るように
#include "Include/Button.hpp"

//  キーボード
//  2018.08.25  作成
#include "Include/Keyboard.hpp"

//  マウス
//  2018.08.26  作成 
#include "Include/Mouse.hpp"

//  XInputコントローラ
//  2018.09.20  作成
#include "Include/XInput.hpp"

//  DirectInputコントローラ
//  2018.09.02  作成 
#include "Include/Gamepad.hpp"


//*************************
//  グラフィック系
//*************************

//  色
//  2018.08.09  作成
#include "Include/Color.hpp"

//  2D画像
//  2018.08.09  作成
//  TODO:もっと簡単に描画出来るように
//  2018.11.14  バッチ処理に変更
#include "Include/Texture.hpp"

//  3Dモデル
//  2018.09.26  作成
//  2018.11.22  GeometricPrimitiveとSkinnedMeshを統合
#include "Include/Model.hpp"

//  カメラ
//  2018.11.21  作成
#include "Include/Camera.hpp"

//  レンダラー2D
//  2018.10.28  作成
#include "Include/Renderer2D.hpp"

//  レンダラー3D
//  2018.11.21  作成
#include "Include/Renderer3D.hpp"

//  ブレンドステート
//  2018.10.29  作成
#include "Include/BlendState.hpp"

//  サンプラーステート
//  2018.11.06  作成
#include "Include/SamplerState.hpp"

//  ラスタライーザーステート
//  2018.11.07  作成
#include "Include/RasterizerState.hpp"

//  デプスステンシルステート
//  2018.11.07  作成
#include "Include/DepthStencilState.hpp"

//  コンスタントバッファ
//  2018.11.21  作成
#include "Include/ConstantBuffer.hpp"

//  レンダーターゲット
//  2018.11.07  作成
#include "Include/RenderTarget.hpp"


//*************************
//  シェーダー系
//*************************

//  コンスタントバッファ
#include "Include/ConstantBuffer.hpp"

//  頂点シェーダー
//  2018.09.30  作成
#include "Include/VertexShader.hpp"

//  ピクセルシェーダー
//  2018.09.30  作成
#include "Include/PixelShader.hpp"


//*************************
//  サウンド系
//*************************

//  サウンド
//  2018.09.02  作成
//  2018.11.24  管理クラス(ISound)作成
#include "Include/Sound.hpp"


//*************************
//  数学系
//*************************

//  数学定数
//  2018.08.09  作成
#include "Include/MathConstants.hpp"

//  数学
//  2018.08.09  作成
#include "Include/Math.hpp"


//*************************
//  基本系
//*************************

//  float,int2つの型
//  2018.08.09  作成
//  2019.02.07  templateクラス化
#include "Include/Type2.hpp"

//  float,int3つの型
//  2018.08.09  作成
//  2019.02.07  templateクラス化
#include "Include/Type3.hpp"

//  float,int4つの型
//  2019.02.07  作成
#include "Include/Type4.hpp"

//  角度自動正規化クラス
//  2018.08.09  作成
#include "Include/Angle.hpp"

//  行列クラス
//  2018.11.19  作成
#include "Include/Matrix.hpp"


//*************************
//  便利系
//*************************

//  ランダム(Xorshift)クラス
//  2018.09.23  作成
#include "Include/Random.hpp"

//  コピー禁止クラス
//  2018.07.31  作成
#include "Include/NonCopy.hpp"

//  シングルトン(デザインパターン)
//  2018.07.31  作成
#include "Include/Singleton.hpp"

//  イージング
//  2018.09.02  作成
#include "Include/Easing.hpp"

//  マクロ
//  2018.09.03  作成
#include "Include/Macro.hpp"

//  GUI
//  2018.11.18  作成
//  TODO:使い勝手向上
#include "Include/GUI.hpp"


//*************************
//  便利系
//*************************

//  定数
//  2019.02.02
#include "Include/Constants.hpp"


//--------------------------------------------------

//  メモリリーク詳細表示
#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
