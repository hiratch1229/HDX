#pragma once
#include "Type2.hpp"
#include "Color.hpp"
#include "Angle.hpp"

namespace hdx
{
  //  2D�摜
  class Texture
  {
  protected:
    int ID_;
    int2 Size_;
  protected:
    Texture(const int2& _Size);
  public:
    Texture();
    //  �t�@�C���p�X����摜���쐬
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
    //  �`��
    //  _isFitScreen:true�ŉ�ʃT�C�Y�ɍ����
    //  _Color:�F
    void Draw(bool _isFitScreen = false, const ColorF& _Color = hdx::Palette::White)const;
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, Size_, int2(0, 0), Size_, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _Angle:�p�x
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, Size_, int2(0, 0), Size_, _Angle, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _DstSize:�`��T�C�Y
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _DstSize:�`��T�C�Y
    //  _Angle:�p�x
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Angle, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _DstSize:�`��T�C�Y
    //  _Angle:�p�x
    //  _HorizontalFlip:true�ō��E���]
    //  _VerticalFlip:true�ŏ㉺���]
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _DstSize, int2(0, 0), Size_, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _SrcLeftPos:�摜�̐ؔ��̊J�n�ʒu(����)
    //  _SrcSize:�摜�̐ؔ��̃T�C�Y
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _SrcLeftPos:�摜�̐ؔ��̊J�n�ʒu(����)
    //  _SrcSize:�摜�̐ؔ��̃T�C�Y
    //  _Angle:�p�x
    //  _HorizontalFlip:true�ō��E���]
    //  _VerticalFlip:true�ŏ㉺���]
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Angle, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _SrcLeftPos:�摜�̐ؔ��̊J�n�ʒu(����)
    //  _SrcSize:�摜�̐ؔ��̃T�C�Y
    //  _Angle:�p�x
    //  _HorizontalFlip:true�ō��E���]
    //  _VerticalFlip:true�ŏ㉺���]
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const
    {
      Draw(_DstLeftTop, _SrcSize, _SrcLeftPos, _SrcSize, _Angle, _HorizontalFlip, _VerticalFlip, _Color);
    }
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _DstSize:�`��T�C�Y
    //  _SrcLeftPos:�摜�̐ؔ��̊J�n�ʒu(����)
    //  _SrcSize:�摜�̐ؔ��̃T�C�Y
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const ColorF& _Color = hdx::Palette::White)const;
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _DstSize:�`��T�C�Y
    //  _SrcLeftPos:�摜�̐ؔ��̊J�n�ʒu(����)
    //  _SrcSize:�摜�̐ؔ��̃T�C�Y
    //  _Angle:�p�x
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, const ColorF& _Color = hdx::Palette::White)const;
    //  �`��
    //  _DstLeftTop:�`��̊J�n�ʒu(����)
    //  _DstSize:�`��T�C�Y
    //  _SrcLeftPos:�摜�̐ؔ��̊J�n�ʒu(����)
    //  _SrcSize:�摜�̐ؔ��̃T�C�Y
    //  _Angle:�p�x
    //  _HorizontalFlip:true�ō��E���]
    //  _VerticalFlip:true�ŏ㉺���]
    //  _Color:�F
    void Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color = hdx::Palette::White)const;
  };
}
