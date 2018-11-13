#include "../../Include/Texture.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../Texture/ITexture.hpp"
#include "../Renderer/Renderer2D/IRenderer2D.hpp"
#include "../BlendState/IBlendState.hpp"
#include "../SamplerState/ISamplerState.hpp"
#include "../RasterizerState/IRasterizerState.hpp"
#include "../DepthStencilState/IDepthStencilState.hpp"
#include "../VertexShader/IVertexShader.hpp"
#include "../PixelShader/IPixelShader.hpp"
#include "../RenderTarget/IRenderTarget.hpp"

#include "../../Include/System.hpp"
#include "../../Include/Math.hpp"
#include "../../Include/Vertex.hpp"
#include "../../Include/Constants.hpp"

#include <time.h>
#include <WICTextureLoader.h>

//****************************************************************************************************
//	Hdx2DObj
//****************************************************************************************************

namespace hdx
{
  Texture::Texture(const int2& _Size)
    : ID_(Engine::GetTexture()->Add(_Size)), Size_(_Size)
  {

  }

  //  �t�@�C���p�X����摜���쐬
  Texture::Texture(const char* FilePath)
    : ID_(Engine::GetTexture()->Load(FilePath)), Size_(Engine::GetTexture()->GetSize(ID_))
  {

  }

  ////  �R���X�g���N�^(��ʂ��琶��)
  //Texture::Texture()
  //{
  //  //  �G���[�`�F�b�N�p
  //  HRESULT hr = S_OK;
  //
  //  //  �o�b�N�o�b�t�@���擾
  //  Microsoft::WRL::ComPtr<ID3D11Texture2D> Screen;
  //  hr = detail::System::Get()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(Screen.GetAddressOf()));
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer");
  //
  //  //  Texture2D���쐬
  //  D3D11_TEXTURE2D_DESC Texture2dDesc;
  //  Screen->GetDesc(&Texture2dDesc);
  //
  //  //  �������݉\��Texture2D���쐬
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
  //  //  �������݉\��Texture2D�ɉ�ʃf�[�^���R�s�[
  //  detail::System::Get()->GetDeviceContext()->CopyResource(pCopyTexture2d.Get(), Screen.Get());
  //
  //  //  Texture2D�̏�������
  //  D3D11_MAPPED_SUBRESOURCE MappedSubresource;
  //  hr = detail::System::Get()->GetDeviceContext()->Map(pCopyTexture2d.Get(), 0, D3D11_MAP_WRITE, 0, &MappedSubresource);
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"Map");
  //
  //  u_char *p = reinterpret_cast<u_char*>(MappedSubresource.pData);
  //  for (size_t y = 0; y < Texture2dDesc.Height; ++y)
  //  {
  //    for (size_t x = 0; x < Texture2dDesc.Width; ++x)
  //    {
  //      p[y*MappedSubresource.RowPitch + x * 4 + 3] = 255;  //  �A���t�@�l���ő��
  //    }
  //  }
  //
  //  //  Texture2D�̏��������I��
  //  detail::System::Get()->GetDeviceContext()->Unmap(pCopyTexture2d.Get(), 0);
  //
  //  //  ShaderResouceView���쐬�\��Texture2D���쐬
  //  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2d;
  //  Texture2dDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
  //  detail::System::Get()->GetDevice()->CreateTexture2D(&Texture2dDesc, nullptr, pTexture2d.GetAddressOf());
  //
  //  //  ShaderResouceView���쐬�\��Texture2D�ɏ���������Texture2D���R�s�[
  //  detail::System::Get()->GetDeviceContext()->CopyResource(pTexture2d.Get(), pCopyTexture2d.Get());
  //
  //  //  ShaderResouceView���쐬
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
  //  //  ���O���w�肵�AShaderResouceView��ۑ�
  //  time_t now = time(nullptr);
  //  char c[256];
  //  sprintf_s(c, "%d", static_cast<int>(now));
  //
  //  ID_ = detail::System::Get()->GetTextureManager()->InsertShaderResourceViewMap(c, pShaderResourceView);
  //
  //  //  �T�C�Y��ۑ�
  //  Size_.X = Texture2dDesc.Width;
  //  Size_.Y = Texture2dDesc.Height;
  //}

  //  �`��ŏI����
  void Texture::Draw2D(const Vertex2D* v)const
  {
    ISystem* pSystem = Engine::GetSystem();
    ITexture* pTexture = Engine::GetTexture();

    //  ���_�o�b�t�@�I�u�W�F�N�g����������
    D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
    pSystem->Map(pTexture->GetVertexBuffer(), &MappedSubresorce);

    Vertex2D* Vertices = reinterpret_cast<Vertex2D*>(MappedSubresorce.pData);

    //  ���_�����R�s�[
    memcpy(Vertices, v, sizeof(Vertex2D) * 4);

    //  ���_�o�b�t�@�I�u�W�F�N�g�����������I��
    pSystem->Unmap(pTexture->GetVertexBuffer());

    //  �V�F�[�_�[���\�[�X�r���[��ݒ�
    pSystem->SetShaderResouceView(pTexture->GetShaderResourceView(ID_), 0);

    const IRenderer2D* pRenderer2D = Engine::GetRenderer2D();

    UINT Strides = sizeof(Vertex2D);
    pSystem->SetVertexBuffers(pTexture->GetAddressOfVertexBuffer(), Strides);

    pSystem->SetBlendState(Engine::GetBlendState()->GetBlendState(pRenderer2D->GetBlendState()));
    pSystem->SetInputLayout(Engine::GetVertexShader()->GetInputLayout(pRenderer2D->GetVertexShader()));
    pSystem->SetVertexShader(Engine::GetVertexShader()->GetVertexShader(pRenderer2D->GetVertexShader()));
    pSystem->SetPixelShader(Engine::GetPixelShader()->GetPixeShader(pRenderer2D->GetPixelShader()));
    pSystem->SetRasterizerState(Engine::GetRasterizerState()->GetRasterizerState(pRenderer2D->GetRasterizerState()));
    pSystem->SetDepthStencilState(Engine::GetDepthStencilState()->GetDepthStencilState(pRenderer2D->GetDepthStencilState()));
    pSystem->SetSamplersState(Engine::GetSamplerState()->GetSamplerState(pRenderer2D->GetSamplerState(0)), 0);

    //for (UINT i = 0; i < SamplerStateMaxNum; ++i)
    //{
    //  pSystem->SetSamplersState(Engine::GetSamplerState()->GetSamplerState(pRenderer2D->GetSamplerState(i)), i);
    //}
    //for (UINT i = 1; i < TextureMaxNum; ++i)
    //{
    //  const hdx::Texture& Texture = pRenderer2D->GetTexture(i);
    //  //  �T�C�Y��0�̎��X���[
    //  if (Texture.GetSize() == hdx::int2()) continue;
    //
    //  pSystem->SetShaderResouceView(pTexture->GetShaderResourceView(Texture.GetID()), i);
    //}

    pSystem->SetRenderTarget(Engine::GetRenderTarget()->GetRenderTargetView(pRenderer2D->GetRenderTarget()), Engine::GetRenderTarget()->GetDepthStencilView(pRenderer2D->GetRenderTarget()));

    //  �`��
    pSystem->GetImmediateContext()->Draw(4, 0);
  }

  //  �`��
  //  _isFitScreen:true:��ʃT�C�Y�ɍ����,false:���̂܂܂̃T�C�Y
  //  _Color:�F���w��(Color�N���X�����̂܂܎g���܂�)
  void Texture::Draw(bool _isFitScreen, const ColorF& _Color)const
  {
    Vertex2D Vertices[4];

    //  ��ʍ��W�ݒ�
    {
      Vertices[0].Position.X = Vertices[2].Position.X = -1.0f;
      Vertices[1].Position.X = Vertices[3].Position.X = (_isFitScreen) ? 1.0f : 2.0f * (static_cast<float>(Size_.X) / System::GetWindowWidth()) - 1.0f;
      Vertices[0].Position.Y = Vertices[1].Position.Y = 1.0f;
      Vertices[2].Position.Y = Vertices[3].Position.Y = (_isFitScreen) ? -1.0f : -2.0f *(static_cast<float>(Size_.Y) / System::GetWindowHeight()) + 1.0f;
    }

    //  �摜���W�ݒ�
    {
      Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = 0.0f;
      Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = 1.0f;
      Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = 0.0f;
      Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = 1.0f;
    }

    //  �őO�ʐݒ�
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  �F�ݒ�
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  �`�揈��
    Draw2D(Vertices);
  }

  //  �`��
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color)const
  {
    Vertex2D Vertices[4];

    //  ��ʍ��W�ݒ�
    {
      Vertices[0].Position.X = Vertices[2].Position.X = 2.0f * (_DstLeftTop.X / System::GetWindowWidth()) - 1.0f;
      Vertices[1].Position.X = Vertices[3].Position.X = 2.0f * ((_DstLeftTop.X + _DstSize.X) / System::GetWindowWidth()) - 1.0f;
      Vertices[0].Position.Y = Vertices[1].Position.Y = -2.0f * (_DstLeftTop.Y / System::GetWindowHeight()) + 1.0f;
      Vertices[2].Position.Y = Vertices[3].Position.Y = -2.0f * ((_DstLeftTop.Y + _DstSize.Y) / System::GetWindowHeight()) + 1.0f;
    }

    //  �摜���W�ݒ�
    {
      Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = _SrcLeftPos.X / Size_.X;
      Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = (_SrcLeftPos.X + _SrcSize.X) / Size_.X;
      Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = _SrcLeftPos.Y / Size_.Y;
      Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y;
    }

    //  �őO�ʐݒ�
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  �F�ݒ�
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  �`�揈��
    Draw2D(Vertices);
  }

  //  �`��
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color)const
  {
    Vertex2D Vertices[4];

    //  ��ʍ��W�ݒ�
    {
      //  ���S���W
      const float2 CenterPos{ _DstLeftTop + (_DstSize / 2.0f) };
      //  ��]���W
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

    //  �摜���W�ݒ�
    {
      Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = _SrcLeftPos.X / Size_.X;
      Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = (_SrcLeftPos.X + _SrcSize.X) / Size_.X;
      Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = _SrcLeftPos.Y / Size_.Y;
      Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y;
    }

    //  �őO�ʐݒ�
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  �F�ݒ�
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  �`�揈��
    Draw2D(Vertices);
  }

  //  �`��
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color)const
  {
    Vertex2D Vertices[4];

    //  ��ʍ��W�ݒ�
    {
      //  ���S���W
      const float2 CenterPos{ _DstLeftTop + (_DstSize / 2.0f) };
      //  ��]���W
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

    //  �摜���W�ݒ�
    Vertices[0].Texcoord.X = Vertices[2].Texcoord.X = (!_HorizontalFlip) ? _SrcLeftPos.X / Size_.X : (_SrcLeftPos.X + _SrcSize.X) / Size_.X;
    Vertices[1].Texcoord.X = Vertices[3].Texcoord.X = (!_HorizontalFlip) ? (_SrcLeftPos.X + _SrcSize.X) / Size_.X : _SrcLeftPos.X / Size_.X;
    Vertices[0].Texcoord.Y = Vertices[1].Texcoord.Y = (!_VerticalFlip) ? _SrcLeftPos.Y / Size_.Y : (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y;
    Vertices[2].Texcoord.Y = Vertices[3].Texcoord.Y = (!_VerticalFlip) ? (_SrcLeftPos.Y + _SrcSize.Y) / Size_.Y : _SrcLeftPos.Y / Size_.Y;

    //  �őO�ʐݒ�
    Vertices[0].Position.Z = Vertices[1].Position.Z = Vertices[2].Position.Z = Vertices[3].Position.Z = 0.0f;

    //  �F�ݒ�
    Vertices[0].Color = Vertices[1].Color = Vertices[2].Color = Vertices[3].Color = _Color;

    //  �`�揈��
    Draw2D(Vertices);
  }
}
