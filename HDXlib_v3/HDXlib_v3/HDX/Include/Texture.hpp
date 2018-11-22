#pragma once
#include "Type2.hpp"
#include "Color.hpp"
#include "Angle.hpp"

//  ライブラリ
namespace hdx
{
  class Texture;

  //class TextureDesc
  //{
  //  const Texture* pTexture_;
  //private:
  //  float2 SrcPos_;
  //  float2 SrcSize_;
  //  float2 Size_;
  //  ColorF Color_;
  //  Degree Angle_;
  //  bool isHorizontalFlip_;
  //  bool isVerticalFlip_;
  //public:
  //  TextureDesc(const Texture* _pTexture, const float2& _SrcPos, const float2& _SrcSize)
  //    : pTexture_(_pTexture), SrcPos_(_SrcPos), SrcSize_(_SrcSize), Size_(_SrcSize), Color_({ 1.0f,1.0f,1.0f,1.0f }),
  //    Angle_(0.0f), isHorizontalFlip_(false), isVerticalFlip_(false) {}
  //  TextureDesc(const Texture* _pTexture, const float2& _SrcPos, const float2& _SrcSize, const float2& _Size, const ColorF& _Color, const Degree& _Angle, bool _isHorizontalFlip, bool _isVerticalFlip)
  //    : pTexture_(_pTexture), SrcPos_(_SrcPos), SrcSize_(_SrcSize), Size_(_Size), Color_(_Color), Angle_(_Angle), isHorizontalFlip_(_isHorizontalFlip), isVerticalFlip_(_isVerticalFlip) {}
  //  TextureDesc Scale(const float2& _Scale)const { return{ pTexture_,SrcPos_,SrcSize_,{ Size_.X*_Scale.X,Size_.Y*_Scale.Y },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc Scale(float _ScaleX, float _ScaleY)const { return{ pTexture_,SrcPos_,SrcSize_,{ Size_.Y*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc Scale(int _ScaleX, int _ScaleY)const { return{ pTexture_,SrcPos_,SrcSize_,{ Size_.X*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc Scale(int _ScaleX, float _ScaleY)const { return{ pTexture_,SrcPos_,SrcSize_,{ Size_.X*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc Scale(float _ScaleX, int _ScaleY)const { return{ pTexture_,SrcPos_,SrcSize_,{ Size_.X*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc Scale(float _Scale)const { return{ pTexture_,SrcPos_,SrcSize_,Size_*_Scale,Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc Scale(int _Scale)const { return{ pTexture_,SrcPos_,SrcSize_, Size_*static_cast<float>(_Scale),Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
  //  TextureDesc VerticalFlip()const { return{ pTexture_,SrcPos_,SrcSize_,Size_,Color_,Angle_,isHorizontalFlip_,true }; }
  //  TextureDesc HorizontalFlip()const { return{ pTexture_,SrcPos_,SrcSize_,Size_,Color_,Angle_,true,isVerticalFlip_ }; }
  //public:
  //  void Draw()const;
  //  void Draw(const float2& _LeftTopPos) {}
  //  void Draw(float _Left, float _Top) {}
  //  void Draw(int _Left, int _Top) {}
  //  void Draw(int _Left, float _Top) {}
  //  void Draw(float _Left, int _Top) {}
  //};

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
    int2 GetSize()const { return Size_; }
    int GetWidth()const { return Size_.X; }
    int GetHeight()const { return Size_.Y; }
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
    ////  (0,0)を基準にそのまま描画
    //TextureDesc operator()() { return Desc(this, { 0,0 }, { Width_,Height_ }); }
    ////  (SrcPos.x,SrcPos.y)を基準に(SrcSize.x,SrcSize.y)のみ描画
    //TextureDesc operator()(float2 _SrcPos, float2 _SrcSize) { return Desc(this, _SrcPos, _SrcSize); }
    //
    ////  (SrcPos.x,SrcPos.y)を基準に(SrcWidth,SrcHeight)のみ描画
    //TextureDesc operator()(float2 _SrcPos, float _SrcWidth, float _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    ////  (SrcPos.x,SrcPos.y)を基準に(SrcWidth,SrcHeight)のみ描画
    //TextureDesc operator()(float2 _SrcPos, int _SrcWidth, int _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    ////  (SrcPos.x,SrcPos.y)を基準に(SrcWidth,SrcHeight)のみ描画
    //TextureDesc operator()(float2 _SrcPos, int _SrcWidth, float _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    ////  (SrcPos.x,SrcPos.y)を基準に(SrcWidth,SrcHeight)のみ描画
    //TextureDesc operator()(float2 _SrcPos, float _SrcWidth, int _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    //
    ////  (SrcX,SrcY)を基準に(SrcSize.x,SrcSize.y)のみ描画
    //TextureDesc operator()(float _SrcX, float _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    ////  (SrcX,SrcY)を基準に(SrcSize.x,SrcSize.y)のみ描画
    //TextureDesc operator()(int _SrcX, int _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    ////  (SrcX,SrcY)を基準に(SrcSize.x,SrcSize.y)のみ描画
    //TextureDesc operator()(int _SrcX, float _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    ////  (SrcX,SrcY)を基準に(SrcSize.x,SrcSize.y)のみ描画
    //TextureDesc operator()(float _SrcX, int _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    //
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, float _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, int _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, int _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, float _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, int _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, int _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, float _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, int _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, int _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, float _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, float _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, int _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, float _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, float _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(float _SrcX, int _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)を基準に(SrcWidth,SrcHeight)のみ描画
    //Desc operator()(int _SrcX, float _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
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

  //inline void TextureDesc::Draw()const
  //{
  //  //pTexture_->Draw(0.0f, 0.0f, Size_.X, Size_.Y, SrcPos_.X, SrcPos_.Y, SrcSize_.X, SrcSize_.Y, Angle_, isHorizontalFlip_, isVerticalFlip_, Color_);
  //}
}
