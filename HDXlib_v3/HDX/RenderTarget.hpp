#pragma once
#include "Color.hpp"
#include "Type2.hpp"

struct ID3D11ShaderResourceView;

namespace hdx
{
  class Degree;
  class PixelShader;
  class VertexShader;

  class RenderTarget
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    void CreateShaderResouceView();
  public:
    ID3D11ShaderResourceView** GetAddressOfShaderResourceView()const;
  public:
    RenderTarget();
    ~RenderTarget();
    void Set();
    void Restore();
    void Clear(const ColorF& _Color);
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = { 1.0f,1.0f,1.0f,1.0f }, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr);
  };
}
