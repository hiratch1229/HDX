#pragma once
#include <HDX/Type2.hpp>
#include <HDX/Color.hpp>
#include <HDX/Angle.hpp>

//  ëOï˚êÈåæ
namespace detail
{
  struct Vertex2D;
}

//  ÉâÉCÉuÉâÉä
namespace hdx
{
  class Sprite;

  class SpriteDesc
  {
    const Sprite* pSprite_;
  private:
    float2 SrcPos_;
    float2 SrcSize_;
    float2 Size_;
    ColorF Color_;
    Degree Angle_;
    bool isHorizontalFlip_;
    bool isVerticalFlip_;
  public:
    SpriteDesc(const Sprite* _pSprite, const float2& _SrcPos, const float2& _SrcSize)
      : pSprite_(_pSprite), SrcPos_(_SrcPos), SrcSize_(_SrcSize), Size_(_SrcSize), Color_({ 1.0f,1.0f,1.0f,1.0f }),
      Angle_(0.0f), isHorizontalFlip_(false), isVerticalFlip_(false) {}
    SpriteDesc(const Sprite* _pSprite, const float2& _SrcPos, const float2& _SrcSize, const float2& _Size, const ColorF& _Color, const Degree& _Angle, bool _isHorizontalFlip, bool _isVerticalFlip)
      : pSprite_(_pSprite), SrcPos_(_SrcPos), SrcSize_(_SrcSize), Size_(_Size), Color_(_Color), Angle_(_Angle), isHorizontalFlip_(_isHorizontalFlip), isVerticalFlip_(_isVerticalFlip) {}
    SpriteDesc Scale(const float2& _Scale)const { return{ pSprite_,SrcPos_,SrcSize_,{ Size_.X*_Scale.X,Size_.Y*_Scale.Y },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc Scale(float _ScaleX, float _ScaleY)const { return{ pSprite_,SrcPos_,SrcSize_,{ Size_.Y*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc Scale(int _ScaleX, int _ScaleY)const { return{ pSprite_,SrcPos_,SrcSize_,{ Size_.X*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc Scale(int _ScaleX, float _ScaleY)const { return{ pSprite_,SrcPos_,SrcSize_,{ Size_.X*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc Scale(float _ScaleX, int _ScaleY)const { return{ pSprite_,SrcPos_,SrcSize_,{ Size_.X*_ScaleX,Size_.Y*_ScaleY },Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc Scale(float _Scale)const { return{ pSprite_,SrcPos_,SrcSize_,Size_*_Scale,Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc Scale(int _Scale)const { return{ pSprite_,SrcPos_,SrcSize_, Size_*static_cast<float>(_Scale),Color_,Angle_,isHorizontalFlip_,isVerticalFlip_ }; }
    SpriteDesc VerticalFlip()const { return{ pSprite_,SrcPos_,SrcSize_,Size_,Color_,Angle_,isHorizontalFlip_,true }; }
    SpriteDesc HorizontalFlip()const { return{ pSprite_,SrcPos_,SrcSize_,Size_,Color_,Angle_,true,isVerticalFlip_ }; }
  public:
    void Draw()const;
    void Draw(const float2& _LeftTopPos) {}
    void Draw(float _Left, float _Top) {}
    void Draw(int _Left, int _Top) {}
    void Draw(int _Left, float _Top) {}
    void Draw(float _Left, int _Top) {}
  };

  class VertexShader;
  class PixelShader;

  //  2DâÊëú
  class Sprite
  {
  public:
    const int ID_;
    union
    {
      const int2 Size_;
      struct
      {
        const int x;
        const int y;
      };
    };
  private:
    //  ï`âÊç≈èIèàóù
    //  (ï`âÊä÷êîÇí«â¡Ç∑ÇÈèÍçáç≈å„Ç…åƒÇÒÇ≈Ç≠ÇæÇ≥Ç¢)
    void Draw2D(const detail::Vertex2D* v)const;
  public:
    //  ÉtÉ@ÉCÉãÉpÉXÇ©ÇÁâÊëúÇçÏê¨
    Sprite(const char* FilePath);
    //Sprite();
    ~Sprite() {}
  public:
    ////  (0,0)ÇäÓèÄÇ…ÇªÇÃÇ‹Ç‹ï`âÊ
    //SpriteDesc operator()() { return Desc(this, { 0,0 }, { Width_,Height_ }); }
    ////  (SrcPos.x,SrcPos.y)ÇäÓèÄÇ…(SrcSize.x,SrcSize.y)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float2 _SrcPos, float2 _SrcSize) { return Desc(this, _SrcPos, _SrcSize); }
    //
    ////  (SrcPos.x,SrcPos.y)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float2 _SrcPos, float _SrcWidth, float _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    ////  (SrcPos.x,SrcPos.y)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float2 _SrcPos, int _SrcWidth, int _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    ////  (SrcPos.x,SrcPos.y)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float2 _SrcPos, int _SrcWidth, float _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    ////  (SrcPos.x,SrcPos.y)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float2 _SrcPos, float _SrcWidth, int _SrcHeight) { return Desc(this, _SrcPos, { _SrcWidth,_SrcHeight }); }
    //
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcSize.x,SrcSize.y)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float _SrcX, float _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcSize.x,SrcSize.y)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(int _SrcX, int _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcSize.x,SrcSize.y)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(int _SrcX, float _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcSize.x,SrcSize.y)ÇÃÇ›ï`âÊ
    //SpriteDesc operator()(float _SrcX, int _SrcY, float2 _SrcSize) { return Desc(this, { _SrcX,_SrcY }, _SrcSize); }
    //
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, float _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, int _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, int _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, float _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, int _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, int _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, float _SrcY, int _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, int _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, int _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, float _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, float _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, int _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, float _SrcY, float _SrcWidth, int _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, float _SrcY, int _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(float _SrcX, int _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
    ////  (SrcX,SrcY)ÇäÓèÄÇ…(SrcWidth,SrcHeight)ÇÃÇ›ï`âÊ
    //Desc operator()(int _SrcX, float _SrcY, float _SrcWidth, float _SrcHeight) { return Desc(this, { _SrcX,_SrcY }, { _SrcWidth,_SrcHeight }); }
  public:
    //  ï`âÊ
    //  _isFitScreen:trueÇ≈âÊñ ÉTÉCÉYÇ…çáÇÌÇÈ
    //  _Color:êF
    void Draw(bool _isFitScreen = false, const ColorF& _Color = hdx::Palette::White)const;
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, Size_, int2(0, 0), Size_, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _Angle:äpìx
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, Size_, int2(0, 0), Size_, _Angle, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _DstSize:ï`âÊÉTÉCÉY
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _DstSize:ï`âÊÉTÉCÉY
    //  _Angle:äpìx
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Angle, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _DstSize:ï`âÊÉTÉCÉY
    //  _Angle:äpìx
    //  _HorizontalFlip:trueÇ≈ç∂âEîΩì]
    //  _VerticalFlip:trueÇ≈è„â∫îΩì]
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcLeftPos:âÊëúÇÃêÿî≤ÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcSize:âÊëúÇÃêÿî≤ÇÃÉTÉCÉY
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcLeftPos:âÊëúÇÃêÿî≤ÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcSize:âÊëúÇÃêÿî≤ÇÃÉTÉCÉY
    //  _Angle:äpìx
    //  _HorizontalFlip:trueÇ≈ç∂âEîΩì]
    //  _VerticalFlip:trueÇ≈è„â∫îΩì]
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Angle, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcLeftPos:âÊëúÇÃêÿî≤ÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcSize:âÊëúÇÃêÿî≤ÇÃÉTÉCÉY
    //  _Angle:äpìx
    //  _HorizontalFlip:trueÇ≈ç∂âEîΩì]
    //  _VerticalFlip:trueÇ≈è„â∫îΩì]
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
    }
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _DstSize:ï`âÊÉTÉCÉY
    //  _SrcLeftPos:âÊëúÇÃêÿî≤ÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcSize:âÊëúÇÃêÿî≤ÇÃÉTÉCÉY
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color = hdx::Palette::White)const;
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _DstSize:ï`âÊÉTÉCÉY
    //  _SrcLeftPos:âÊëúÇÃêÿî≤ÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcSize:âÊëúÇÃêÿî≤ÇÃÉTÉCÉY
    //  _Angle:äpìx
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const;
    //  ï`âÊ
    //  _DstLeftTop:ï`âÊÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _DstSize:ï`âÊÉTÉCÉY
    //  _SrcLeftPos:âÊëúÇÃêÿî≤ÇÃäJénà íu(ç∂è„äÓèÄ)
    //  _SrcSize:âÊëúÇÃêÿî≤ÇÃÉTÉCÉY
    //  _Angle:äpìx
    //  _HorizontalFlip:trueÇ≈ç∂âEîΩì]
    //  _VerticalFlip:trueÇ≈è„â∫îΩì]
    //  _Color:êF
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const;
  };

  inline void SpriteDesc::Draw()const
  {
    //pSprite_->Draw(0.0f, 0.0f, Size_.X, Size_.Y, SrcPos_.X, SrcPos_.Y, SrcSize_.X, SrcSize_.Y, Angle_, isHorizontalFlip_, isVerticalFlip_, Color_);
  }
}
