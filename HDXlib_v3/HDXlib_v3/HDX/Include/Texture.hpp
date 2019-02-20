#pragma once
#include "Type2.hpp"
#include "Color.hpp"
#include "Angle.hpp"

namespace hdx
{
  //  2D画像
  class Texture
  {
  protected:
    int ID_;
    int2 Size_;
  protected:
    Texture(const int2& _Size);
  public:
    Texture();
    //  ファイルパスから画像を作成
    Texture(const char* FilePath);
    ~Texture() = default;
  public:
    int GetID()const { return ID_; }
    const int2& GetSize()const { return Size_; }
    int GetWidth()const { return Size_.x; }
    int GetHeight()const { return Size_.y; }
  public:
    bool operator==(const Texture& _Texture)const
    {
      return ID_ == _Texture.ID_;
    }
    bool operator!=(const Texture& _Texture)const
    {
      return !((*this) == _Texture);
    }
  public:
    //  描画
    //  _isFitScreen:trueで画面サイズに合わる
    //  _Color:色
    void Draw(bool _isFitScreen = false, const ColorF& _Color = hdx::Palette::White)const;
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, Size_, int2(0, 0), Size_, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _Angle:角度
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, Size_, int2(0, 0), Size_, _Angle, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _DstSize:描画サイズ
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _DstSize:描画サイズ
    //  _Angle:角度
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Angle, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _DstSize:描画サイズ
    //  _Angle:角度
    //  _HorizontalFlip:trueで左右反転
    //  _VerticalFlip:trueで上下反転
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _SrcLeftPos:画像の切抜の開始位置(左上基準)
    //  _SrcSize:画像の切抜のサイズ
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _SrcLeftPos:画像の切抜の開始位置(左上基準)
    //  _SrcSize:画像の切抜のサイズ
    //  _Angle:角度
    //  _HorizontalFlip:trueで左右反転
    //  _VerticalFlip:trueで上下反転
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Angle, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _SrcLeftPos:画像の切抜の開始位置(左上基準)
    //  _SrcSize:画像の切抜のサイズ
    //  _Angle:角度
    //  _HorizontalFlip:trueで左右反転
    //  _VerticalFlip:trueで上下反転
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
    }
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _DstSize:描画サイズ
    //  _SrcLeftPos:画像の切抜の開始位置(左上基準)
    //  _SrcSize:画像の切抜のサイズ
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color = hdx::Palette::White)const;
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _DstSize:描画サイズ
    //  _SrcLeftPos:画像の切抜の開始位置(左上基準)
    //  _SrcSize:画像の切抜のサイズ
    //  _Angle:角度
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const;
    //  描画
    //  _DstLeftTop:描画の開始位置(左上基準)
    //  _DstSize:描画サイズ
    //  _SrcLeftPos:画像の切抜の開始位置(左上基準)
    //  _SrcSize:画像の切抜のサイズ
    //  _Angle:角度
    //  _HorizontalFlip:trueで左右反転
    //  _VerticalFlip:trueで上下反転
    //  _Color:色
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const;
  };
}
