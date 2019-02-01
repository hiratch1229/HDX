#pragma once
#include "Include/BlendState.hpp"
#include "Include/ConstantBuffer.hpp"
#include "Include/DepthStencilState.hpp"
#include "Include/RasterizerState.hpp"
#include "Include/RenderTarget.hpp"
#include "Include/SamplerState.hpp"
#include "Include/VertexShader.hpp"
#include "Include/PixelShader.hpp"

#include <d3d11.h>

class IRenderer2D
{
public:
  static IRenderer2D* Create();

  IRenderer2D() = default;

  virtual ~IRenderer2D() = default;

  virtual void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView) = 0;

  virtual void Draw(const hdx::Texture& _Texture, const hdx::float2& _DstLeftTop, const hdx::float2& _DstSize, const hdx::float2& _SrcLeftPos, const hdx::float2& _SrcSize, const hdx::Radian& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const hdx::ColorF& _Color) = 0;

  virtual void Flush() = 0;

  virtual void SetBlendState(const hdx::BlendState& _BlendState) = 0;

  virtual void SetConstantBuffer(hdx::ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot) = 0;

  virtual void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState) = 0;

  virtual void SetRasterizerState(const hdx::RasterizerState& _RasterizerState) = 0;

  virtual void SetRenderTarget(const hdx::RenderTarget& _RenderTarget) = 0;

  virtual void SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot) = 0;

  virtual void SetTexture(const hdx::Texture& _Texture, UINT _Slot) = 0;

  virtual void SetVertexShader(const hdx::VertexShader& _VertexShader) = 0;

  virtual void SetPixelShader(const hdx::PixelShader& _PixelShader) = 0;

  virtual void RestoreRenderTarget() = 0;
};


//#include "Src/Renderer/IRenderer.hpp"
//
//namespace hdx
//{
//  class VertexShader;
//  class PixelShader;
//  class BlendState;
//  class SamplerState;
//  class RasterizerState;
//  class DepthStencilState;
//  class Texture;
//  class RenderTarget;
//
//  struct float2;
//  class Radian;
//  struct ColorF;
//}
//
//class IRenderer2D : public IRenderer
//{
//public:
//  void SetVertexShader(const hdx::VertexShader& _VertexShader);
//  void SetPixelShader(const hdx::PixelShader& _PixelShader);
//  void SetBlendState(const hdx::BlendState& _BlendState);
//  void SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot);
//  void SetRasterizerState(const hdx::RasterizerState& _RasterizerState);
//  void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState);
//  void SetTexture(const hdx::Texture& _Texture, UINT _Slot);
//  void RestoreRenderTarget();
//  void SetRenderTarget(const hdx::RenderTarget& _RenderTarger);
//private:
//  void Begin(const hdx::Texture& _Texture);
//public:
//  void End();
//  void Draw(const hdx::Texture& _Texture, const hdx::float2& _DstLeftTop, const hdx::float2& _DstSize, const hdx::float2& _SrcLeftPos, const hdx::float2& _SrcSize, const hdx::Radian& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const hdx::ColorF& _Color);
//public:
//  IRenderer2D();
//public:
//  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView);
//};
