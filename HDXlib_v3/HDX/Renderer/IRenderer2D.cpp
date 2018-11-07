#include <HDX/Renderer/IRenderer2D.hpp>

#include <HDX/System/System.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/BlendState/BlendState.hpp>
#include <HDX/SamplerState/SamplerState.hpp>
#include <HDX/RasterizerState/RasterizerState.hpp>
#include <HDX/DepthStencilState/DepthStencilState.hpp>

namespace detail
{
  struct IRenderer2D::Impl
  {
    hdx::VertexShader CurrentVertexShader_;
    hdx::PixelShader CurrentPixelShader_;
    hdx::BlendState CurrentBlendState_ = hdx::BlendState::Default;
    hdx::SamplerState CurrentSamplerState_ = hdx::SamplerState::Default2D;
    hdx::RasterizerState CurrentRasterizerState_ = hdx::RasterizerState::Default2D;
    hdx::DepthStencilState CurrentDepthStencilState_ = hdx::DepthStencilState::Default2D;
  public:
    Impl()
    {

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

  void IRenderer2D::SetSamplerState(const hdx::SamplerState& _SamplerState)
  {
    if (pImpl_->CurrentSamplerState_ != _SamplerState)
    {
      pImpl_->CurrentSamplerState_ = _SamplerState;
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

  const hdx::SamplerState& IRenderer2D::GetSamplerState()const
  {
    return pImpl_->CurrentSamplerState_;
  }

  const hdx::RasterizerState& IRenderer2D::GetRasterizerState()const
  {
    return pImpl_->CurrentRasterizerState_;
  }

  const hdx::DepthStencilState& IRenderer2D::GetDepthStencilState()const
  {
    return pImpl_->CurrentDepthStencilState_;
  }
}
