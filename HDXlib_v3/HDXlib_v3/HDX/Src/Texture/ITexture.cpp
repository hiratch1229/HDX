#include "ITexture.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../NumberMap.hpp"
#include "../Misc.hpp"

#include "../../Include/RenderTarget.hpp"
#include "../../Include/Type2.hpp"
#include "../../Include/Constants.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <wincodec.h>
#include <assert.h>

namespace
{
  class Image
  {
    static constexpr int kPixelBytes = 4;
  public:
    const hdx::int2 Size_;
  private:
    std::vector<unsigned char> Buffer_;
  public:
    int Stride()const { return Size_.X*kPixelBytes; }
    unsigned char* Buffer() { return &Buffer_[0]; }
    size_t BufferSize()const { return Buffer_.size(); }
  public:
    Image(const hdx::int2& _Size)
      : Size_(_Size), Buffer_(_Size.X*_Size.Y*kPixelBytes)
    {

    }
  };

  struct TextureData
  {
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
    hdx::int2 Size;
  };

  int CreateTextureNum = 0;
  Microsoft::WRL::ComPtr<IWICImagingFactory> pFactory;
  NumberMap<std::string, TextureData> TextureMap;
  ID3D11Device* pDevice = nullptr;
  IDXGISwapChain* pSwapChain = nullptr;

  int CreateDammyTexture(const hdx::int2& _Size)
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    //  シェーダーリソースビュー設定で作成
    D3D11_TEXTURE2D_DESC Texture2dDesc{};
    {
      Texture2dDesc.Width = _Size.X;
      Texture2dDesc.Height = _Size.Y;
      Texture2dDesc.MipLevels = 1;
      Texture2dDesc.ArraySize = 1;
      Texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      Texture2dDesc.SampleDesc.Count = 1;
      Texture2dDesc.SampleDesc.Quality = 0;
      Texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
      Texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
      Texture2dDesc.CPUAccessFlags = 0;
      Texture2dDesc.MiscFlags = 0;
    }

    //  白色設定で作成
    D3D11_SUBRESOURCE_DATA SubresourceData{};
    {
      u_int color = 0xFFFFFFFF;
      SubresourceData.pSysMem = &color;
      SubresourceData.SysMemPitch = 4;
      SubresourceData.SysMemSlicePitch = 4;
    }

    //  Texture2Dを作成
    Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2d;
    {
      hr = pDevice->CreateTexture2D(&Texture2dDesc, &SubresourceData, pTexture2d.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    }

    //  シェーダーリソースビューをスワップチェーン設定で作成
    D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
    {
      DXGI_SWAP_CHAIN_DESC SwapChainDesc;
      pSwapChain->GetDesc(&SwapChainDesc);
      ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
      ShaderResourceViewDesc.Texture2D.MipLevels = 1;
    }

    //  シェーダーリソースビューを作成
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResouceView;
    {
      hr = pDevice->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResouceView.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    }

    char FileName[hdx::MaxCharLimit];
    sprintf_s(FileName, "CreateTextureNumber%d", CreateTextureNum++);

    //  マップへ追加
    return TextureMap.insert(FileName, { pShaderResouceView, _Size });
  }
}

ITexture::ITexture()
{
  TIMER_START("Texture");

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(pFactory.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  TIMER_END("Texture");
}

void ITexture::Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain)
{
  pDevice = _pDevice;
  pSwapChain = _pSwapChain;
  CreateDammyTexture(kDummyTextureSize);
}

int ITexture::Load(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = TextureMap.find(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<IWICBitmapDecoder> Decoder;

  //  char型→wchar_t型に変換
  wchar_t wFilePath[hdx::MaxCharLimit];
  mbstowcs_s(nullptr, wFilePath, _FilePath, hdx::MaxCharLimit);

  hr = pFactory->CreateDecoderFromFilename(wFilePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, Decoder.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> Frame;
  hr = Decoder->GetFrame(0, Frame.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  hdx::int2 Size;
  {
    UINT Width, Height;
    hr = Frame->GetSize(&Width, &Height);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    Size = { static_cast<int>(Width), static_cast<int>(Height) };
    assert(Size.X > 0 && Size.Y > 0);
  }

  WICPixelFormatGUID PixelFormat;
  hr = Frame->GetPixelFormat(&PixelFormat);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  Image Image(Size);

  if (PixelFormat != GUID_WICPixelFormat32bppRGBA)
  {
    Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;

    hr = pFactory->CreateFormatConverter(pConverter.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    hr = pConverter->Initialize(Frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeCustom);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    hr = pConverter->CopyPixels(0, Image.Stride(), Image.BufferSize(), Image.Buffer());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }
  else
  {
    hr = Frame->CopyPixels(0, Image.Stride(), Image.BufferSize(), Image.Buffer());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  D3D11_TEXTURE2D_DESC Texture2dDesc;
  Texture2dDesc.Width = Image.Size_.X;
  Texture2dDesc.Height = Image.Size_.Y;
  Texture2dDesc.MipLevels = 1;
  Texture2dDesc.ArraySize = 1;
  Texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  Texture2dDesc.SampleDesc.Count = 1;
  Texture2dDesc.SampleDesc.Quality = 0;
  Texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
  Texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  Texture2dDesc.CPUAccessFlags = 0;
  Texture2dDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA InitializeData;
  InitializeData.pSysMem = Image.Buffer();
  InitializeData.SysMemPitch = Image.Stride();
  InitializeData.SysMemSlicePitch = Image.BufferSize();

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2d;

  hr = pDevice->CreateTexture2D(&Texture2dDesc, &InitializeData, pTexture2d.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  pSwapChain->GetDesc(&SwapChainDesc);
  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  ShaderResourceViewDesc.Texture2D.MipLevels = 1;

  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
  hr = pDevice->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResourceView.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return TextureMap.insert(_FilePath, { pShaderResourceView, Size });
}

int ITexture::Add(const hdx::int2& _Size)
{
  return CreateDammyTexture(_Size);
}

const hdx::int2& ITexture::GetSize(int _ID)
{
  return TextureMap[_ID].Size;
}

ID3D11ShaderResourceView** ITexture::GetShaderResourceView(int _ID)
{
  return TextureMap[_ID].pShaderResourceView.GetAddressOf();
}

void ITexture::SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView)
{
  const int ID = _RenderTarget.GetID();

  //pImpl_->TextureMap_[ID].pShaderResourceView.Reset();
  //pImpl_->TextureMap_[ID].pShaderResourceView = _pShaderResouceView;
}
