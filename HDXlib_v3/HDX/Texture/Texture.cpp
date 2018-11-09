#include <HDX/Texture/Texture.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>
#include <HDX/Renderer/IRenderer2D.hpp>
#include <HDX/BlendState/IBlendState.hpp>
#include <HDX/SamplerState/ISamplerState.hpp>
#include <HDX/RasterizerState/IRasterizerState.hpp>
#include <HDX/DepthStencilState/IDepthStencilState.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>

#include <HDX/IWIC.hpp>
#include <HDX/Texture/ITexture.hpp>

#include <HDX/System/System.hpp>
#include <HDX/Math.hpp>
#include <HDX/Vertex.hpp>
#include <HDX/Constants.hpp>

//#include <HDX/System/System.hpp>
//#include <HDX/Math.hpp>
//#include <HDX/Error.hpp>
//#include <HDX/VertexShader/VertexShader.hpp>
//#include <HDX/PixelShader/PixelShader.hpp>
//#include <HDX/VertexShader/IVertexShader.hpp>
//#include <HDX/PixelShader/IPixelShader.hpp>
//#include <HDX/WIC.hpp>

#include <time.h>
#include <WICTextureLoader.h>

//****************************************************************************************************
//	Hdx2DObj
//****************************************************************************************************

namespace hdx
{
  Texture::Texture(const int2& _Size)
    : ID_(GetWIC()->Add(_Size)), Size_(_Size)
  {

  }

  //  ファイルパスから画像を作成
  Texture::Texture(const char* FilePath)
    : ID_(GetWIC()->Load(FilePath)), Size_(GetTexture()->GetSize(ID_))
  {

  }

  ////  コンストラクタ(画面から生成)
  //Texture::Texture()
  //{
  //  //  エラーチェック用
  //  HRESULT hr = S_OK;
  //
  //  //  バックバッファを取得
  //  Microsoft::WRL::ComPtr<ID3D11Texture2D> Screen;
  //  hr = detail::System::Get()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(Screen.GetAddressOf()));
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer");
  //
  //  //  Texture2Dを作成
  //  D3D11_TEXTURE2D_DESC Texture2dDesc;
  //  Screen->GetDesc(&Texture2dDesc);
  //
  //  //  書き込み可能なTexture2Dを作成
  //  Microsoft::WRL::ComPtr<ID3D11Texture2D> pCopyTexture2d;
  //  D3D11_TEXTURE2D_DESC CopyTexture2dDesc;
  //  CopyTexture2dDesc.ArraySize = 1;
  //  CopyTexture2dDesc.BindFlags = 0;
  //  CopyTexture2dDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  //  CopyTexture2dDesc.Format = Texture2dDesc.Format;
  //  CopyTexture2dDesc.Height = Texture2dDesc.Height;
  //  CopyTexture2dDesc.Width = Texture2dDesc.Width;
  //  CopyTexture2dDesc.MipLevels = 1;
  //  CopyTexture2dDesc.MiscFlags = 0;
  //  CopyTexture2dDesc.SampleDesc.Count = 1;
  //  CopyTexture2dDesc.SampleDesc.Quality = 0;
  //  CopyTexture2dDesc.Usage = D3D11_USAGE_STAGING;
  //  hr = detail::System::Get()->GetDevice()->CreateTexture2D(&CopyTexture2dDesc, 0, pCopyTexture2d.GetAddressOf());
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");
  //
  //  //  書き込み可能なTexture2Dに画面データをコピー
  //  detail::System::Get()->GetDeviceContext()->CopyResource(pCopyTexture2d.Get(), Screen.Get());
  //
  //  //  Texture2Dの書き換え
  //  D3D11_MAPPED_SUBRESOURCE MappedSubresource;
  //  hr = detail::System::Get()->GetDeviceContext()->Map(pCopyTexture2d.Get(), 0, D3D11_MAP_WRITE, 0, &MappedSubresource);
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"Map");
  //
  //  u_char *p = reinterpret_cast<u_char*>(MappedSubresource.pData);
  //  for (size_t y = 0; y < Texture2dDesc.Height; ++y)
  //  {
  //    for (size_t x = 0; x < Texture2dDesc.Width; ++x)
  //    {
  //      p[y*MappedSubresource.RowPitch + x * 4 + 3] = 255;  //  アルファ値を最大に
  //    }
  //  }
  //
  //  //  Texture2Dの書き換え終了
  //  detail::System::Get()->GetDeviceContext()->Unmap(pCopyTexture2d.Get(), 0);
  //
  //  //  ShaderResouceViewを作成可能なTexture2Dを作成
  //  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2d;
  //  Texture2dDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
  //  detail::System::Get()->GetDevice()->CreateTexture2D(&Texture2dDesc, nullptr, pTexture2d.GetAddressOf());
  //
  //  //  ShaderResouceViewを作成可能なTexture2Dに書き換えたTexture2Dをコピー
  //  detail::System::Get()->GetDeviceContext()->CopyResource(pTexture2d.Get(), pCopyTexture2d.Get());
  //
  //  //  ShaderResouceViewを作成
  //  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  //  ShaderResourceViewDesc.Format = Texture2dDesc.Format;
  //  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  //  detail::System::Get()->GetSwapChain()->GetDesc(&SwapChainDesc);
  //  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  //  ShaderResourceViewDesc.Texture2D.MipLevels = Texture2dDesc.MipLevels;
  //
  //  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
  //  hr = detail::System::Get()->GetDevice()->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, pShaderResourceView.GetAddressOf());
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateShaderResourceView");
  //
  //  //  名前を指定し、ShaderResouceViewを保存
  //  time_t now = time(nullptr);
  //  char c[256];
  //  sprintf_s(c, "%d", static_cast<int>(now));
  //
  //  ID_ = detail::System::Get()->GetTextureManager()->InsertShaderResourceViewMap(c, pShaderResourceView);
  //
  //  //  サイズを保存
  //  Size_.X = Texture2dDesc.Width;
  //  Size_.Y = Texture2dDesc.Height;
  //}

  //  描画最終処理
  void Texture::Draw2D(const detail::Vertex2D* v)const
  {
    detail::ISystem* pSystem = GetSystem();

    //  頂点バッファオブジェクトを書き換え
    D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
    pSystem->Map(GetTexture()->GetVertexBuffer(), &MappedSubresorce);

    detail::Vertex2D* Vertices = reinterpret_cast<detail::Vertex2D*>(MappedSubresorce.pData);

    //  頂点情報をコピー
    memcpy(Vertices, v, sizeof(detail::Vertex2D) * 4);

    //  頂点バッファオブジェクトを書き換え終了
    pSystem->Unmap(GetTexture()->GetVertexBuffer());

    //  シェーダーリソースビューを設定
    pSystem->SetShaderResouceView(GetTexture()->GetShaderResourceView(ID_), 0);

    const detail::IRenderer2D* pGraphics2D = GetRenderer2D();

    UINT Strides = sizeof(detail::Vertex2D);
    pSystem->SetVertexBuffers(GetTexture()->GetAddressOfVertexBuffer(), Strides);

    pSystem->SetBlendState(GetBlendState()->GetBlendState(pGraphics2D->GetBlendState()));
    pSystem->SetInputLayout(GetVertexShader()->GetInputLayout(pGraphics2D->GetVertexShader()));
    pSystem->SetVertexShader(GetVertexShader()->GetVertexShader(pGraphics2D->GetVertexShader()));
    pSystem->SetPixelShader(GetPixelShader()->GetPixeShader(pGraphics2D->GetPixelShader()));
    pSystem->SetRasterizerState(GetRasterizerState()->GetRasterizerState(pGraphics2D->GetRasterizerState()));
    pSystem->SetDepthStencilState(GetDepthStencilState()->GetDepthStencilState(pGraphics2D->GetDepthStencilState()));
    for (UINT i = 0; i < SamplerStateMaxNum; ++i)
    {
      pSystem->SetSamplersState(GetSamplerState()->GetSamplerState(pGraphics2D->GetSamplerState(i)), i);
    }
    for (UINT i = 1; i < TextureMaxNum; ++i)
    {
      const hdx::Texture& Texture = pGraphics2D->GetTexture(i);
      //  サイズが0の時スルー
      if (Texture.GetSize() == hdx::int2()) continue;

      pSystem->SetShaderResouceView(GetTexture()->GetShaderResourceView(Texture.GetID()), i);
    }

    //  描画
    pSystem->GetImmediateContext()->Draw(4, 0);
  }

  //  描画
  //  _isFitScreen:true:画面サイズに合わる,false:そのままのサイズ
  //  _Color:色を指定(Colorクラスもそのまま使えます)
  void Texture::Draw(bool _isFitScreen, const ColorF& _Color)const
  {
    detail::Vertex2D Vertices[4];

    //  画面座標設定
    {
      Vertices[0].Position.X = Vertices[2].Position.X = -1.0f;
      Vertices[1].Position.X = Vertices[3].Position.X = (_isFitScreen) ? 1.0f : 2.0f * (static_cast<float>(Size_.X) / System::GetWindowWidth()) - 1.0f;
      Vertices[0].Position.Y = Vertices[1].Position.Y = 1.0f;
      Vertices[2].Position.Y = Vertices[3].Position.Y = (_isFitScreen) ? -1.0f : -2.0f *(static_cast<float>(Size_.Y) / System::GetWindowHeight()) + 1.0f;
    }

    //  画像座標設定
    {
      Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = 0.0f;
      Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = 1.0f;
      Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = 0.0f;
      Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = 1.0f;
    }

    //  最前面設定
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  色設定
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  描画処理
    Draw2D(Vertices);
  }

  //  描画
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color)const
  {
    detail::Vertex2D Vertices[4];

    //  画面座標設定
    {
      Vertices[0].Position.X = Vertices[2].Position.X = 2.0f * (_DstLeftTop.X / System::GetWindowWidth()) - 1.0f;
      Vertices[1].Position.X = Vertices[3].Position.X = 2.0f * ((_DstLeftTop.X + _DstSize.X) / System::GetWindowWidth()) - 1.0f;
      Vertices[0].Position.Y = Vertices[1].Position.Y = -2.0f * (_DstLeftTop.Y / System::GetWindowHeight()) + 1.0f;
      Vertices[2].Position.Y = Vertices[3].Position.Y = -2.0f * ((_DstLeftTop.Y + _DstSize.Y) / System::GetWindowHeight()) + 1.0f;
    }

    //  画像座標設定
    {
      Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = _SrcLeftPos.X / Size_.X;
      Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = (_SrcLeftPos.X + _SrcSize.X) / Size_.X;
      Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = _SrcLeftPos.Y / Size_.Y;
      Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y;
    }

    //  最前面設定
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  色設定
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  描画処理
    Draw2D(Vertices);
  }

  //  描画
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color)const
  {
    detail::Vertex2D Vertices[4];

    //  画面座標設定
    {
      //  中心座標
      const float2 CenterPos{ _DstLeftTop + (_DstSize / 2.0f) };
      //  回転座標
      const float2 RotatePos[4] = {
        Math::RotateXY(_DstLeftTop, CenterPos, _Angle),
        Math::RotateXY(_DstLeftTop.X + _DstSize.X, _DstLeftTop.Y, CenterPos, _Angle),
        Math::RotateXY(_DstLeftTop.X, _DstLeftTop.Y + _DstSize.Y, CenterPos, _Angle),
        Math::RotateXY(_DstLeftTop + _DstSize, CenterPos, _Angle)
      };

      for (int i = 0; i < 4; ++i)
      {
        Vertices[i].Position.X = 2.0f * (RotatePos[i].X / System::GetWindowWidth()) - 1.0f;
        Vertices[i].Position.Y = -2.0f * (RotatePos[i].Y / System::GetWindowHeight()) + 1.0f;
      }
    }

    //  画像座標設定
    {
      Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = _SrcLeftPos.X / Size_.X;
      Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = (_SrcLeftPos.X + _SrcSize.X) / Size_.X;
      Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = _SrcLeftPos.Y / Size_.Y;
      Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y;
    }

    //  最前面設定
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  色設定
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  描画処理
    Draw2D(Vertices);
  }

  //  描画
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color)const
  {
    detail::Vertex2D Vertices[4];

    //  画面座標設定
    {
      //  中心座標
      const float2 CenterPos{ _DstLeftTop + (_DstSize / 2.0f) };
      //  回転座標
      const float2 RotatePos[4] = {
        Math::RotateXY(_DstLeftTop, CenterPos, _Angle),
        Math::RotateXY(_DstLeftTop.X + _DstSize.X, _DstLeftTop.Y, CenterPos, _Angle),
        Math::RotateXY(_DstLeftTop.X, _DstLeftTop.Y + _DstSize.Y, CenterPos, _Angle),
        Math::RotateXY(_DstLeftTop + _DstSize, CenterPos, _Angle)
      };

      for (int i = 0; i < 4; ++i)
      {
        Vertices[i].Position.X = 2.0f * (RotatePos[i].X / System::GetWindowWidth()) - 1.0f;
        Vertices[i].Position.Y = -2.0f * (RotatePos[i].Y / System::GetWindowHeight()) + 1.0f;
      }
    }

    //  画像座標設定
    Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = (!_HorizontalFlip) ? _SrcLeftPos.X / Size_.X : (_SrcLeftPos.X + _SrcSize.X) / Size_.X;
    Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = (!_HorizontalFlip) ? (_SrcLeftPos.X + _SrcSize.X) / Size_.X : _SrcLeftPos.X / Size_.X;
    Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = (!_VerticalFlip) ? _SrcLeftPos.Y / Size_.Y : (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y;
    Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = (!_VerticalFlip) ? (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y : _SrcLeftPos.Y / Size_.Y;

    //  最前面設定
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  色設定
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  描画処理
    Draw2D(Vertices);
  }
}
