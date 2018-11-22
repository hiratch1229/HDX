#pragma once
//#include <SimpleMath.h>
//#include "Color.hpp"
//
//namespace hdx
//{
//  struct ConstantBuffer
//  {
//    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ワールド・ビュー・プロジェクション合成行列
//    DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
//    ColorF MaterialColor;                     //  材質色
//    DirectX::XMFLOAT4 LightDirection;         //  ライト進行方向
//  };
//}
#include "Types.hpp"
#include "Color.hpp"
#include "Constants.hpp"

#include <DirectXMath.h>

namespace hdx
{
  struct Data
  {
    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ワールド・ビュー・プロジェクション合成行列
    DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
    ColorF MaterialColor;                     //  材質色
    DirectX::XMFLOAT4 LightDirection;         //  ライト進行方向
    DirectX::XMFLOAT4X4 BoneTransforms[kMaxBoneInfluences];
  };

  struct ConstantBuffer
  {
    static constexpr UINT Size = sizeof(Data);
  public:
    Data Data_;
  public:
    ConstantBuffer() = default;
  };
}
