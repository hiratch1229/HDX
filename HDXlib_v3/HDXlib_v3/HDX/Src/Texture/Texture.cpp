#include "../../Include/Texture.hpp"

#include "../Engine.hpp"
#include "../Texture/ITexture.hpp"
#include "../Renderer/Renderer2D/IRenderer2D.hpp"

#include "../../Include/System.hpp"

//****************************************************************************************************
//	Hdx2DObj
//****************************************************************************************************

namespace hdx
{
  Texture::Texture(const int2& _Size)
    : ID_(Engine::GetTexture()->Add(_Size)), Size_(_Size)
  {

  }

  //  ƒtƒ@ƒCƒ‹ƒpƒX‚©‚ç‰æ‘œ‚ðì¬
  Texture::Texture(const char* FilePath)
    : ID_(Engine::GetTexture()->Load(FilePath)), Size_(Engine::GetTexture()->GetSize(ID_))
  {

  }

  //  •`‰æ
  void Texture::Draw(bool _isFitScreen, const ColorF& _Color)const
  {
    Engine::GetRenderer2D()->Draw((*this), hdx::float2(0.0f, 0.0f), (_isFitScreen) ? hdx::System::GetWindowSize() : Size_, hdx::float2(0.0f, 0.0f), Size_, 0.0f, false, false, _Color);
  }

  //  •`‰æ
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color)const
  {
    Engine::GetRenderer2D()->Draw((*this), _DstLeftTop, _DstSize, _SrcLeftPos, _SrcSize, 0.0f, false, false, _Color);
  }

  //  •`‰æ
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color)const
  {
    Engine::GetRenderer2D()->Draw((*this), _DstLeftTop, _DstSize, _SrcLeftPos, _SrcSize, _Angle, false, false, _Color);
  }

  //  •`‰æ
  void Texture::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color)const
  {
    Engine::GetRenderer2D()->Draw((*this), _DstLeftTop, _DstSize, _SrcLeftPos, _SrcSize, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
  }
}
