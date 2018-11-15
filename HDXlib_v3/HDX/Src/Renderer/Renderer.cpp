#include "Renderer.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"

#include "../../Include/Constants.hpp"

#include <d3d11.h>

namespace
{
  ID3D11DeviceContext* pImmediateContext = nullptr;
  ID3D11RenderTargetView** pRenderTargetView = nullptr;
  ID3D11DepthStencilView* pDepthStencilView = nullptr;
}

inline ID3D11DeviceContext* GetImmediateContext()
{
  if (!pImmediateContext)
  {
    pImmediateContext = Engine::GetSystem()->GetImmediateContext();
  }

  return pImmediateContext;
}

inline ID3D11RenderTargetView** GetRenderTargetView()
{
  if (!pRenderTargetView)
  {
    pRenderTargetView = Engine::GetSystem()->GetRenderTargetView();
  }

  return pRenderTargetView;
}

inline ID3D11DepthStencilView* GetDepthStencilView()
{
  if (!pDepthStencilView)
  {
    pDepthStencilView = Engine::GetSystem()->GetDepthStencilView();
  }

  return pDepthStencilView;
}

void IRenderer::SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot)
{
  static ID3D11ShaderResourceView*const* ppShaderResourceViews[hdx::TextureMaxNum] = { nullptr };

  ID3D11ShaderResourceView*const*& ppShaderResourceView = ppShaderResourceViews[_Slot];
  if (ppShaderResourceView != _ppShaderResourceView)
  {
    ppShaderResourceView = _ppShaderResourceView;
    //  設定を反映
    GetImmediateContext()->PSSetShaderResources(_Slot, 1, ppShaderResourceView);
  }
}

void IRenderer::SetBlendState(ID3D11BlendState* _pBlendState)
{
  static ID3D11BlendState* pBlendState = nullptr;

  //  現在のと同じなら設定しない
  if (pBlendState != _pBlendState)
  {
    pBlendState = _pBlendState;
    //  設定を反映
    GetImmediateContext()->OMSetBlendState(pBlendState, nullptr, 0xFFFFFFFF);
  }
}

void IRenderer::SetInputLayout(ID3D11InputLayout* _pInputLayout)
{
  static ID3D11InputLayout* pInputLayout = nullptr;
  if (pInputLayout != _pInputLayout)
  {
    pInputLayout = _pInputLayout;
    //  設定を反映
    GetImmediateContext()->IASetInputLayout(pInputLayout);
  }
}

void IRenderer::SetVertexShader(ID3D11VertexShader* _pVertexShader)
{
  static ID3D11VertexShader* pVertexShader = nullptr;
  if (pVertexShader != _pVertexShader)
  {
    pVertexShader = _pVertexShader;
    //  設定を反映
    GetImmediateContext()->VSSetShader(pVertexShader, nullptr, 0);
  }
}

void IRenderer::SetPixelShader(ID3D11PixelShader* _pPixelShader)
{
  static ID3D11PixelShader* pPixelShader = nullptr;
  if (pPixelShader != _pPixelShader)
  {
    pPixelShader = _pPixelShader;
    //  設定を反映
    GetImmediateContext()->PSSetShader(pPixelShader, nullptr, 0);
  }
}

void IRenderer::SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot)
{
  static ID3D11Buffer*const* ppVertexBuffer[2];
  if (ppVertexBuffer[_Slot] != _ppVertexBuffer)
  {
    ppVertexBuffer[_Slot] = _ppVertexBuffer;
    UINT Offset = 0;

    //  設定を反映
    GetImmediateContext()->IASetVertexBuffers(_Slot, 1, ppVertexBuffer[_Slot], &_Strides, &Offset);
  }
}

void IRenderer::SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot)
{
  static ID3D11SamplerState*const* ppSamplerStatus[hdx::SamplerStateMaxNum] = { nullptr };

  ID3D11SamplerState*const*& ppSamplerState = ppSamplerStatus[_Slot];
  if (ppSamplerState != _ppSamplerState)
  {
    ppSamplerState = _ppSamplerState;
    //  設定を反映
    GetImmediateContext()->PSSetSamplers(_Slot, 1, ppSamplerState);
  }
}

void IRenderer::SetRasterizerState(ID3D11RasterizerState* _pRasterizerState)
{
  static ID3D11RasterizerState* pRasterizerState = nullptr;
  if (pRasterizerState != _pRasterizerState)
  {
    pRasterizerState = _pRasterizerState;
    //  設定を反映
    GetImmediateContext()->RSSetState(pRasterizerState);
  }
}

void IRenderer::SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
{
  static ID3D11DepthStencilState* pDepthStencilState = nullptr;
  if (pDepthStencilState != _pDepthStencilState)
  {
    pDepthStencilState = _pDepthStencilState;
    //  設定を反映
    GetImmediateContext()->OMSetDepthStencilState(pDepthStencilState, 1);
  }
}

void IRenderer::SetRenderTarget(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  struct State
  {
    ID3D11RenderTargetView** ppRenderTargetView = nullptr;
    ID3D11DepthStencilView* pDepthStencilView = nullptr;
    State(ID3D11RenderTargetView** _ppRenderTargetView = nullptr, ID3D11DepthStencilView* _pDepthStencilView = nullptr)
      : ppRenderTargetView(_ppRenderTargetView), pDepthStencilView(_pDepthStencilView)
    {

    }
  };

  auto Comparison = [](const State& _State1, const State& _State2)->bool
  {
    return _State1.ppRenderTargetView == _State2.ppRenderTargetView && _State1.pDepthStencilView == _State2.pDepthStencilView;
  };

  static State CurrentState;

  State _State = (_ppRenderTargetView == nullptr && _pDepthStencilView == nullptr)
    ? State(GetRenderTargetView(), GetDepthStencilView()) : State(_ppRenderTargetView, _pDepthStencilView);

  if (!Comparison(CurrentState, _State))
  {
    CurrentState = _State;
    GetImmediateContext()->OMSetRenderTargets(1, CurrentState.ppRenderTargetView, CurrentState.pDepthStencilView);
  }
}

void IRenderer::Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce)
{
  GetImmediateContext()->Map(_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, _pMappedSubresorce);
}

void IRenderer::Unmap(ID3D11Buffer* _pVertexBuffer)
{
  GetImmediateContext()->Unmap(_pVertexBuffer, 0);
}

void IRenderer::DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation)
{
  GetImmediateContext()->DrawInstanced(_VertexCountPerInstance, _InstanceCount, _StartVertexLocation, _StartInstanceLocation);
}
