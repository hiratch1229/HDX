#pragma once
#include "IRenderer3D.hpp"
#include "Src/Constants.hpp"

#include <wrl.h>

class CRenderer3D : public IRenderer3D
{
  struct CommonConstantBuffer
  {
    DirectX::XMFLOAT4X4 ViewProjectionMatrix;
    DirectX::XMFLOAT4X4 GlobalTransform;
    DirectX::XMFLOAT4 LightDirection;     //  ライト進行方向
    hdx::ColorF DiffuseColor;

    DirectX::XMFLOAT4X4 BoneTransforms[kModelBoneMaxNum];
  };
  struct ConstantBufferData
  {
    UINT Size = 0;
    void* pData;
  public:
    ConstantBufferData() = default;
    ConstantBufferData(UINT _Size, void* _pData)
      : Size(_Size), pData(_pData)
    {

    }
  };
  struct Instance
  {
    DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
    hdx::ColorF MaterialColor;                //  材質色
  };
private:
  ID3D11DeviceContext* pImmediateContext_ = nullptr;
  ID3D11RenderTargetView** ppRenderTargetView_ = nullptr;
  ID3D11DepthStencilView* pDepthStencilView_ = nullptr;
private:
  Microsoft::WRL::ComPtr<ID3D11Buffer> pInstanceBuffer_;
  Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout_;
  Instance* Instances_ = nullptr;
  int Count_ = 0;
  hdx::Model Model_;
  hdx::MotionData MotionData_;
  DirectX::XMFLOAT4X4 BoneNothingMatrix_;
private:
  hdx::BlendState BlendState_ = hdx::BlendState::Default;
  hdx::ConstantBuffer<CommonConstantBuffer> ConstantBuffer_;
  ConstantBufferData VertexStageConstantBuffers_[kConstantBufferMaxNum - 1];
  ConstantBufferData PixelStageConstantBuffers_[kConstantBufferMaxNum - 1];
  hdx::RasterizerState RasterizerState_ = hdx::RasterizerState::Default3D;
  hdx::DepthStencilState DepthStencilState_ = hdx::DepthStencilState::Default3D;
  hdx::RenderTarget RenderTarget_;
  hdx::SamplerState SamplerStatus_[kSamplerStateMaxNum] = { hdx::SamplerState::Default3D };
  hdx::Texture Textures_[kTextureMaxNum - 1];
  hdx::VertexShader VertexShader_;
  hdx::PixelShader PixelShader_;
  hdx::Camera Camera_;
  DirectX::XMFLOAT4X4 ViewMatrix_;
  DirectX::XMFLOAT4X4 ProjectionMatrix_;
private:
  void Begin();
  void CalcView();
  void CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget);
  void SetViewPort(const hdx::float2& _Size);
public:
  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)override;

  void Draw(const hdx::Model& _Model, const hdx::Matrix& _WorldMatrix, const hdx::MotionData& _MotionData, const hdx::ColorF& _Color)override;

  void Flush()override;

  void SetBlendState(const hdx::BlendState& _BlendState)override;

  void SetConstantBuffer(hdx::ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot)override;

  void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)override;

  void SetRasterizerState(const hdx::RasterizerState& _RasterizerState)override;

  void SetRenderTarget(const hdx::RenderTarget& _RenderTarget)override;

  void SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)override;

  void SetTexture(const hdx::Texture& _Texture, UINT _Slot)override;

  void SetVertexShader(const hdx::VertexShader& _VertexShader)override;

  void SetPixelShader(const hdx::PixelShader& _PixelShader)override;

  void RestoreRenderTarget()override;

  void SetLightDirection(const hdx::float3& _LightDirection)override;

  void SetCamera(const hdx::Camera& _Camera)override;

  void CalcProjection()override;

  void FreeCamera()override;

  hdx::Matrix GetProjectionMatrix()const override;

  hdx::Matrix GetViewMatrix()const override;
};
