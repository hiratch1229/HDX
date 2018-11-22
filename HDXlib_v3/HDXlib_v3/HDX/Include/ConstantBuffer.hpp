#pragma once
//#include <SimpleMath.h>
//#include "Color.hpp"
//
//namespace hdx
//{
//  struct ConstantBuffer
//  {
//    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ���[���h�E�r���[�E�v���W�F�N�V���������s��
//    DirectX::XMFLOAT4X4 World;                //  ���[���h�ϊ��s��
//    ColorF MaterialColor;                     //  �ގ��F
//    DirectX::XMFLOAT4 LightDirection;         //  ���C�g�i�s����
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
    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ���[���h�E�r���[�E�v���W�F�N�V���������s��
    DirectX::XMFLOAT4X4 World;                //  ���[���h�ϊ��s��
    ColorF MaterialColor;                     //  �ގ��F
    DirectX::XMFLOAT4 LightDirection;         //  ���C�g�i�s����
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
