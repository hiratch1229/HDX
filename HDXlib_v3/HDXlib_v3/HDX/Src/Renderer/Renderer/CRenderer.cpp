#include "CRenderer.hpp"

void CRenderer::Initialize(ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  pImmediateContext_ = _pImmediateContext;
  ppRenderTargetView_ = _ppRenderTargetView;
  pDepthStencilView_ = _pDepthStencilView;
}

void CRenderer::DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation)
{
  pImmediateContext_->DrawInstanced(_VertexCountPerInstance, _InstanceCount, _StartVertexLocation, _StartInstanceLocation);
}

void CRenderer::DrawIndexedInstanced(UINT _IndexCountPerInstance, UINT _InstanceCount, UINT _StartIndexLocation, INT _BaseVertexLocation, UINT _StartInstanceLocation)
{
  pImmediateContext_->DrawIndexedInstanced(_IndexCountPerInstance, _InstanceCount, _StartIndexLocation, _BaseVertexLocation, _StartInstanceLocation);
}

void CRenderer::Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce)
{
  pImmediateContext_->Map(_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, _pMappedSubresorce);
}

void CRenderer::Unmap(ID3D11Buffer* _pVertexBuffer)
{
  pImmediateContext_->Unmap(_pVertexBuffer, 0);
}

void CRenderer::UpdateSubresource(ID3D11Buffer* _pConstantBuffer, const void* _pSrcData)
{
  pImmediateContext_->UpdateSubresource(_pConstantBuffer, 0, 0, _pSrcData, 0, 0);
}

void CRenderer::SetBlendState(ID3D11BlendState* _pBlendState)
{
  pImmediateContext_->OMSetBlendState(_pBlendState, nullptr, 0xFFFFFFFF);
}

void CRenderer::SetConstatBufferVS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot)
{
  pImmediateContext_->VSSetConstantBuffers(_Slot, 1, _ppConstantBuffer);
}

void CRenderer::SetConstatBufferPS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot)
{
  pImmediateContext_->PSSetConstantBuffers(_Slot, 1, _ppConstantBuffer);
}

void CRenderer::SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
{
  pImmediateContext_->OMSetDepthStencilState(_pDepthStencilState, 1);
}

void CRenderer::SetRasterizerState(ID3D11RasterizerState* _pRasterizerState)
{
  pImmediateContext_->RSSetState(_pRasterizerState);
}

void CRenderer::SetRenderTarget(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  if (_ppRenderTargetView == nullptr && _pDepthStencilView == nullptr)
  {
    pImmediateContext_->OMSetRenderTargets(1, ppRenderTargetView_, pDepthStencilView_);
  }
  else
  {
    pImmediateContext_->OMSetRenderTargets(1, _ppRenderTargetView, _pDepthStencilView);
  }
}

void CRenderer::SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot)
{
  pImmediateContext_->PSSetSamplers(_Slot, 1, _ppSamplerState);
}

void CRenderer::SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot)
{
  pImmediateContext_->PSSetShaderResources(_Slot, 1, _ppShaderResourceView);
}

void CRenderer::SetVertexShader(ID3D11VertexShader* _pVertexShader)
{
  pImmediateContext_->VSSetShader(_pVertexShader, nullptr, 0);
}

void CRenderer::SetPixelShader(ID3D11PixelShader* _pPixelShader)
{
  pImmediateContext_->PSSetShader(_pPixelShader, nullptr, 0);
}

void CRenderer::SetInputLayout(ID3D11InputLayout* _pInputLayout)
{
  pImmediateContext_->IASetInputLayout(_pInputLayout);
}

void CRenderer::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY _Topology)
{
  pImmediateContext_->IASetPrimitiveTopology(_Topology);
}

void CRenderer::SetViewPort(const hdx::int2& _Size)
{
  D3D11_VIEWPORT ViewPort;
  UINT ViewPortNum = 1;

  //  Œ»Ý‚Ìƒf[ƒ^‚ðŽæ“¾
  pImmediateContext_->RSGetViewports(&ViewPortNum, &ViewPort);

  ViewPort.Width = static_cast<float>(_Size.X);
  ViewPort.Height = static_cast<float>(_Size.Y);

  //  Ý’è‚ð”½‰f
  pImmediateContext_->RSSetViewports(1, &ViewPort);
}

void CRenderer::SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot)
{
  UINT Offset = 0;
  pImmediateContext_->IASetVertexBuffers(_Slot, 1, _ppVertexBuffer, &_Strides, &Offset);
}

void CRenderer::SetIndexBuffer(ID3D11Buffer* _pIndexBuffer)
{
  pImmediateContext_->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
