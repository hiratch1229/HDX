#pragma once
#include "IRenderer.hpp"

#include "Src/Constants.hpp"

class CRenderer : public IRenderer
{
  ID3D11DeviceContext* pImmediateContext_ = nullptr;
  ID3D11RenderTargetView** ppRenderTargetView_ = nullptr;
  ID3D11DepthStencilView* pDepthStencilView_ = nullptr;
public:
  void Initialize(ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)override;

  void DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation)override;

  void DrawIndexedInstanced(UINT _IndexCountPerInstance, UINT _InstanceCount, UINT _StartIndexLocation, INT _BaseVertexLocation, UINT _StartInstanceLocation)override;

  void Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce)override;

  void Unmap(ID3D11Buffer* _pVertexBuffer)override;

  void UpdateSubresource(ID3D11Buffer* _pConstantBuffer, const void* _pSrcData)override;

  void SetBlendState(ID3D11BlendState* _pBlendState)override;

  void SetConstatBufferVS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot)override;

  void SetConstatBufferPS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot)override;

  void SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)override;

  void SetRasterizerState(ID3D11RasterizerState* _pRasterizerState)override;

  void SetRenderTarget(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)override;

  void SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot)override;

  void SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot)override;

  void SetVertexShader(ID3D11VertexShader* _pVertexShader)override;

  void SetPixelShader(ID3D11PixelShader* _pPixelShader)override;

  void SetInputLayout(ID3D11InputLayout* _pInputLayout)override;

  void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY _Topology)override;

  void SetViewPort(const hdx::int2& _Size)override;

  void SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot)override;

  void SetIndexBuffer(ID3D11Buffer* _pIndexBuffer)override;
};
