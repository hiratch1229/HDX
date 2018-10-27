#include <HDX/Graphics/IGraphics2D.hpp>

#include <HDX/System.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>

namespace detail
{
  struct IGraphics2D::Impl
  {
  //  hdx::VertexShader CurrentVertexShader_;
  //  hdx::PixelShader CurrentPixelShader_;
  //public:
  //  Impl()
  //  {
  //
  //  }
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
}
