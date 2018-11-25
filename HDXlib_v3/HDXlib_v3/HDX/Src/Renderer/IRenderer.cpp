#include "IRenderer.hpp"

#include "../../Include/Constants.hpp"

#include <d3d11.h>

namespace
{
  ID3D11DeviceContext* pImmediateContext = nullptr;
  ID3D11RenderTargetView** ppRenderTargetView = nullptr;
  ID3D11DepthStencilView* pDepthStencilView = nullptr;
}

void IRenderer::Initialize(ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  pImmediateContext = _pImmediateContext;
  ppRenderTargetView = _ppRenderTargetView;
  pDepthStencilView = _pDepthStencilView;
}

void IRenderer::SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot)
{
  static ID3D11ShaderResourceView*const* ppShaderResourceViews[hdx::Constants::TextureMaxNum]{};

  ID3D11ShaderResourceView*const*& ppShaderResourceView = ppShaderResourceViews[_Slot];
  if (ppShaderResourceView == _ppShaderResourceView)return;

  ppShaderResourceView = _ppShaderResourceView;
  //  Ý’è‚ð”½‰f
  pImmediateContext->PSSetShaderResources(_Slot, 1, ppShaderResourceView);
}

void IRenderer::SetBlendState(ID3D11BlendState* _pBlendState)
{
  static ID3D11BlendState* pBlendState = nullptr;
  if (pBlendState == _pBlendState)return;

  pBlendState = _pBlendState;
  //  Ý’è‚ð”½‰f
  pImmediateContext->OMSetBlendState(pBlendState, nullptr, 0xFFFFFFFF);
}

void IRenderer::SetInputLayout(ID3D11InputLayout* _pInputLayout)
{
  static ID3D11InputLayout* pInputLayout = nullptr;
  if (pInputLayout == _pInputLayout)return;

  pInputLayout = _pInputLayout;
  //  Ý’è‚ð”½‰f
  pImmediateContext->IASetInputLayout(pInputLayout);
}

void IRenderer::SetVertexShader(ID3D11VertexShader* _pVertexShader)
{
  static ID3D11VertexShader* pVertexShader = nullptr;
  if (pVertexShader == _pVertexShader)return;

  pVertexShader = _pVertexShader;
  //  Ý’è‚ð”½‰f
  pImmediateContext->VSSetShader(pVertexShader, nullptr, 0);
}

void IRenderer::SetPixelShader(ID3D11PixelShader* _pPixelShader)
{
  static ID3D11PixelShader* pPixelShader = nullptr;
  if (pPixelShader == _pPixelShader)return;

  pPixelShader = _pPixelShader;
  //  Ý’è‚ð”½‰f
  pImmediateContext->PSSetShader(pPixelShader, nullptr, 0);
}

void IRenderer::SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot)
{
  static ID3D11Buffer*const* ppVertexBuffer[2];
  if (ppVertexBuffer[_Slot] == _ppVertexBuffer)return;

  ppVertexBuffer[_Slot] = _ppVertexBuffer;
  UINT Offset = 0;

  //  Ý’è‚ð”½‰f
  pImmediateContext->IASetVertexBuffers(_Slot, 1, ppVertexBuffer[_Slot], &_Strides, &Offset);
}

void IRenderer::SetIndexBuffer(ID3D11Buffer* _pIndexBuffer)
{
  static ID3D11Buffer* pIndexBuffer = nullptr;
  if (pIndexBuffer == _pIndexBuffer)return;

  pIndexBuffer = _pIndexBuffer;
  //  Ý’è‚ð”½‰f
  pImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void IRenderer::SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot)
{
  static ID3D11SamplerState*const* ppSamplerStatus[hdx::Constants::SamplerStateMaxNum]{};

  ID3D11SamplerState*const*& ppSamplerState = ppSamplerStatus[_Slot];
  if (ppSamplerState == _ppSamplerState)return;

  ppSamplerState = _ppSamplerState;
  //  Ý’è‚ð”½‰f
  pImmediateContext->PSSetSamplers(_Slot, 1, ppSamplerState);
}

void IRenderer::SetRasterizerState(ID3D11RasterizerState* _pRasterizerState)
{
  static ID3D11RasterizerState* pRasterizerState = nullptr;
  if (pRasterizerState == _pRasterizerState)return;

  pRasterizerState = _pRasterizerState;
  //  Ý’è‚ð”½‰f
  pImmediateContext->RSSetState(pRasterizerState);
}

void IRenderer::SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
{
  static ID3D11DepthStencilState* pDepthStencilState = nullptr;
  if (pDepthStencilState == _pDepthStencilState)return;

  pDepthStencilState = _pDepthStencilState;
  //  Ý’è‚ð”½‰f
  pImmediateContext->OMSetDepthStencilState(pDepthStencilState, 1);
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

    bool operator==(const State& _State)const
    {
      return ppRenderTargetView == _State.ppRenderTargetView && pDepthStencilView == _State.pDepthStencilView;
    }
  };

  static State CurrentState;

  State _State = (_ppRenderTargetView == nullptr && _pDepthStencilView == nullptr)
    ? State(ppRenderTargetView, pDepthStencilView) : State(_ppRenderTargetView, _pDepthStencilView);

  if (CurrentState == _State)return;

  CurrentState = _State;
  pImmediateContext->OMSetRenderTargets(1, CurrentState.ppRenderTargetView, CurrentState.pDepthStencilView);
}

void IRenderer::SetConstatBufferVS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot)
{
  static ID3D11Buffer*const* pConstantBuffers[hdx::Constants::ConstantBufferMaxNum]{};

  ID3D11Buffer*const*& pConstantBuffer = pConstantBuffers[_Slot];
  if (pConstantBuffer == _ppConstantBuffer)return;

  pConstantBuffer = _ppConstantBuffer;
  //  Ý’è‚ð”½‰f
  pImmediateContext->VSSetConstantBuffers(_Slot, 1, pConstantBuffer);
}

void IRenderer::SetConstatBufferPS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot)
{
  static ID3D11Buffer*const* pConstantBuffers[hdx::Constants::ConstantBufferMaxNum]{};

  ID3D11Buffer*const*& pConstantBuffer = pConstantBuffers[_Slot];
  if (pConstantBuffer == _ppConstantBuffer)return;

  pConstantBuffer = _ppConstantBuffer;
  //  Ý’è‚ð”½‰f
  pImmediateContext->PSSetConstantBuffers(_Slot, 1, pConstantBuffer);
}

void IRenderer::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY _Topology)
{
  static D3D_PRIMITIVE_TOPOLOGY Topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
  if (Topology == _Topology)return;

  Topology = _Topology;
  //  Ý’è‚ð”½‰f
  pImmediateContext->IASetPrimitiveTopology(Topology);
}

void IRenderer::SetViewPort(const hdx::int2& _Size)
{
  UINT ViewPortNum = 1;

  D3D11_VIEWPORT ViewPort;
  pImmediateContext->RSGetViewports(&ViewPortNum, &ViewPort);

  ViewPort.Width = static_cast<float>(_Size.X);
  ViewPort.Height = static_cast<float>(_Size.Y);

  pImmediateContext->RSSetViewports(1, &ViewPort);
}

void IRenderer::UpdateSubresource(ID3D11Buffer* _pConstantBuffer, const void* _pSrcData)
{
  pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, 0, _pSrcData, 0, 0);
}

void IRenderer::Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce)
{
  pImmediateContext->Map(_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, _pMappedSubresorce);
}

void IRenderer::Unmap(ID3D11Buffer* _pVertexBuffer)
{
  pImmediateContext->Unmap(_pVertexBuffer, 0);
}

void IRenderer::DrawIndexed(UINT _IndexCount, UINT _StartIndexLocation, UINT _BaseVertexLocation)
{
  pImmediateContext->DrawIndexed(_IndexCount, _StartIndexLocation, _BaseVertexLocation);
}

void IRenderer::DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation)
{
  pImmediateContext->DrawInstanced(_VertexCountPerInstance, _InstanceCount, _StartVertexLocation, _StartInstanceLocation);
}
