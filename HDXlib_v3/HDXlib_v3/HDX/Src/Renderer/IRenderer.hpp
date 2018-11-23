#pragma once
#include "../../Include/Types.hpp"

struct ID3D11DeviceContext;
struct ID3D11ShaderResourceView;
struct ID3D11BlendState;
struct ID3D11VertexShader;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
struct ID3D11Buffer;
struct ID3D11SamplerState;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct D3D11_MAPPED_SUBRESOURCE;

class IRenderer
{
protected:
  void SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot);
  void SetBlendState(ID3D11BlendState* _pBlendState);
  void SetInputLayout(ID3D11InputLayout* _pInputLayout);
  void SetVertexShader(ID3D11VertexShader* _pVertexShader);
  void SetPixelShader(ID3D11PixelShader* _pPixelShader);
  void SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot = 0);
  void SetIndexBuffer(ID3D11Buffer* _pIndexBuffer);
  void SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot);
  void SetRasterizerState(ID3D11RasterizerState* _pRasterizerState);
  void SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState);
  void SetRenderTarget(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView);
  void SetConstatBuffer(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot);
  void UpdateSubresource(ID3D11Buffer* _pConstantBuffer, const void* _pSrcData);
protected:
  void Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce);
  void Unmap(ID3D11Buffer* _pVertexBuffer);
protected:
  void DrawIndexed(UINT _IndexCount, UINT _StartIndexLocation, UINT _BaseVertexLocation);
  void DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation);
protected:
  void Initialize(ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView);
};
