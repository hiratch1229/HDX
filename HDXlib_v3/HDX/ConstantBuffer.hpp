#pragma once
#include <SimpleMath.h>
#include <HDX/Color.hpp>

namespace hdx
{
  struct ConstantBuffer
  {
    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ワールド・ビュー・プロジェクション合成行列
    DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
    ColorF MaterialColor;                     //  材質色
    DirectX::XMFLOAT4 LightDirection;         //  ライト進行方向
  };
}
