#pragma once
#include <HDX/Types.hpp>

//  ライブラリ
namespace hdx
{
  struct InputElementDesc;

  //  頂点シェーダー
  class VertexShader
  {
  private:
    int ID_ = -1;
  public:
    int GetID()const { return ID_; }
  public:
    bool operator==(const VertexShader& _VertexShader)const { return ID_ == _VertexShader.ID_; }
    bool operator!=(const VertexShader& _VertexShader)const { return !((*this) == _VertexShader); }
  public:
    VertexShader() = default;
    VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], UINT _NumElements);
  };
}
