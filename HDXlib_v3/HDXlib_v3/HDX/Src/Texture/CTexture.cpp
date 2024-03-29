#include "CTexture.hpp"

#include "Src/Engine.hpp"
#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include <dxgi1_2.h>
#include <memory>
#include <string>
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
    int Stride()const { return Size_.x*kPixelBytes; }
    unsigned char* Buffer() { return &Buffer_[0]; }
    size_t BufferSize()const { return Buffer_.size(); }
  public:
    Image(const hdx::int2& _Size)
      : Size_(_Size), Buffer_(_Size.x*_Size.y*kPixelBytes)
    {

    }
  };
}

CTexture::CTexture()
{
  TIMER_START("Texture");

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(pFactory_.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  TIMER_END("Texture");
}

void CTexture::Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain)
{
  pDevice_ = _pDevice;
  pSwapChain_ = _pSwapChain;
  CreateDummyTexture(kDummyTextureSize);
}

int CTexture::CreateDummyTexture(const hdx::int2& _Size)
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  //  シェーダーリソースビュー設定で作成
  D3D11_TEXTURE2D_DESC Texture2dDesc{};
  {
    Texture2dDesc.Width = _Size.x;
    Texture2dDesc.Height = _Size.y;
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


  const UINT SysMemSize = _Size.x*_Size.y;
  std::unique_ptr<UINT[]> pSysmem = std::make_unique<UINT[]>(SysMemSize);

  //  白色設定で作成
  D3D11_SUBRESOURCE_DATA SubresourceData{};
  {
    for (UINT i = 0; i < SysMemSize; ++i)
    {
      pSysmem[i] = 0xFFFFFFFF;
    }
    SubresourceData.pSysMem = pSysmem.get();
    SubresourceData.SysMemPitch = sizeof(UINT)*_Size.x;
    SubresourceData.SysMemSlicePitch = 0;
  }

  //  Texture2Dを作成
  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2d;
  {
    hr = pDevice_->CreateTexture2D(&Texture2dDesc, &SubresourceData, pTexture2d.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  //  シェーダーリソースビューをスワップチェーン設定で作成
  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  {
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    pSwapChain_->GetDesc(&SwapChainDesc);
    ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
    ShaderResourceViewDesc.Texture2D.MipLevels = 1;
  }

  //  シェーダーリソースビューを作成
  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResouceView;
  {
    hr = pDevice_->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResouceView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  char FileName[kCharMaxNum];
  sprintf_s(FileName, "CreateTextureNumber%d", CreateTextureNum_++);

  //  マップへ追加
  return TextureMap_.insert(FileName, { pShaderResouceView, _Size });
}

int CTexture::Load(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = TextureMap_.find(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<IWICBitmapDecoder> Decoder;

  //  char型→wchar_t型に変換
  wchar_t wFilePath[kCharMaxNum];
  mbstowcs_s(nullptr, wFilePath, _FilePath, kCharMaxNum);

  hr = pFactory_->CreateDecoderFromFilename(wFilePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, Decoder.GetAddressOf());
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
    assert(Size.x > 0 && Size.y > 0);
  }

  WICPixelFormatGUID PixelFormat;
  hr = Frame->GetPixelFormat(&PixelFormat);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  Image Image(Size);

  if (PixelFormat != GUID_WICPixelFormat32bppRGBA)
  {
    Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;

    hr = pFactory_->CreateFormatConverter(pConverter.GetAddressOf());
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
  Texture2dDesc.Width = Image.Size_.x;
  Texture2dDesc.Height = Image.Size_.y;
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

  hr = pDevice_->CreateTexture2D(&Texture2dDesc, &InitializeData, pTexture2d.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  pSwapChain_->GetDesc(&SwapChainDesc);
  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  ShaderResourceViewDesc.Texture2D.MipLevels = 1;

  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
  hr = pDevice_->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResourceView.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return TextureMap_.insert(_FilePath, { pShaderResourceView, Size });
}

int CTexture::Add(const hdx::int2& _Size)
{
  return CreateDummyTexture(_Size);
}

const hdx::int2& CTexture::GetSize(int _ID)
{
  return TextureMap_[_ID].Size;
}

ID3D11ShaderResourceView* CTexture::GetShaderResourceView(int _ID)
{
  return TextureMap_[_ID].pShaderResourceView.Get();
}

void CTexture::SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView)
{
  const int ID = _RenderTarget.GetID();

  TextureMap_[ID].pShaderResourceView = _pShaderResouceView;
}
