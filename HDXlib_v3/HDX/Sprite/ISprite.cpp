#include <HDX/Sprite/ISprite.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

#include <HDX/Vertex.hpp>
#include <HDX/NumberMap.hpp>
#include <HDX/Type2.hpp>
#include <HDX/Constants.hpp>

#include <d3d11.h>
#include <wrl.h>

namespace detail
{
  class ISprite::Impl
  {
    int CreateTextureNum_ = 0;
  private:
    struct TextureData
    {
      Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
      hdx::int2 Size_;
    };
  private:
    NumberMap<std::string, TextureData> TextureMap_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;
  private:
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

      Engine::GetSystem()->GetDevice()->CreateBuffer(&BufferDesc, &InitialData, pVertexBuffer_.GetAddressOf());

    }
  public:
    ID3D11Buffer* GetVertexBuffer()
    {
      if (!pVertexBuffer_)
      {
        CreateVertexBuffer();
      }

      return pVertexBuffer_.Get();
    }
    ID3D11Buffer** GetAddressOfVertexBuffer()
    {
      if (!pVertexBuffer_)
      {
        CreateVertexBuffer();
      }

      return pVertexBuffer_.GetAddressOf();
    }
  public:
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
        Texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
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

      char FileName[hdx::kMaxCharLimit];
      sprintf_s(FileName, "CreateTextureNumber%d", CreateTextureNum_++);

      //  マップへ追加
      return TextureMap_.insert(FileName, { pShaderResouceView, hdx::int2(1, 1) });
    }
  public:
    int GetDummyTextureID()
    {
      int ID = TextureMap_.find("");
      if (ID >= 0)
      {
        return ID;
      }

      return CreateDammyTexture(1);
    }
    int GetTextureID(const char* _FilePath) { return TextureMap_.find(_FilePath); }
    const hdx::int2& GetSize(int _ID) { return TextureMap_[_ID].Size_; }
    int InsertTexture(const char* _FilePath, ID3D11ShaderResourceView* _pShaderResourceView, const hdx::int2& _Size)
    {
      return TextureMap_.insert(_FilePath, { _pShaderResourceView, _Size });
    }
    ID3D11ShaderResourceView** GetShaderResourceView(int _ID) { return TextureMap_[_ID].pShaderResourceView.GetAddressOf(); }
  public:
    Impl() { TextureMap_.clear(); }
    ~Impl() { TextureMap_.clear(); }
  };

  ISprite::ISprite()
    : pImpl_(new Impl)
  {

  }

  ISprite::~ISprite()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  int ISprite::GetDummyTextureID()
  {
    return pImpl_->GetDummyTextureID();
  }

  int ISprite::GetTextureID(const char* _FilePath)
  {
    return pImpl_->GetTextureID(_FilePath);
  }

  const hdx::int2& ISprite::GetSize(int _ID)
  {
    return pImpl_->GetSize(_ID);
  }

  int ISprite::InsertTexture(const char* _FilePath, ID3D11ShaderResourceView* _pShaderResourceView, const hdx::int2& _Size)
  {
    return pImpl_->InsertTexture(_FilePath, _pShaderResourceView, _Size);
  }

  int ISprite::CreateTexture(const hdx::int2& _Size)
  {
    return pImpl_->CreateDammyTexture(_Size);
  }

  ID3D11ShaderResourceView** ISprite::GetShaderResourceView(int _ID)
  {
    return pImpl_->GetShaderResourceView(_ID);
  }

  ID3D11Buffer* ISprite::GetVertexBuffer()
  {
    return pImpl_->GetVertexBuffer();
  }

  ID3D11Buffer** ISprite::GetAddressOfVertexBuffer()
  {
    return pImpl_->GetAddressOfVertexBuffer();
  }
}
