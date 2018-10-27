#pragma once

//  ���C�u����
namespace hdx
{
  class VertexShader;
  class PixelShader;

  namespace Graphics2D
  {
    void SetVertexShader(const VertexShader& _VertexShader);
    void RestoreVertexShader();
    void SetPixelShader(const PixelShader& _PixelShader);
    void RestorePixelShader();
  };
}
