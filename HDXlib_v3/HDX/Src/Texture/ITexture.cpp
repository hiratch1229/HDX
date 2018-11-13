#include "ITexture.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../NumberMap.hpp"

#include "../../Include/Vertex.hpp"
#include "../../Include/RenderTarget.hpp"
#include "../../Include/Type2.hpp"
#include "../../Include/Constants.hpp"

#include <d3d11.h>
#include <wincodec.h>
#include <wrl.h>

namespace
{
  Microsoft::WRL::ComPtr<IWICImagingFactory> pFactory;

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

  NumberMap<std::string, TextureData> TextureMap;
  Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

  int CreateDammyTexture(const hdx::int2& _Size)
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    ISystem* pSystem = Engine::GetSystem();

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
      hr = pSystem->GetDevice()->CreateTexture2D(&Texture2dDesc, &SubresourceData, pTexture2d.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");
    }

    //  シェーダーリソースビューをスワップチェーン設定で作成
    D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
    {
      DXGI_SWAP_CHAIN_DESC SwapChainDesc;
      pSystem->GetSwapChain()->GetDesc(&SwapChainDesc);
      ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
      ShaderResourceViewDesc.Texture2D.MipLevels = 1;
    }

    //  シェーダーリソースビューを作成
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResouceView;
    {
      hr = pSystem->GetDevice()->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResouceView.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), L"CreateShaderResourceView");
    }

    char FileName[hdx::MaxCharLimit];
    sprintf_s(FileName, "CreateTextureNumber%d", CreateTextureNum++);

    //  マップへ追加
    return TextureMap.insert(FileName, { pShaderResouceView, _Size });
  }

  void CreateVertexBuffer()
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    Vertex2D Vertices[4]{};

    D3D11_BUFFER_DESC BufferDesc{};
    {
      BufferDesc.ByteWidth = sizeof(Vertices);
      BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
      BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      BufferDesc.MiscFlags = 0;
      BufferDesc.StructureByteStride = 0;
    }

    D3D11_SUBRESOURCE_DATA InitialData{};
    {
      InitialData.pSysMem = Vertices;
      InitialData.SysMemPitch = 0;
      InitialData.SysMemSlicePitch = 0;
    }

    Engine::GetSystem()->GetDevice()->CreateBuffer(&BufferDesc, &InitialData, pVertexBuffer.GetAddressOf());
  }
}

ITexture::ITexture()
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(pFactory.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), L"CoCreateInstance");
}

int ITexture::Load(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = GetTextureID(_FilePath);
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
    _ASSERT_EXPR(Size.X > 0 && Size.Y > 0, L"Size");
  }

  WICPixelFormatGUID PixelFormat;
  hr = Frame->GetPixelFormat(&PixelFormat);
  _ASSERT_EXPR(SUCCEEDED(hr), L"GetPixelFormat");

  Image Image(Size);

  if (PixelFormat != GUID_WICPixelFormat32bppRGBA)
  {
    Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;

    hr = pFactory->CreateFormatConverter(pConverter.GetAddressOf());
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

  return InsertTexture(_FilePath, pShaderResourceView.Get(), Size);
}

int ITexture::Add(const hdx::int2& _Size)
{
  return CreateDammyTexture(_Size);
}

int ITexture::GetDummyTextureID()
{
  int ID = TextureMap.find("");
  if (ID >= 0)
  {
    return ID;
  }

  return CreateDammyTexture(1);
}

int ITexture::GetTextureID(const char* _FilePath)
{
  return TextureMap.find(_FilePath);
}

const hdx::int2& ITexture::GetSize(int _ID)
{
  return TextureMap[_ID].Size;
}

int ITexture::InsertTexture(const char* _FilePath, ID3D11ShaderResourceView* _pShaderResourceView, const hdx::int2& _Size)
{
  return TextureMap.insert(_FilePath, { _pShaderResourceView, _Size });
}

ID3D11ShaderResourceView** ITexture::GetShaderResourceView(int _ID)
{
  return TextureMap[_ID].pShaderResourceView.GetAddressOf();
}

inline void CheckCreateVertexBuffer()
{
  if (pVertexBuffer) return;

  CreateVertexBuffer();
}

ID3D11Buffer* ITexture::GetVertexBuffer()
{
  CheckCreateVertexBuffer();

  return pVertexBuffer.Get();
}

ID3D11Buffer** ITexture::GetAddressOfVertexBuffer()
{
  CheckCreateVertexBuffer();

  return pVertexBuffer.GetAddressOf();
}

void ITexture::SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView)
{
  //pImpl_->TextureMap_[_RenderTarget.GetID()].pShaderResourceView.Reset();
  //pImpl_->TextureMap_[_RenderTarget.GetID()].pShaderResourceView = _pShaderResouceView;
}
