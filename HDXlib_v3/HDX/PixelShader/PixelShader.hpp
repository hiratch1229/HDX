#pragma once

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  class PixelShader
  {
  private:
    int ID_ = -1;
  public:
    int GetID()const { return ID_; }
  public:
    bool operator==(const PixelShader& _PixelShader)const { return ID_ == _PixelShader.ID_; }
    bool operator!=(const PixelShader& _PixelShader)const { return !((*this) == _PixelShader); }
  public:
    PixelShader() = default;
    PixelShader(const char* _FilePath);
  };
}
