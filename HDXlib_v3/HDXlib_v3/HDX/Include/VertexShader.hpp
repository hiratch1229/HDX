#pragma once
#include "Types.hpp"
#include "InputElementDesc.hpp"

//  ���C�u����
namespace hdx
{
  //  ���_�V�F�[�_�[
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
    VertexShader(const char* _FilePath);
  };
}
