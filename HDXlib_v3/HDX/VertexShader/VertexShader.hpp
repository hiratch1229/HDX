#pragma once

//  ���C�u����
namespace hdx
{
  struct InputElementDesc;

  //  ���_�V�F�[�_�[
  class VertexShader
  {
  public:
    const int ID_ = -1;
  public:
    VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], unsigned int _NumElements);
  };
}
