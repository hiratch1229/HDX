#include "../../Include/Model.hpp"

#include "../Engine.hpp"
#include "../Model/IModel.hpp"
#include "../Renderer/Renderer3D/IRenderer3D.hpp"

namespace hdx
{
  //  ファイルパスから作成
  Model::Model(const char* FilePath)
    : ID_(Engine::Get<IModel>()->Load(FilePath))
  {

  }

  //  矩形を作成
  Model::Model(const Rectangle& _Rectangle)
    : ID_(Engine::Get<IModel>()->Load(_Rectangle))
  {

  }

  //  立方体を作成
  Model::Model(const Cube& _Cube)
    : ID_(Engine::Get<IModel>()->Load(_Cube))
  {

  }

  //  円筒を作成
  Model::Model(const Cylinder& _Cylinder)
    : ID_(Engine::Get<IModel>()->Load(_Cylinder))
  {

  }

  void Model::Draw(const Matrix& _WorldMatrix, const ColorF& _Color)const
  {
    Engine::Get<IRenderer3D>()->Draw((*this), _WorldMatrix, _Color);
  }
}
