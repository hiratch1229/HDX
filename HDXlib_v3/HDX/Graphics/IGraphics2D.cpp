#include <HDX/Graphics/IGraphics2D.hpp>

#include <HDX/System/System.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/BlendState/BlendState.hpp>

namespace detail
{
  struct IGraphics2D::Impl
  {
    hdx::VertexShader CurrentVertexShader_;
    hdx::PixelShader CurrentPixelShader_;
    hdx::BlendState CurrentBlendState_;
  public:
    Impl()
    {

    }
  };

  IGraphics2D::IGraphics2D()
    : pImpl_(new Impl)
  {

  }

  IGraphics2D::~IGraphics2D()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  void IGraphics2D::SetVertexShader(const hdx::VertexShader& _VertexShader)
  {
    if (_VertexShader != hdx::VertexShader() && pImpl_->CurrentVertexShader_ != _VertexShader)
    {
      pImpl_->CurrentVertexShader_ = _VertexShader;
    }
  }

  void IGraphics2D::SetPixelShader(const hdx::PixelShader& _PixelShader)
  {
    if (_PixelShader != hdx::PixelShader() && pImpl_->CurrentPixelShader_ != _PixelShader)
    {
      pImpl_->CurrentPixelShader_ = _PixelShader;
    }
  }

  void IGraphics2D::SetBlendState(const hdx::BlendState& _BlendState)
  {
    if (pImpl_->CurrentBlendState_ != _BlendState)
    {
      pImpl_->CurrentBlendState_ = _BlendState;
    }
  }

  const hdx::VertexShader& IGraphics2D::GetVertexShader()const
  {
    return pImpl_->CurrentVertexShader_;
  }

  const hdx::PixelShader& IGraphics2D::GetPixelShader()const
  {
    return pImpl_->CurrentPixelShader_;
  }

  const hdx::BlendState& IGraphics2D::GetBlendState()const
  {
    return pImpl_->CurrentBlendState_;
  }
}
