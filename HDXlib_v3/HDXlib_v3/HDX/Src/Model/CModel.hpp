#pragma once
#include "IModel.hpp"

#include "Src/NumberMap.hpp"
#include "Include/Constants.hpp"

#include <fbxsdk.h>

class CModel : public IModel
{
  static constexpr char kDelimiters[] = { '\\', '/' };
private:
  fbxsdk::FbxManager* pManager_;
  fbxsdk::FbxImporter* pImporter_;
  ID3D11Device* pDevice_;
  NumberMap<std::string, ModelData> ModelMap_;
private:
  void CreateBuffers(Vertex _Vertices[], int _VerticesNum, UINT _Indices[], int _IndicesNum, ID3D11Buffer** _ppVertexBuffer, ID3D11Buffer** _ppIndexBuffer);
public:
  CModel();

  ~CModel();

  void Initialize(ID3D11Device* _pDevice)override;

  void ModelUpdate(int _ID, float _DeltaTime, hdx::MotionData* _pMotionData)override;

  int Load(const char* _FilePath)override;

  int Load(const hdx::Rectangle& _Rectangle)override;

  int Load(const hdx::Cube& _Cube)override;

  int Load(const hdx::Cylinder& _Cylinder)override;

  int Load(const hdx::Sphere& _Sphere)override;

  int Load(const hdx::Capsule& _Capsule)override;

  const ModelData& GetModelData(int _ID)override;

  const std::vector<hdx::float3>& GetVertices(int _ID)override;

  const std::vector<UINT>& GetIndices(int _ID)override;

  const hdx::float3& GetScale(int _ID)override;

  float GetFrame(int _ID, int _MotionNumber)override;
};
