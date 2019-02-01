#include "Include/Model.hpp"

#include "Src/Engine.hpp"
#include "Src/Model/IModel.hpp"
#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"

namespace hdx
{
  //  �t�@�C���p�X����쐬
  Model::Model(const char* FilePath)
    : ID_(Engine::Get<IModel>()->Load(FilePath))
  {

  }

  //  ��`���쐬
  Model::Model(const Rectangle& _Rectangle)
    : ID_(Engine::Get<IModel>()->Load(_Rectangle))
  {

  }

  //  �����̂��쐬
  Model::Model(const Cube& _Cube)
    : ID_(Engine::Get<IModel>()->Load(_Cube))
  {

  }

  //  �~�����쐬
  Model::Model(const Cylinder& _Cylinder)
    : ID_(Engine::Get<IModel>()->Load(_Cylinder))
  {

  }

  void Model::Update(float _DeltaTime, MotionData* _pMotionData)const
  {
    Engine::Get<IModel>()->ModelUpdate(ID_, _DeltaTime, _pMotionData);
  }

  //  �`��
  void Model::Draw(const Matrix& _WorldMatrix, const ColorF& _Color)const
  {
    Engine::Get<IRenderer3D>()->Draw((*this), _WorldMatrix, { 0.0f, 0 }, _Color);
  }

  //  ���[�V�����L��`��
  void Model::Draw(const Matrix& _WorldMatrix, const MotionData& _MotionData, const ColorF& _Color)const
  {
    Engine::Get<IRenderer3D>()->Draw((*this), _WorldMatrix, _MotionData, _Color);
  }
  
  const std::vector<hdx::float3>& Model::GetVertices()const
  {
    return Engine::Get<IModel>()->GetVertices(ID_);
  }

  const std::vector<UINT>& Model::GetIndices()const
  {
    return Engine::Get<IModel>()->GetIndices(ID_);
  }

  const hdx::float3& Model::GetScale()const
  {
    return Engine::Get<IModel>()->GetScale(ID_);
  }

  float Model::GetFrame(int _MotionNumber)const
  {
    return Engine::Get<IModel>()->GetFrame(ID_, _MotionNumber);
  }
}
