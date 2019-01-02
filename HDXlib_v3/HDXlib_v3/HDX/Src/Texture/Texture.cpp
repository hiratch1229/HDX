#include "Include/Texture.hpp"

#include "Src/Engine.hpp"
#include "Src/Texture/ITexture.hpp"
#include "Src/Renderer/Renderer2D/IRenderer2D.hpp"

#include "Include/System.hpp"

namespace hdx
{
  Texture::Texture(const int2& _Size)
    : ID_(Engine::Get<ITexture>()->Add(_Size)), Size_(_Size)
  {

  }

  Texture::Texture()
    : ID_(ITexture::kDummyTextureID), Size_(ITexture::kDummyTextureSize)
  {

  }

  //  ÉtÉ@ÉCÉãÉpÉXÇ©ÇÁâÊëúÇçÏê¨
  Texture::Texture(const char* FilePath)
    : ID_(Engine::Get<ITexture>()->Load(FilePath)), Size_(Engine::Get<ITexture>()->GetSize(ID_))
  {

  }

  //  ï`âÊ
  void Texture::Draw(bool _isFitScreen, const ColorF& _Color)const
  {
    Engine::Get<IRenderer2D>()->Draw((*this), hdx::float2(0.0f, 0.0f), (_isFitScreen) ? hdx::System::GetWindowSize() : Size_, hdx::float2(0.0f, 0.0f), Size_, 0.0f, false, false, _Color);
  }

  //  ï`âÊ
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color)const
  {
    Engine::Get<IRenderer2D>()->Draw((*this), _DstLeftTop, _DstSize, _SrcLeftPos, _SrcSize, 0.0f, false, false, _Color);
  }

  //  ï`âÊ
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color)const
  {
    Engine::Get<IRenderer2D>()->Draw((*this), _DstLeftTop, _DstSize, _SrcLeftPos, _SrcSize, _Angle, false, false, _Color);
  }

  //  ï`âÊ
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color)const
  {
    Engine::Get<IRenderer2D>()->Draw((*this), _DstLeftTop, _DstSize, _SrcLeftPos, _SrcSize, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
  }
}
