#pragma once
#include "Include/Type2.hpp"

#include <d3d11.h>

class IRenderer
{
public:
  static IRenderer* Get();

  IRenderer() = default;

  virtual ~IRenderer() = default;

  virtual void Initialize(ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView) = 0;

  virtual void DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation) = 0;

  virtual void DrawIndexedInstanced(UINT _IndexCountPerInstance, UINT _InstanceCount, UINT _StartIndexLocation, INT _BaseVertexLocation, UINT _StartInstanceLocation) = 0;

  virtual void Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce) = 0;

  virtual void Unmap(ID3D11Buffer* _pVertexBuffer) = 0;

  virtual void UpdateSubresource(ID3D11Buffer* _pConstantBuffer, const void* _pSrcData) = 0;

  virtual void SetBlendState(ID3D11BlendState* _pBlendState) = 0;

  virtual void SetConstatBufferVS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot) = 0;

  virtual void SetConstatBufferPS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot) = 0;

  virtual void SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState) = 0;

  virtual void SetRasterizerState(ID3D11RasterizerState* _pRasterizerState) = 0;

  virtual void SetRenderTarget(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView) = 0;

  virtual void SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot) = 0;

  virtual void SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot) = 0;

  virtual void SetVertexShader(ID3D11VertexShader* _pVertexShader) = 0;

  virtual void SetPixelShader(ID3D11PixelShader* _pPixelShader) = 0;

  virtual void SetInputLayout(ID3D11InputLayout* _pInputLayout) = 0;

  virtual void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY _Topology) = 0;

  virtual void SetViewPort(const hdx::int2& _Size) = 0;
  
  virtual void SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot) = 0;

  virtual void SetIndexBuffer(ID3D11Buffer* _pIndexBuffer) = 0;
};

//#include "Include/Type2.hpp"
//#include "Include/Types.hpp"
//
//#include <d3d11.h>
//
//class IRenderer
//{
//protected:
//  void SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, UINT _Slot);
//  void SetBlendState(ID3D11BlendState* _pBlendState);
//  void SetInputLayout(ID3D11InputLayout* _pInputLayout);
//  void SetVertexShader(ID3D11VertexShader* _pVertexShader);
//  void SetPixelShader(ID3D11PixelShader* _pPixelShader);
//  void SetVertexBuffer(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides, UINT _Slot = 0);
//  void SetIndexBuffer(ID3D11Buffer* _pIndexBuffer);
//  void SetSamplersState(ID3D11SamplerState*const* _ppSamplerState, UINT _Slot);
//  void SetRasterizerState(ID3D11RasterizerState* _pRasterizerState);
//  void SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState);
//  void SetRenderTarget(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView);
//  void SetConstatBufferVS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot);
//  void SetConstatBufferPS(ID3D11Buffer*const* _ppConstantBuffer, UINT _Slot);
//  void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY _Topology);
//  void SetViewPort(const hdx::int2& _Size);
//  void UpdateSubresource(ID3D11Buffer* _pConstantBuffer, const void* _pSrcData);
//protected:
//  void Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce);
//  void Unmap(ID3D11Buffer* _pVertexBuffer);
//protected:
//  void DrawIndexed(UINT _IndexCount, UINT _StartIndexLocation, UINT _BaseVertexLocation);
//  void DrawInstanced(UINT _VertexCountPerInstance, UINT _InstanceCount, UINT _StartVertexLocation, UINT _StartInstanceLocation);
//  void DrawIndexedInstanced(UINT _IndexCountPerInstance, UINT _InstanceCount, UINT _StartIndexLocation, INT _BaseVertexLocation, UINT _StartInstanceLocation);
//protected:
//  void Initialize(ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView);
//};
