#pragma once

namespace hdx
{
  enum class Blend;
  enum class BlendOp;
}

namespace detail
{
  class IBlendState
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    IBlendState();
    ~IBlendState();
  public:
    int Create(bool _AlphaToCoverageEnable, bool _BlendEnable, hdx::Blend& _SrcBlend, hdx::Blend& _DestBlend, hdx::BlendOp& _BlendOp, hdx::Blend& _SrcBlendAlpha, hdx::Blend& _DestBlnedAlpha, hdx::BlendOp& _BlendOpAlpha);
  };
}
