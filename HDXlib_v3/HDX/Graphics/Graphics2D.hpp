#pragma once

//  ���C�u����
namespace hdx
{
  class VertexShader;
  class PixelShader;
  class BlendState;

  namespace Graphics2D
  {
    void SetVertexShader(const VertexShader& _VertexShader);
    void RestoreVertexShader();
    void SetPixelShader(const PixelShader& _PixelShader);
    void RestorePixelShader();
    void SetBlendState(const BlendState& _BlendState);
  };
}
