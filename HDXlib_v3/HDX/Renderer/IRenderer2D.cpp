#include <HDX/Renderer/IRenderer2D.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Texture/ITexture.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/BlendState/BlendState.hpp>
#include <HDX/SamplerState/SamplerState.hpp>
#include <HDX/RasterizerState/RasterizerState.hpp>
#include <HDX/DepthStencilState/DepthStencilState.hpp>
#include <HDX/Texture/Texture.hpp>
#include <HDX/RenderTarget.hpp>

#include <HDX/Constants.hpp>

namespace detail
{
  struct IRenderer2D::Impl
  {
    hdx::VertexShader CurrentVertexShader_;
    hdx::PixelShader CurrentPixelShader_;
    hdx::BlendState CurrentBlendState_ = hdx::BlendState::Default;
    hdx::SamplerState CurrentSamplerStatus_[hdx::SamplerStateMaxNum];
    hdx::RasterizerState CurrentRasterizerState_ = hdx::RasterizerState::Default2D;
    hdx::DepthStencilState CurrentDepthStencilState_ = hdx::DepthStencilState::Default2D;
    hdx::Texture CurrentTextures_[hdx::TextureMaxNum - 1];
    hdx::RenderTarget CurrentRenderTarget_;
    bool isDefaultRenderTarget_ = true;
  public:
    Impl()
    {
      CurrentSamplerStatus_[0] = hdx::SamplerState::Default2D;
    }
  };

  IRenderer2D::IRenderer2D()
    : pImpl_(new Impl)
  {

  }

  IRenderer2D::~IRenderer2D()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  void IRenderer2D::SetVertexShader(const hdx::VertexShader& _VertexShader)
  {
    if (_VertexShader != hdx::VertexShader() && pImpl_->CurrentVertexShader_ != _VertexShader)
    {
      pImpl_->CurrentVertexShader_ = _VertexShader;
    }
  }

  void IRenderer2D::SetPixelShader(const hdx::PixelShader& _PixelShader)
  {
    if (_PixelShader != hdx::PixelShader() && pImpl_->CurrentPixelShader_ != _PixelShader)
    {
      pImpl_->CurrentPixelShader_ = _PixelShader;
    }
  }

  void IRenderer2D::SetBlendState(const hdx::BlendState& _BlendState)
  {
    if (pImpl_->CurrentBlendState_ != _BlendState)
    {
      pImpl_->CurrentBlendState_ = _BlendState;
    }
  }

  void IRenderer2D::SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)
  {


    hdx::SamplerState& CurrentSamplerState = pImpl_->CurrentSamplerStatus_[_Slot];
    if (CurrentSamplerState != _SamplerState)
    {
      CurrentSamplerState = _SamplerState;
    }
  }

  void IRenderer2D::SetRasterizerState(const hdx::RasterizerState& _RasterizerState)
  {
    if (pImpl_->CurrentRasterizerState_ != _RasterizerState)
    {
      pImpl_->CurrentRasterizerState_ = _RasterizerState;
    }
  }

  void IRenderer2D::SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
  {
    if (pImpl_->CurrentDepthStencilState_ != _DepthStencilState)
    {
      pImpl_->CurrentDepthStencilState_ = _DepthStencilState;
    }
  }

  void IRenderer2D::SetTexture(const hdx::Texture& _Texture, UINT _Slot)
  {
    hdx::Texture& CurrentTexture = pImpl_->CurrentTextures_[_Slot - 1];
    if (CurrentTexture != _Texture)
    {
      CurrentTexture = _Texture;
    }
  }

  inline void CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarger)
  {
    Engine::
  }

  void IRenderer2D::RestoreRenderTarget()
  {
    pImpl_->isDefaultRenderTarget_ = true;
    CreateTextureFromRenderTarget(pImpl_->CurrentRenderTarget_);
  }

  void IRenderer2D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
  {
    pImpl_->isDefaultRenderTarget_ = false;
    if (pImpl_->CurrentRenderTarget_ != _RenderTarger)
    {
      CreateTextureFromRenderTarget(pImpl_->CurrentRenderTarget_);
      pImpl_->CurrentRenderTarget_ = _RenderTarger;
    }
  }

  const hdx::VertexShader& IRenderer2D::GetVertexShader()const
  {
    return pImpl_->CurrentVertexShader_;
  }

  const hdx::PixelShader& IRenderer2D::GetPixelShader()const
  {
    return pImpl_->CurrentPixelShader_;
  }

  const hdx::BlendState& IRenderer2D::GetBlendState()const
  {
    return pImpl_->CurrentBlendState_;
  }

  const hdx::SamplerState& IRenderer2D::GetSamplerState(UINT _Slot)const
  {
    return pImpl_->CurrentSamplerStatus_[_Slot];
  }

  const hdx::RasterizerState& IRenderer2D::GetRasterizerState()const
  {
    return pImpl_->CurrentRasterizerState_;
  }

  const hdx::DepthStencilState& IRenderer2D::GetDepthStencilState()const
  {
    return pImpl_->CurrentDepthStencilState_;
  }

  const hdx::Texture& IRenderer2D::GetTexture(UINT _Slot)const
  {
    return pImpl_->CurrentTextures_[_Slot - 1];
  }

  //const hdx::RenderTarget& IRenderer2D::GetRenderTarget()const
  //{
  //  return pImpl_
  //}
}
