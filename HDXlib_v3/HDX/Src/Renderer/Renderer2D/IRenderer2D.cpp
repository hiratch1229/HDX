#include "IRenderer2D.hpp"

#include "../../Engine.hpp"
#include "../../Texture/ITexture.hpp"
#include "../../RenderTarget/IRenderTarget.hpp"

#include "../../../Include/VertexShader.hpp"
#include "../../../Include/PixelShader.hpp"
#include "../../../Include/BlendState.hpp"
#include "../../../Include/SamplerState.hpp"
#include "../../../Include/RasterizerState.hpp"
#include "../../../Include/DepthStencilState.hpp"
#include "../../../Include/Texture.hpp"
#include "../../../Include/RenderTarget.hpp"

#include "../../../Include/Constants.hpp"

namespace
{
  hdx::VertexShader CurrentVertexShader;
  hdx::PixelShader CurrentPixelShader;
  hdx::BlendState CurrentBlendState = hdx::BlendState::Default;
  hdx::SamplerState CurrentSamplerStatus[hdx::SamplerStateMaxNum];
  hdx::RasterizerState CurrentRasterizerState = hdx::RasterizerState::Default2D;
  hdx::DepthStencilState CurrentDepthStencilState = hdx::DepthStencilState::Default2D;
  hdx::Texture CurrentTextures[hdx::TextureMaxNum - 1];
  hdx::RenderTarget CurrentRenderTarget;
}

IRenderer2D::IRenderer2D()
{
  CurrentSamplerStatus[0] = hdx::SamplerState::Default2D;
}

void IRenderer2D::SetVertexShader(const hdx::VertexShader& _VertexShader)
{
  if (CurrentVertexShader != _VertexShader)
  {
    CurrentVertexShader = _VertexShader;
  }
}

void IRenderer2D::SetPixelShader(const hdx::PixelShader& _PixelShader)
{
  if (CurrentPixelShader != _PixelShader)
  {
    CurrentPixelShader = _PixelShader;
  }
}

void IRenderer2D::SetBlendState(const hdx::BlendState& _BlendState)
{
  if (CurrentBlendState != _BlendState)
  {
    CurrentBlendState = _BlendState;
  }
}

void IRenderer2D::SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)
{
  hdx::SamplerState& CurrentSamplerState = CurrentSamplerStatus[_Slot];
  if (CurrentSamplerState != _SamplerState)
  {
    CurrentSamplerState = _SamplerState;
  }
}

void IRenderer2D::SetRasterizerState(const hdx::RasterizerState& _RasterizerState)
{
  if (CurrentRasterizerState != _RasterizerState)
  {
    CurrentRasterizerState = _RasterizerState;
  }
}

void IRenderer2D::SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
{
  if (CurrentDepthStencilState != _DepthStencilState)
  {
    CurrentDepthStencilState = _DepthStencilState;
  }
}

void IRenderer2D::SetTexture(const hdx::Texture& _Texture, UINT _Slot)
{
  hdx::Texture& CurrentTexture = CurrentTextures[_Slot - 1];
  if (CurrentTexture != _Texture)
  {
    CurrentTexture = _Texture;
  }
}

inline void CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  Engine::GetTexture()->SetShaderResouceView(_RenderTarget, Engine::GetRenderTarget()->GetShaderResourceView(_RenderTarget));
}

void IRenderer2D::RestoreRenderTarget()
{
  if (CurrentRenderTarget.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(CurrentRenderTarget);
    CurrentRenderTarget = hdx::RenderTarget();
  }
}

void IRenderer2D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
{
  if (CurrentRenderTarget != _RenderTarger)
  {
    if (CurrentRenderTarget.GetSize() != hdx::int2())
    {
      CreateTextureFromRenderTarget(CurrentRenderTarget);
    }
    CurrentRenderTarget = _RenderTarger;
  }
}

const hdx::VertexShader& IRenderer2D::GetVertexShader()const
{
  return CurrentVertexShader;
}

const hdx::PixelShader& IRenderer2D::GetPixelShader()const
{
  return CurrentPixelShader;
}

const hdx::BlendState& IRenderer2D::GetBlendState()const
{
  return CurrentBlendState;
}

const hdx::SamplerState& IRenderer2D::GetSamplerState(UINT _Slot)const
{
  return CurrentSamplerStatus[_Slot];
}

const hdx::RasterizerState& IRenderer2D::GetRasterizerState()const
{
  return CurrentRasterizerState;
}

const hdx::DepthStencilState& IRenderer2D::GetDepthStencilState()const
{
  return CurrentDepthStencilState;
}

const hdx::Texture& IRenderer2D::GetTexture(UINT _Slot)const
{
  return CurrentTextures[_Slot - 1];
}

const hdx::RenderTarget& IRenderer2D::GetRenderTarget()const
{
  return CurrentRenderTarget;
}
