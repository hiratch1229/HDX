#pragma once
#include "IRenderer2D.hpp"
#include "Src/Constants.hpp"

#include "Include/Type3.hpp"

#include <wrl.h>

class CRenderer2D : public IRenderer2D
{
  struct Vertex
  {
    hdx::float3 Position;
    hdx::float2 Texcoord;
  };
  struct Instance
  {
    DirectX::XMFLOAT4X4 NDCTransform;
    DirectX::XMFLOAT4 TexcoordTransfrom;
    hdx::ColorF Color;
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
private:
  ID3D11DeviceContext* pImmediateContext_ = nullptr;
  ID3D11RenderTargetView** ppRenderTargetView_ = nullptr;
  ID3D11DepthStencilView* pDepthStencilView_ = nullptr;
private:
  Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;
  Microsoft::WRL::ComPtr<ID3D11Buffer> pInstanceBuffer_;
  Instance* Instances_ = nullptr;
  int Count_ = 0;
private:
  hdx::BlendState BlendState_ = hdx::BlendState::Default;
  ConstantBufferData VertexStageConstantBuffers_[kConstantBufferMaxNum];
  ConstantBufferData PixelStageConstantBuffers_[kConstantBufferMaxNum];
  hdx::RasterizerState RasterizerState_ = hdx::RasterizerState::Default2D;
  hdx::DepthStencilState DepthStencilState_ = hdx::DepthStencilState::Default2D;
  hdx::RenderTarget RenderTarget_;
  hdx::SamplerState SamplerStatus_[kSamplerStateMaxNum] = { hdx::SamplerState::Default2D };
  hdx::Texture Textures_[kTextureMaxNum];
  hdx::VertexShader VertexShader_;
  hdx::PixelShader PixelShader_;
private:
  void Begin();
  void CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget);
  void SetViewPort(const hdx::float2& _Size);
public:
  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)override;

  void Draw(const hdx::Texture& _Texture, const hdx::float2& _DstLeftTop, const hdx::float2& _DstSize, const hdx::float2& _SrcLeftPos, const hdx::float2& _SrcSize, const hdx::Radian& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const hdx::ColorF& _Color)override;

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
};

