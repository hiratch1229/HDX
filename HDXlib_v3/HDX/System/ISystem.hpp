#pragma once
#include <HDX/Type2.hpp>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11ShaderResourceView;
struct ID3D11BlendState;
struct ID3D11VertexShader;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
struct ID3D11Buffer;
struct ID3D11SamplerState;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;
struct D3D11_MAPPED_SUBRESOURCE;
struct HWND__;
typedef struct HWND__ *HWND;

namespace hdx
{
  class BlendState;
  struct ColorF;
}

namespace detail
{
  class ISystem
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    int GetWindowWidth()const;
    int GetWindowHeight()const;
    const hdx::int2& GetWindowSize()const;
  public:
    void SetWindowLeftTopPos(int _LeftPos, int _TopPos);
    void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos);
    void SetWindowSize(int _Width, int _Height);
    void SetWindowSize(const hdx::int2& _Size);
    void SetWindowMode(bool _isFullScreen);
    void SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen);
    void SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen);
    void ShowCursor(bool _isShowCursor);
    void SetTitle(const char* _Title);
    void SetBackColor(const hdx::ColorF& _Color);
  public:
    void ChangeWindowMode();
    void RenameTitle(const char* _Title);
    void ScreenShot();
    void Exit();
  public:
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetImmediateContext();
    IDXGISwapChain* GetSwapChain();
    HWND GetHWND();
  public:
    void SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, int _Slot);
    void SetBlendState(ID3D11BlendState* _pBlendState);
    void SetInputLayout(ID3D11InputLayout* _pInputLayout);
    void SetVertexShader(ID3D11VertexShader* _pVertexShader);
    void SetPixelShader(ID3D11PixelShader* _pPixelShader);
    void SetVertexBuffers(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides);
    void SetSamplersState(ID3D11SamplerState*const* _ppSamplerState);
    void SetRasterizerState(ID3D11RasterizerState* _pRasterizerState);
    void SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState);
  public:
    void Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce);
    void Unmap(ID3D11Buffer* _pVertexBuffer);
  public:
    bool Update();
  public:
    ISystem();
    ~ISystem();
  };
}
