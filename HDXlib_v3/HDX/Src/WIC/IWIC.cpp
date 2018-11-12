#include "IWIC.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../Texture/ITexture.hpp"

#include "../../Include/Type2.hpp"
#include "../../Include/Constants.hpp"

#include <d3d11.h>
#include <wincodec.h>
#include <wrl.h>
#include <vector>
#include <assert.h>

struct IWIC::Impl
{
  Microsoft::WRL::ComPtr<IWICImagingFactory> pFactory_;
public:
  Impl()
  {
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(pFactory_.GetAddressOf()));
    _ASSERT_EXPR(SUCCEEDED(hr), L"CoCreateInstance");
  }
};

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

IWIC::IWIC()
  : pImpl_(new Impl)
{

}

IWIC::~IWIC()
{
  delete pImpl_;
  pImpl_ = nullptr;
}

int IWIC::Load(const char* _FilePath)
{
  //  Šù‚Éì¬‚³‚ê‚Ä‚¢‚é‚©Šm”F
  {
    const int ID = Engine::GetTexture()->GetTextureID(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<IWICBitmapDecoder> Decoder;

  //  charŒ^¨wchar_tŒ^‚É•ÏŠ·
  wchar_t wFilePath[hdx::MaxCharLimit];
  mbstowcs_s(nullptr, wFilePath, _FilePath, hdx::MaxCharLimit);

  hr = pImpl_->pFactory_->CreateDecoderFromFilename(wFilePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, Decoder.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDecoderFromFilename");

  Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> Frame;
  hr = Decoder->GetFrame(0, Frame.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), L"GetFrame");

  hdx::int2 Size;
  {
    UINT Width, Height;
    hr = Frame->GetSize(&Width, &Height);
    _ASSERT_EXPR(SUCCEEDED(hr), L"GetSize");
    Size = { static_cast<int>(Width), static_cast<int>(Height) };
    assert(Size.X > 0 && Size.Y > 0);
  }

  WICPixelFormatGUID PixelFormat;
  hr = Frame->GetPixelFormat(&PixelFormat);
  _ASSERT_EXPR(SUCCEEDED(hr), L"GetPixelFormat");

  Image Image(Size);

  if (PixelFormat != GUID_WICPixelFormat32bppRGBA)
  {
    Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;

    hr = pImpl_->pFactory_->CreateFormatConverter(pConverter.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateFormatConverter");

    hr = pConverter->Initialize(Frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeCustom);
    _ASSERT_EXPR(SUCCEEDED(hr), L"Initialize");

    hr = pConverter->CopyPixels(0, Image.Stride(), Image.BufferSize(), Image.Buffer());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CopyPixels");
  }
  else
  {
    hr = Frame->CopyPixels(0, Image.Stride(), Image.BufferSize(), Image.Buffer());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CopyPixels");
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

  ISystem* pSystem = Engine::GetSystem();

  hr = pSystem->GetDevice()->CreateTexture2D(&Texture2dDesc, &InitializeData, pTexture2d.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");

  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  pSystem->GetSwapChain()->GetDesc(&SwapChainDesc);
  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  ShaderResourceViewDesc.Texture2D.MipLevels = 1;

  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
  hr = pSystem->GetDevice()->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResourceView.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateShaderResourceView");

  return Engine::GetTexture()->InsertTexture(_FilePath, pShaderResourceView.Get(), Size);
}

int IWIC::Add(const hdx::int2& _Size)
{
  return Engine::GetTexture()->CreateTexture(_Size);
}
