#pragma once

//  ライブラリ
namespace hdx
{
  struct InputElementDesc;

  //  頂点シェーダー
  class VertexShader
  {
  public:
    const int ID_;
  public:
    VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], unsigned int _NumElements);
  };
}
