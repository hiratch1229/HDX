#pragma once
#include "IGUI.hpp"
#include "imgui.h"

#include "Include/Type2.hpp"
#include "Include/VertexShader.hpp"
#include "Include/PixelShader.hpp"

#include <wrl.h>
#include <memory>

class CGUI : public IGUI
{
  class Win32
  {
    static constexpr hdx::float2 kWindowFrameSize = hdx::float2(8, 35);
  private:
    const HWND hWnd_;
    ImGuiMouseCursor LastMouseCursor_ = ImGuiMouseCursor_COUNT;
  public:
    Win32(const HWND& _hWnd);

    void NewFrame();
  };
  class DX11
  {
    static constexpr int kVertexBufferExtraSize = 5000;
    static constexpr int kIndexBufferExtraSize = 10000;
  private:
    struct VertexConstantBuffer
    {
      float   mvp[4][4];
    };
  private:
    ID3D11Device* pDevice_;
    ID3D11DeviceContext* pImmediateContext_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexConstantBuffer_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRsterizerState_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pFont_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer_;
    ID3D11VertexShader* pVertexShader_;
    ID3D11PixelShader* pPixelShader_;
  private:
    int VertexBufferSize_ = kVertexBufferExtraSize;
    int IndexBufferSize_ = kIndexBufferExtraSize;
  public:
    DX11(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext);

    ~DX11() = default;

    void Render(ImDrawData* _pDrawData);
  };
private:
  std::unique_ptr<Win32> pWin32_;
  std::unique_ptr<DX11> pDX11_;
public:
  ~CGUI();

  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, const HWND& _hWnd)override;

  void Update()override;
};
