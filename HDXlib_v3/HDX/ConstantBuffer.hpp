#pragma once
#include <SimpleMath.h>
#include <HDX/Color.hpp>

namespace hdx
{
  struct ConstantBuffer
  {
    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ���[���h�E�r���[�E�v���W�F�N�V���������s��
    DirectX::XMFLOAT4X4 World;                //  ���[���h�ϊ��s��
    ColorF MaterialColor;                     //  �ގ��F
    DirectX::XMFLOAT4 LightDirection;         //  ���C�g�i�s����
  };
}
