#include "CModel.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Texture/ITexture.hpp"
#include "Src/Misc.hpp"

#include "Src/Constants.hpp"

#include <memory>
#include <algorithm>
#include <functional>

namespace
{
  inline void FetchBoneInfluences(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<BoneInfluencePerControlPoint>* _pInfluences)
  {
    const int NumberOfControlPoints = _pFbxMesh->GetControlPointsCount();
    _pInfluences->resize(NumberOfControlPoints);

    const int NumberOfDeformers = _pFbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);

    for (int IndexOfDeformer = 0; IndexOfDeformer < NumberOfDeformers; ++IndexOfDeformer)
    {
      fbxsdk::FbxSkin *pSkin = static_cast<fbxsdk::FbxSkin*>(_pFbxMesh->GetDeformer(IndexOfDeformer, fbxsdk::FbxDeformer::eSkin));

      const int NumberOfClusters = pSkin->GetClusterCount();
      for (int IndexOfClusters = 0; IndexOfClusters < NumberOfClusters; ++IndexOfClusters)
      {
        fbxsdk::FbxCluster* pCluster = pSkin->GetCluster(IndexOfClusters);

        const int NumberOfControlPointIndices = pCluster->GetControlPointIndicesCount();
        const int* ArrayOfControlPointIndices = pCluster->GetControlPointIndices();
        const double* ArrayOfControlPointWeights = pCluster->GetControlPointWeights();

        for (int i = 0; i < NumberOfControlPointIndices; ++i)
        {
          BoneInfluencePerControlPoint &InfluencePerControlPoint = _pInfluences->at(ArrayOfControlPointIndices[i]);
          BoneInfluence Influence;
          Influence.Index = IndexOfClusters;
          Influence.Weight = static_cast<float>(ArrayOfControlPointWeights[i]);
          InfluencePerControlPoint.push_back(Influence);
        }
      }
    }
  }

  inline void FetchBoneMatrices(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<Bone>& _Skeletal, const fbxsdk::FbxTime& _Time)
  {
    const int NumberOfDeformers = _pFbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);

    for (int IndexOfDeformer = 0; IndexOfDeformer < NumberOfDeformers; ++IndexOfDeformer)
    {
      fbxsdk::FbxSkin* pSkin = static_cast<fbxsdk::FbxSkin*>(_pFbxMesh->GetDeformer(IndexOfDeformer, fbxsdk::FbxDeformer::eSkin));

      const int NumberOfClusters = pSkin->GetClusterCount();
      _Skeletal.resize(NumberOfClusters);
      for (int IndexOfCluster = 0; IndexOfCluster < NumberOfClusters; ++IndexOfCluster)
      {
        Bone& Bone = _Skeletal.at(IndexOfCluster);

        fbxsdk::FbxCluster* pCluster = pSkin->GetCluster(IndexOfCluster);

        // this matrix trnasforms coordinates of the initial pose from mesh space to global space
        fbxsdk::FbxAMatrix ReferenceGlobalInitPosition;
        pCluster->GetTransformMatrix(ReferenceGlobalInitPosition);

        // this matrix trnasforms coordinates of the initial pose from bone space to global space
        fbxsdk::FbxAMatrix ClusterGlobalInitPosition;
        pCluster->GetTransformLinkMatrix(ClusterGlobalInitPosition);

        // this matrix trnasforms coordinates of the current pose from bone space to global space
        fbxsdk::FbxAMatrix ClusterGlobalCurrentPosition;
        ClusterGlobalCurrentPosition = pCluster->GetLink()->EvaluateGlobalTransform(_Time);

        // this matrix trnasforms coordinates of the current pose from mesh space to global space
        fbxsdk::FbxAMatrix ReferenceGlobalCurrentPosition;
        ReferenceGlobalCurrentPosition = _pFbxMesh->GetNode()->EvaluateGlobalTransform(_Time);

        // Matrices are defined using the Column Major scheme. When a FbxAMatrix represents a transformation
        // (translation, rotation and scale), the last row of the matrix represents the translation part of the transformation.
        const fbxsdk::FbxAMatrix Offset = ClusterGlobalInitPosition.Inverse() * ReferenceGlobalInitPosition;
        const fbxsdk::FbxAMatrix Pose = ReferenceGlobalCurrentPosition.Inverse() * ClusterGlobalCurrentPosition;

        for (int Row = 0; Row < 4; ++Row)
        {
          for (int Column = 0; Column < 4; ++Column)
          {
            Bone.Offset.m[Row][Column] = static_cast<float>(Offset.Get(Row, Column));
            Bone.Pose.m[Row][Column] = static_cast<float>(Pose.Get(Row, Column));
          }
        }
      }
    }
  }

  inline void FetchAnimations(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<SkeletalAnimation>* _pSkeletalAnimation)
  {
    // Get the list of all the animation stack.
    fbxsdk::FbxArray<FbxString*> ArrayOfAnimationStackNames;
    _pFbxMesh->GetScene()->FillAnimStackNameArray(ArrayOfAnimationStackNames);

    // Get the number of animations.
    const int NumberOfAnimations = ArrayOfAnimationStackNames.Size();
    (*_pSkeletalAnimation).resize(NumberOfAnimations);

    for (int IndexOfAnimation = 0; IndexOfAnimation < NumberOfAnimations; ++IndexOfAnimation)
    {
      // Get the FbxTime per animation's frame.
      const fbxsdk::FbxTime::EMode TimeMode = _pFbxMesh->GetScene()->GetGlobalSettings().GetTimeMode();
      fbxsdk::FbxTime FrameTime;
      FrameTime.SetTime(0, 0, 0, 1, 0, TimeMode);

      fbxsdk::FbxString* AnimationStackName = ArrayOfAnimationStackNames.GetAt(IndexOfAnimation);
      fbxsdk::FbxAnimStack* CurrentAnimationStack = _pFbxMesh->GetScene()->FindMember<fbxsdk::FbxAnimStack>(AnimationStackName->Buffer());
      _pFbxMesh->GetScene()->SetCurrentAnimationStack(CurrentAnimationStack);

      const fbxsdk::FbxTakeInfo* TakeInfo = _pFbxMesh->GetScene()->GetTakeInfo(AnimationStackName->Buffer());
      const fbxsdk::FbxTime StartTime = TakeInfo->mLocalTimeSpan.GetStart();
      const fbxsdk::FbxTime EndTime = TakeInfo->mLocalTimeSpan.GetStop();

      fbxsdk::FbxTime SamplingStep;
      SamplingStep.SetTime(0, 0, 1, 0, 0, TimeMode);
      SamplingStep = static_cast<fbxsdk::FbxLongLong>(SamplingStep.Get() * kModelAnimationSamplingTime);

      for (fbxsdk::FbxTime CurrentTime = StartTime; CurrentTime < EndTime; CurrentTime += SamplingStep)
      {
        Skeletal Skeletal;
        FetchBoneMatrices(_pFbxMesh, Skeletal, CurrentTime);
        (*_pSkeletalAnimation)[IndexOfAnimation].push_back(Skeletal);
      }

      delete ArrayOfAnimationStackNames[IndexOfAnimation];
    }
  }
}

void CModel::CreateBuffers(Vertex _Vertices[], int _VerticesNum, UINT _Indices[], int _IndicesNum, ID3D11Buffer** _ppVertexBuffer, ID3D11Buffer** _ppIndexBuffer)
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  D3D11_BUFFER_DESC VertexBufferDesc{};
  {
    VertexBufferDesc.ByteWidth = sizeof(Vertex)*_VerticesNum;
    VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.StructureByteStride = 0;
  }

  D3D11_SUBRESOURCE_DATA InitialData{};
  {
    InitialData.pSysMem = _Vertices;
    InitialData.SysMemPitch = 0;
    InitialData.SysMemSlicePitch = 0;
  }

  hr = pDevice_->CreateBuffer(&VertexBufferDesc, &InitialData, _ppVertexBuffer);
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

  D3D11_BUFFER_DESC IndexBufferDesc{};
  {
    IndexBufferDesc.ByteWidth = sizeof(UINT)*_IndicesNum;
    IndexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    InitialData.pSysMem = _Indices;
  }

  hr = pDevice_->CreateBuffer(&IndexBufferDesc, &InitialData, _ppIndexBuffer);
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");
}

CModel::CModel()
{
  TIMER_START("Model");

  //  FBXManager作成
  pManager_ = fbxsdk::FbxManager::Create();

  //  入力を設定
  pManager_->SetIOSettings(fbxsdk::FbxIOSettings::Create(pManager_, IOSROOT));

  //  インポーター作成
  pImporter_ = fbxsdk::FbxImporter::Create(pManager_, "");

  TIMER_END("Model");
}

CModel::~CModel()
{
  pManager_->Destroy();
}

void CModel::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

void CModel::ModelUpdate(int _ID, float _DeltaTime, hdx::MotionData* _pMotionData)
{
  assert(_pMotionData->Number < ModelMap_[_ID].Meshes[0].SkeletalAnimations.size());

  const auto& Mesh = ModelMap_[_ID].Meshes[0];

  const int SkeletalAnimationNum = Mesh.SkeletalAnimations[_pMotionData->Number].size();
  if (SkeletalAnimationNum <= 0)return;

  _pMotionData->Frame += _DeltaTime;

  int Frame = static_cast<int>(_pMotionData->Frame / kModelAnimationSamplingTime);
  while (Frame > SkeletalAnimationNum - 1)
  {
    Frame -= SkeletalAnimationNum;
    _pMotionData->Frame -= kModelAnimationSamplingTime * SkeletalAnimationNum;
  }
}

int CModel::Load(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = ModelMap_.find(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  char str[8];
  //  ファイル形式のみ抽出
  {
    const char* p = strrchr(_FilePath, '.');
    assert(p && ".がありません");
    strncpy_s(str, p, 4);
  }

  ////  Objファイルのロード
  //auto ObjLoader = [&]()->int
  //{
  //  UINT CurrentIndex = 0;
  //  UINT CurrentSubSetIndex = -1;
  //
  //  std::deque<hdx::float3> Positions;
  //  std::deque<hdx::float3> Normals;
  //  std::deque<hdx::float2> TexCoords;
  //
  //  std::fstream fin(_FilePath);
  //  _ASSERT_EXPR(fin, L"OBJ File not Found.");
  //
  //  std::deque<std::string> MtlFileNames;
  //
  //  while (fin)
  //  {
  //    char command[hdx::Constants::CharMaxNum];
  //    fin >> command;
  //
  //    if (strcmp(command, "mtllib") == 0)
  //    {
  //      char mtl[hdx::Constants::CharMaxNum];
  //      fin >> mtl;
  //
  //      MtlFileNames.push_back(mtl);
  //    }
  //    else if (strcmp(command, "v") == 0)
  //    {
  //      float x, y, z;
  //      fin >> x >> y >> z;
  //
  //      Positions.push_back({ x, y, z });
  //    }
  //    else if (strcmp(command, "vt") == 0)
  //    {
  //      float u, v;
  //      fin >> u >> v;
  //
  //      TexCoords.push_back({ u, v });
  //    }
  //    else if (strcmp(command, "vn") == 0)
  //    {
  //      float i, j, k;
  //      fin >> i >> j >> k;
  //
  //      Normals.push_back({ i, j, k });
  //    }
  //    else if (strcmp(command, "usemtl") == 0)
  //    {
  //      char usemtl[hdx::Constants::CharMaxNum];
  //
  //      fin >> usemtl;
  //      Subset Subset;
  //      Subset.UseMtl = usemtl;
  //      Subset.IndexStart = CurrentIndex;
  //      ++CurrentSubSetIndex;
  //      Subsets.push_back(Subset);
  //    }
  //    else if (strcmp(command, "f") == 0)
  //    {
  //      for (UINT i = 0; i < 3; ++i)
  //      {
  //        ++Subsets[CurrentSubSetIndex].IndexCount;
  //
  //        Vertex3D Vertex;
  //
  //        u_int v, vt, vn;
  //        fin >> v;
  //        Vertex.Position = Positions[v - 1];
  //        if (L'/' == fin.peek())
  //        {
  //          fin.ignore();
  //          if (L'/' != fin.peek())
  //          {
  //            fin >> vt;
  //            Vertex.Texcoord = TexCoords[vt - 1];
  //          }
  //          if (L'/' == fin.peek())
  //          {
  //            fin.ignore();
  //            fin >> vn;
  //            Vertex.Normal = Normals[vn - 1];
  //          }
  //        }
  //        (*Vertices).push_back(Vertex);
  //        (*Indices).push_back(CurrentIndex++);
  //      }
  //    }
  //
  //    fin.ignore(1024, '\n');
  //  }
  //
  //  fin.close();
  //
  //  //  objファイルが存在するフォルダ
  //  char Directory[hdx::Constants::CharMaxNum]{};
  //
  //  for (char Delimiter : kDelimiters)
  //  {
  //    //  後ろから区切り文字を判別
  //    const char* p = strrchr(const_cast<char*>(_FilePath), Delimiter);
  //
  //    //  区切り文字があれば
  //    if (p)
  //    {
  //      //  区切り文字までをフォルダ名として格納
  //      strncpy_s(Directory, _FilePath, (p + 1) - _FilePath);
  //    }
  //  }
  //
  //  //  Mtlファイルの数ループ
  //  while (!MtlFileNames.empty())
  //  {
  //    int CurrentMaterialIndex = -1;
  //
  //    //  Mtlファイルのファイルパスを作成
  //    char MtlFilePath[hdx::Constants::CharMaxNum]{};
  //    strcpy_s(MtlFilePath, Directory);
  //    strcat_s(MtlFilePath, MtlFileNames.front().c_str());
  //
  //    //  Mtlファイル読み込み
  //    std::fstream fin(MtlFilePath);
  //    MtlFileNames.pop_front();
  //
  //    Material Material;
  //
  //    while (fin)
  //    {
  //      wchar_t command[Constants::CharMaxNum];
  //      fin >> command;
  //
  //      if (wcscmp(command, L"newmtl") == 0)
  //      {
  //        wchar_t NewMtl[Constants::CharMaxNum];
  //        fin >> NewMtl;
  //
  //        Material.NewMtl = NewMtl;
  //
  //        Materials.push_back(Material);
  //        ++CurrentMaterialIndex;
  //      }
  //      else if (wcscmp(command, L"Ka") == 0)
  //      {
  //        float x, y, z;
  //        fin >> x >> y >> z;
  //
  //        Materials[CurrentMaterialIndex].Ka = DirectX::XMFLOAT3(x, y, z);
  //      }
  //      else if (wcscmp(command, L"Kd") == 0)
  //      {
  //        float x, y, z;
  //        fin >> x >> y >> z;
  //
  //        Materials[CurrentMaterialIndex].Kd = DirectX::XMFLOAT3(x, y, z);
  //      }
  //      else if (wcscmp(command, L"Ks") == 0)
  //      {
  //        float x, y, z;
  //        fin >> x >> y >> z;
  //
  //        Materials[CurrentMaterialIndex].Ks = DirectX::XMFLOAT3(x, y, z);
  //      }
  //      else if (wcscmp(command, L"illum") == 0)
  //      {
  //        UINT illum;
  //        fin >> illum;
  //  
  //        Materials[CurrentMaterialIndex].illum = illum;
  //      }
  //      else if (wcscmp(command, L"map_Kd") == 0)
  //      {
  //        wchar_t TextureFileName[Constants::CharMaxNum]{};
  //        fin >> TextureFileName;
  //
  //        //  テクスチャのファイルパスを作成
  //        wchar_t TextureFilePath[Constants::CharMaxNum]{};
  //        wcscpy_s(TextureFilePath, Directory);
  //        wcscat_s(TextureFilePath, TextureFileName);
  //
  //        Materials[CurrentMaterialIndex].map_Kd = TextureFileName;
  //
  //        HRESULT hr = DirectX::CreateWICTextureFromFile(detail::System::Get()->GetDevice(), TextureFilePath, nullptr, Materials[CurrentMaterialIndex].pShaderResourceView_.GetAddressOf());
  //        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateWICTextureFromFile");
  //      }
  //    }
  //
  //    for (auto& Material : Materials)
  //    {
  //      if (!Material.pShaderResourceView_)
  //      {
  //        detail::System::Get()->MakeDummyTexture(Material.pShaderResourceView_.GetAddressOf());
  //      }
  //    }
  //  }
  //
  //  return 0;
  //};

  //  Fbxファイルのロード
  auto FbxLoader = [&]()->int
  {
    //  Initialize the importer.
    bool ImportStatus = pImporter_->Initialize(_FilePath, -1, pManager_->GetIOSettings());
    _ASSERT_EXPR_A(ImportStatus, pImporter_->GetStatus().GetErrorString());

    //  Create a new scene so it can be populated by the imported file.
    fbxsdk::FbxScene* pScene = fbxsdk::FbxScene::Create(pManager_, "");

    //  Import the contentts of the file into the scene.
    ImportStatus = pImporter_->Import(pScene);
    _ASSERT_EXPR_A(ImportStatus, pImporter_->GetStatus().GetErrorString());

    //  Convert mesh,NURBS and patch into triangle mesh
    fbxsdk::FbxGeometryConverter GeometryConverter(pManager_);
    GeometryConverter.Triangulate(pScene, true);

    //  Fetch node attributes and materials under this node recursively.
    //  Currently only mesh.
    std::vector<fbxsdk::FbxNode*> FetchedMeshed;
    std::function<void(fbxsdk::FbxNode*)> Traverse = [&](fbxsdk::FbxNode* pNode)
    {
      if (pNode)
      {
        fbxsdk::FbxNodeAttribute* pFbxNodeAttribute = pNode->GetNodeAttribute();
        if (pFbxNodeAttribute)
        {
          switch (pFbxNodeAttribute->GetAttributeType())
          {
          case fbxsdk::FbxNodeAttribute::eMesh:
            FetchedMeshed.push_back(pNode);
            break;
          }
        }
        for (int i = 0, ChildCount = pNode->GetChildCount(); i < ChildCount; ++i)
        {
          Traverse(pNode->GetChild(i));
        }
      }
    };
    Traverse(pScene->GetRootNode());

    ModelData ModelData;

    const int NumberOfMeshes = FetchedMeshed.size();
    ModelData.Meshes.resize(NumberOfMeshes);

    for (int i = 0; i < NumberOfMeshes; ++i)
    {
      fbxsdk::FbxMesh* pFbxMesh = FetchedMeshed.at(i)->GetMesh();
      Mesh& Mesh = ModelData.Meshes.at(i);

      fbxsdk::FbxAMatrix GlobalTransform = pFbxMesh->GetNode()->EvaluateGlobalTransform(0);

      for (int Row = 0; Row < 4; ++Row)
      {
        for (int Column = 0; Column < 4; ++Column)
        {
          Mesh.GlobalTransform.m[Row][Column] = static_cast<float>(GlobalTransform[Row][Column]);
        }
      }

      std::vector<BoneInfluencePerControlPoint> BoneInfluences;

      FetchBoneInfluences(pFbxMesh, &BoneInfluences);
      FetchAnimations(pFbxMesh, &Mesh.SkeletalAnimations);

      std::vector<Subset>& Subsets = Mesh.Subsets;

      //  Fetch mesh data
      std::vector<Vertex> Vertices; //  VertexBuffer
      std::vector<UINT> Indices;   //  IndexBuffer
      UINT VertexCount = 0;

      //  Fetch material properties.
      const int NumberOfMaterials = pFbxMesh->GetNode()->GetMaterialCount();
      //  1つも無い時は1つ作成
      Subsets.resize((NumberOfMaterials > 0) ? NumberOfMaterials : 1);

      //  Count the faces of each material
      const int NumberOfPolygons = pFbxMesh->GetPolygonCount();
      Indices.resize(NumberOfPolygons * 3);

      //  Count the polygon count of each material
      if (NumberOfMaterials > 0)
      {
        for (int IndexOfPolygon = 0; IndexOfPolygon < NumberOfPolygons; ++IndexOfPolygon)
        {
          const UINT MaterialIndex = pFbxMesh->GetElementMaterial()->GetIndexArray().GetAt(IndexOfPolygon);
          Subsets.at(MaterialIndex).IndexCount += 3;
        }
      }

      //  Record the offset(how many vertex)
      int Offset = 0;
      for (Subset &Subset : Subsets)
      {
        Subset.IndexStart = Offset;
        Offset += Subset.IndexCount;
        //  This will be used as counter in the following procedures,rest to zero
        Subset.IndexCount = 0;
      }

      for (int IndexOfPolygon = 0; IndexOfPolygon < NumberOfPolygons; ++IndexOfPolygon)
      {
        //  The material for current face.
        int IndexOfMaterial = 0;
        if (NumberOfMaterials > 0)
        {
          IndexOfMaterial = pFbxMesh->GetElementMaterial()->GetIndexArray().GetAt(IndexOfPolygon);
        }

        //  Where should I save the vertex attribute index, according to the material
        Subset& Subset = Subsets.at(IndexOfMaterial);
        const int IndexOffset = Subset.IndexStart + Subset.IndexCount;

        const fbxsdk::FbxVector4* ArrayOfControlPoints = pFbxMesh->GetControlPoints();

        for (int IndexOfVertex = 0; IndexOfVertex < 3; ++IndexOfVertex)
        {
          Vertex Vertex;
          const int IndexOfControlPoint = pFbxMesh->GetPolygonVertex(IndexOfPolygon, IndexOfVertex);
          Vertex.Position.x = static_cast<float>(ArrayOfControlPoints[IndexOfControlPoint][0]);
          Vertex.Position.y = static_cast<float>(ArrayOfControlPoints[IndexOfControlPoint][1]);
          Vertex.Position.z = static_cast<float>(ArrayOfControlPoints[IndexOfControlPoint][2]);

          BoneInfluencePerControlPoint& InfluencesPerControlPoint = BoneInfluences.at(IndexOfControlPoint);
          if (InfluencesPerControlPoint.size() > 4)
          {
            std::sort(InfluencesPerControlPoint.begin(), InfluencesPerControlPoint.end(), [](const BoneInfluence& _Obj1, const BoneInfluence& _Obj2)->bool {
              return _Obj1.Weight > _Obj2.Weight;
            });

            float SumWeight = 0.0f;
            for (int i = 4, Size = InfluencesPerControlPoint.size(); i < Size; ++i)
            {
              SumWeight += InfluencesPerControlPoint[i].Weight;
            }
            InfluencesPerControlPoint[0].Weight += SumWeight;

            for (int i = 0, MaxCount = InfluencesPerControlPoint.size() - 4; i < MaxCount; ++i)
            {
              InfluencesPerControlPoint.pop_back();
            }
            assert(InfluencesPerControlPoint.size() <= 4);
          }

          for (int IndexOfInfluence = 0, Size = InfluencesPerControlPoint.size(); IndexOfInfluence < Size; ++IndexOfInfluence)
          {
            Vertex.BoneWeights[IndexOfInfluence] = InfluencesPerControlPoint.at(IndexOfInfluence).Weight;
            Vertex.BoneIndices[IndexOfInfluence] = InfluencesPerControlPoint.at(IndexOfInfluence).Index;
          }

          if (pFbxMesh->GetElementNormalCount())
          {
            fbxsdk::FbxVector4 Normal;
            pFbxMesh->GetPolygonVertexNormal(IndexOfPolygon, IndexOfVertex, Normal);
            Vertex.Normal.x = static_cast<float>(Normal[0]);
            Vertex.Normal.y = static_cast<float>(Normal[1]);
            Vertex.Normal.z = static_cast<float>(Normal[2]);
          }

          if (pFbxMesh->GetElementUVCount())
          {
            fbxsdk::FbxStringList UVNames;
            pFbxMesh->GetUVSetNames(UVNames);

            fbxsdk::FbxVector2 UV;
            bool UnMappedUV = false;
            pFbxMesh->GetPolygonVertexUV(IndexOfPolygon, IndexOfVertex, UVNames[0], UV, UnMappedUV);
            Vertex.Texcoord.x = static_cast<float>(UV[0]);
            Vertex.Texcoord.y = 1.0f - static_cast<float>(UV[1]);
          }

          Vertices.emplace_back(Vertex);
          Indices.at(IndexOffset + IndexOfVertex) = VertexCount++;
        }
        Subset.IndexCount += 3;
      }

      ITexture* pTexture = Engine::Get<ITexture>();

      //  Fetch material properties.
      for (int IndexOfMaterial = 0; IndexOfMaterial < NumberOfMaterials; ++IndexOfMaterial)
      {
        Subset& Subset = Subsets.at(IndexOfMaterial);

        const fbxsdk::FbxSurfaceMaterial* pSurfaceMaterial = pFbxMesh->GetNode()->GetMaterial(IndexOfMaterial);

        const fbxsdk::FbxProperty Property = pSurfaceMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse);
        const fbxsdk::FbxProperty Factor = pSurfaceMaterial->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuseFactor);

        if (Property.IsValid() && Factor.IsValid())
        {
          const fbxsdk::FbxDouble3 Color = Property.Get<fbxsdk::FbxDouble3>();
          const double f = Factor.Get<fbxsdk::FbxDouble>();
          Subset.Diffuse.Color.R = static_cast<float>(Color[0] * f);
          Subset.Diffuse.Color.G = static_cast<float>(Color[1] * f);
          Subset.Diffuse.Color.B = static_cast<float>(Color[2] * f);
          Subset.Diffuse.Color.A = 1.0f;
        }

        if (Property.IsValid())
        {
          const int NumberOfTextures = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();

          if (NumberOfTextures > 0)
          {
            const fbxsdk::FbxFileTexture* pFileTexture = Property.GetSrcObject<fbxsdk::FbxFileTexture>();
            if (pFileTexture)
            {
              //  fbxファイルが存在するフォルダ
              char Directory[kCharMaxNum]{};

              for (char Delimiter : kDelimiters)
              {
                //  後ろから区切り文字を判別
                const char* p = strrchr(const_cast<char*>(_FilePath), Delimiter);

                //  区切り文字があれば
                if (p)
                {
                  //  区切り文字までをフォルダ名として格納
                  strncpy_s(Directory, _FilePath, (p + 1) - _FilePath);
                }
              }

              char TextureFilePath[kCharMaxNum];

              if (strstr(str, ".fbx") != nullptr)
              {
                strcpy_s(TextureFilePath, Directory);
                strcat_s(TextureFilePath, pFileTexture->GetRelativeFileName());
              }
              else
              {
                strcpy_s(TextureFilePath, pFileTexture->GetFileName());
              }

              Subset.Diffuse.TextureID = pTexture->Load(TextureFilePath);
            }
          }
        }
      }

      for (auto& Subset : Subsets)
      {
        //  既に作成されている時はスルー
        if (Subset.Diffuse.TextureID >= 0) continue;

        Subset.Diffuse.TextureID = pTexture->kDummyTextureID;
      }

      std::sort(Subsets.begin(), Subsets.end());

      //  バッファの作成
      CreateBuffers(Vertices.data(), Vertices.size(), Indices.data(), Indices.size(), Mesh.pVertexBuffer.GetAddressOf(), Mesh.pIndexBuffer.GetAddressOf());

      for (auto& Vertex : Vertices)
      {
        ModelData.Vertices.push_back(Vertex.Position);
      }
      for (auto& Index : Indices)
      {
        ModelData.Indices.push_back(Index);
      }
    }

    hdx::float3 Min, Max;

    Min = Max = 0.0f;

    for (int i = 0, Size = ModelData.Vertices.size(); i < Size; ++i)
    {
      const hdx::float3 Pos = ModelData.Vertices[i];

      Min.x = (Pos.x < Min.x) ? Pos.x : Min.x;
      Min.y = (Pos.y < Min.y) ? Pos.y : Min.y;
      Min.z = (Pos.z < Min.z) ? Pos.z : Min.z;

      Max.x = (Pos.x > Max.x) ? Pos.x : Max.x;
      Max.y = (Pos.y > Max.y) ? Pos.y : Max.y;
      Max.z = (Pos.z > Max.z) ? Pos.z : Max.z;
    }

    ModelData.Scale = Max - Min;

    return ModelMap_.insert(_FilePath, ModelData);
  };

  return FbxLoader();

  //if (strstr(str, ".obj"))
  //{
  //  return ObjLoader();
  //}
  //else if (strstr(str, ".fbx"))
  //{
  //  return FbxLoader();
  //}
  //else
  //{
  //  assert(false && "対応していないファイル形式です");
  //}
}

int CModel::Load(const hdx::Rectangle& _Rectangle)
{
  const int TextureID = _Rectangle.Texture.GetID();

  char ModelName[kCharMaxNum];
  sprintf_s(ModelName, "Rectangle:%d", TextureID);

  //  既に作成されているか確認
  {
    const int ID = ModelMap_.find(ModelName);
    if (ID >= 0)
    {
      return ID;
    }
  }

  ModelData ModelData;
  ModelData.Meshes.resize(1);

  Mesh& Mesh = ModelData.Meshes[0];
  Mesh.Subsets.resize(1);

  Mesh.Subsets[0].Diffuse.TextureID = TextureID;
  Mesh.Subsets[0].IndexCount = 6;

  //  頂点情報設定
  Vertex Vertices[4];
  {
    Vertices[0].Position = { -0.5f, +0.5f, +0.0f };
    Vertices[1].Position = { +0.5f, +0.5f, +0.0f };
    Vertices[2].Position = { -0.5f, -0.5f, +0.0f };
    Vertices[3].Position = { +0.5f, -0.5f, +0.0f };
    Vertices[0].Normal = { +0.0f, +0.0f, -1.0f };
    Vertices[1].Normal = { +0.0f, +0.0f, -1.0f };
    Vertices[2].Normal = { +0.0f, +0.0f, -1.0f };
    Vertices[3].Normal = { +0.0f, +0.0f, -1.0f };
    Vertices[0].Texcoord = { +0.0f, +0.0f };
    Vertices[1].Texcoord = { +1.0f, +0.0f };
    Vertices[2].Texcoord = { +0.0f, +1.0f };
    Vertices[3].Texcoord = { +1.0f, +1.0f };
  }

  //  インデックス設定
  UINT Indices[6];
  {
    Indices[0] = 0;   //  1つ目の三角形
    Indices[1] = 1;   //  
    Indices[2] = 2;   //  
    Indices[3] = 1;   //  2つ目の三角形
    Indices[4] = 3;   //  
    Indices[5] = 2;   //  
  }

  CreateBuffers(Vertices, 4, Indices, 6, Mesh.pVertexBuffer.GetAddressOf(), Mesh.pIndexBuffer.GetAddressOf());

  for (int i = 0; i < 4; ++i)
  {
    ModelData.Vertices.push_back(Vertices[i].Position);
  }
  for (int i = 0; i < 6; ++i)
  {
    ModelData.Indices.push_back(Indices[i]);
  }

  hdx::float3 Min, Max;

  Min = Max = 0.0f;

  for (int i = 0, Size = ModelData.Vertices.size(); i < Size; ++i)
  {
    const hdx::float3 Pos = ModelData.Vertices[i];

    Min.x = (Pos.x < Min.x) ? Pos.x : Min.x;
    Min.y = (Pos.y < Min.y) ? Pos.y : Min.y;
    Min.z = (Pos.z < Min.z) ? Pos.z : Min.z;

    Max.x = (Pos.x > Max.x) ? Pos.x : Max.x;
    Max.y = (Pos.y > Max.y) ? Pos.y : Max.y;
    Max.z = (Pos.z > Max.z) ? Pos.z : Max.z;
  }

  ModelData.Scale = Max - Min;

  return ModelMap_.insert(ModelName, ModelData);
}

int CModel::Load(const hdx::Cube& _Cube)
{
  const int TextureID = _Cube.Texture.GetID();

  char ModelName[kCharMaxNum];
  sprintf_s(ModelName, "Cube:%d", TextureID);

  //  既に作成されているか確認
  {
    const int ID = ModelMap_.find(ModelName);
    if (ID >= 0)
    {
      return ID;
    }
  }

  ModelData ModelData;
  ModelData.Meshes.resize(1);

  Mesh& Mesh = ModelData.Meshes[0];
  Mesh.Subsets.resize(1);

  Mesh.Subsets[0].Diffuse.TextureID = TextureID;
  Mesh.Subsets[0].IndexCount = 36;

  //  頂点情報設定
  Vertex Vertices[24];
  {
    //  手前
    {
      Vertices[0].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[1].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[2].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[3].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[0].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[1].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[2].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[3].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[0].Texcoord = { +0.0f, +0.0f };
      Vertices[1].Texcoord = { +1.0f, +0.0f };
      Vertices[2].Texcoord = { +0.0f, +1.0f };
      Vertices[3].Texcoord = { +1.0f, +1.0f };
    }

    //	右
    {
      Vertices[4].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[5].Position = { +0.5f, +0.5f, +0.5f };
      Vertices[6].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[7].Position = { +0.5f, -0.5f, +0.5f };
      Vertices[4].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[5].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[6].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[7].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[4].Texcoord = { +0.0f, +0.0f };
      Vertices[5].Texcoord = { +1.0f, +0.0f };
      Vertices[6].Texcoord = { +0.0f, +1.0f };
      Vertices[7].Texcoord = { +1.0f, +1.0f };
    }

    //	上
    {
      Vertices[8].Position = { -0.5f, +0.5f, +0.5f };
      Vertices[9].Position = { +0.5f, +0.5f, +0.5f };
      Vertices[10].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[11].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[8].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[9].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[10].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[11].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[8].Texcoord = { +0.0f, +0.0f };
      Vertices[9].Texcoord = { +1.0f, +0.0f };
      Vertices[10].Texcoord = { +0.0f, +1.0f };
      Vertices[11].Texcoord = { +1.0f, +1.0f };
    }

    //	左
    {
      Vertices[12].Position = { -0.5f, +0.5f, +0.5f };
      Vertices[13].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[14].Position = { -0.5f, -0.5f, +0.5f };
      Vertices[15].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[12].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[13].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[14].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[15].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[12].Texcoord = { +0.0f, +0.0f };
      Vertices[13].Texcoord = { +1.0f, +0.0f };
      Vertices[14].Texcoord = { +0.0f, +1.0f };
      Vertices[15].Texcoord = { +1.0f, +1.0f };
    }

    //	下
    {
      Vertices[16].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[17].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[18].Position = { -0.5f, -0.5f, +0.5f };
      Vertices[19].Position = { +0.5f, -0.5f, +0.5f };
      Vertices[16].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[17].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[18].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[19].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[16].Texcoord = { +0.0f, +0.0f };
      Vertices[17].Texcoord = { +1.0f, +0.0f };
      Vertices[18].Texcoord = { +0.0f, +1.0f };
      Vertices[19].Texcoord = { +1.0f, +1.0f };
    }

    //	奥
    {
      Vertices[20].Position = { +0.5f, +0.5f, +0.5f };
      Vertices[21].Position = { -0.5f, +0.5f, +0.5f };
      Vertices[22].Position = { +0.5f, -0.5f, +0.5f };
      Vertices[23].Position = { -0.5f, -0.5f, +0.5f };
      Vertices[20].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[21].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[22].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[23].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[20].Texcoord = { +0.0f, +0.0f };
      Vertices[21].Texcoord = { +1.0f, +0.0f };
      Vertices[22].Texcoord = { +0.0f, +1.0f };
      Vertices[23].Texcoord = { +1.0f, +1.0f };
    }
  }

  //  インデックス設定
  UINT Indices[36];
  {
    Indices[0] = 0;   //  1つ目の三角形
    Indices[1] = 1;   //  
    Indices[2] = 2;   //  
    Indices[3] = 1;   //  2つ目の三角形
    Indices[4] = 3;   //  
    Indices[5] = 2;   //  
    Indices[6] = 4;   //  3つ目の三角形
    Indices[7] = 5;   //  
    Indices[8] = 6;   //  
    Indices[9] = 5;   //  4つ目の三角形
    Indices[10] = 7;  //  
    Indices[11] = 6;  //  
    Indices[12] = 8;  //  5つ目の三角形
    Indices[13] = 9;  //  
    Indices[14] = 10; //  
    Indices[15] = 9;  //  6つ目の三角形
    Indices[16] = 11; //  
    Indices[17] = 10; //  
    Indices[18] = 12; //  7つ目の三角形
    Indices[19] = 13; //  
    Indices[20] = 14; //  
    Indices[21] = 13; //  8つ目の三角形
    Indices[22] = 15; //  
    Indices[23] = 14; //  
    Indices[24] = 16; //  9つ目の三角形
    Indices[25] = 17; //  
    Indices[26] = 18; //  
    Indices[27] = 17; //  10つ目の三角形
    Indices[28] = 19; //  
    Indices[29] = 18; //  
    Indices[30] = 20; //  11つ目の三角形
    Indices[31] = 21; //  
    Indices[32] = 22; //  
    Indices[33] = 21; //  12つ目の三角形
    Indices[34] = 23; //  
    Indices[35] = 22; //  
  }

  CreateBuffers(Vertices, 24, Indices, 36, Mesh.pVertexBuffer.GetAddressOf(), Mesh.pIndexBuffer.GetAddressOf());

  for (int i = 0; i < 24; ++i)
  {
    ModelData.Vertices.push_back(Vertices[i].Position);
  }
  for (int i = 0; i < 36; ++i)
  {
    ModelData.Indices.push_back(Indices[i]);
  }

  hdx::float3 Min, Max;

  Min = Max = 0.0f;

  for (int i = 0, Size = ModelData.Vertices.size(); i < Size; ++i)
  {
    const hdx::float3 Pos = ModelData.Vertices[i];

    Min.x = (Pos.x < Min.x) ? Pos.x : Min.x;
    Min.y = (Pos.y < Min.y) ? Pos.y : Min.y;
    Min.z = (Pos.z < Min.z) ? Pos.z : Min.z;

    Max.x = (Pos.x > Max.x) ? Pos.x : Max.x;
    Max.y = (Pos.y > Max.y) ? Pos.y : Max.y;
    Max.z = (Pos.z > Max.z) ? Pos.z : Max.z;
  }

  ModelData.Scale = Max - Min;

  return ModelMap_.insert(ModelName, ModelData);
}

int CModel::Load(const hdx::Cylinder& _Cylinder)
{
  const int TextureID = _Cylinder.Texture.GetID();
  const UINT Slices = _Cylinder.Slices;
  char ModelName[kCharMaxNum];
  sprintf_s(ModelName, "Cylinder:%d,%d", TextureID, Slices);

  //  既に作成されているか確認
  {
    const int ID = ModelMap_.find(ModelName);
    if (ID >= 0)
    {
      return ID;
    }
  }

  const int VertexNum = (Slices + 1) * 2;
  const int IndexNum = Slices * 6 + Slices * 6;

  ModelData ModelData;
  ModelData.Meshes.resize(1);

  Mesh& Mesh = ModelData.Meshes[0];
  Mesh.Subsets.resize(1);

  Mesh.Subsets[0].Diffuse.TextureID = TextureID;
  Mesh.Subsets[0].IndexCount = IndexNum;

  std::unique_ptr<Vertex[]> Vertices(new Vertex[VertexNum]);
  std::unique_ptr<UINT[]> Indices(new UINT[IndexNum]);

  //  1つの三角形の角度
  const float Degree = 360.0f / Slices;

  //  頂点情報設定
  {
    //  上底の真ん中設定
    Vertices[0].Position = { 0.0f, +0.5f, 0.0f };
    //  上底の周り設定
    for (UINT i = 0; i < Slices; ++i)
    {
      Vertices[i + 1].Position = { 0.5f*cosf(hdx::Math::ToRadian(Degree*i)), +0.5f, 0.5f*sinf(hdx::Math::ToRadian(Degree*i)) };
    }
    //  下底の設定
    for (UINT i = 0; i <= Slices; ++i)
    {
      Vertices[(Slices + 1) + i] = Vertices[i];
      Vertices[(Slices + 1) + i].Position.y = -Vertices[i].Position.y;
    }
    //  上底の法線設定
    for (UINT i = 0; i <= Slices; ++i)
    {
      Vertices[i].Normal = { 0.0f, 1.0f, 0.0f };
    }
    //  下底の法線設定
    for (UINT i = 0; i <= Slices; ++i)
    {
      Vertices[(Slices + 1) + i].Normal = { 0.0f, -1.0f, 0.0f };
    }
  }

  //  インデックス設定
  {
    //  上底設定
    for (UINT i = 0; i < Slices; ++i)
    {
      Indices[i * 3 + 0] = 0;
      Indices[i * 3 + 1] = i + 2;
      Indices[i * 3 + 2] = i + 1;

      if (Indices[i * 3 + 1] > Slices) Indices[i * 3 + 1] -= Slices;
      if (Indices[i * 3 + 2] > Slices) Indices[i * 3 + 2] -= Slices;
    }
    //  下底設定
    for (UINT i = 0; i <= Slices; ++i)
    {
      Indices[((Slices * 1) + i) * 3 + 0] = (Slices + 1) + 0;
      Indices[((Slices * 1) + i) * 3 + 1] = (Slices + 1) + i + 1;
      Indices[((Slices * 1) + i) * 3 + 2] = (Slices + 1) + i + 2;

      if (Indices[((Slices * 1) + i) * 3 + 1] > (Slices + 1) * 2 - 1) Indices[((Slices * 1) + i) * 3 + 1] -= Slices;
      if (Indices[((Slices * 1) + i) * 3 + 2] > (Slices + 1) * 2 - 1) Indices[((Slices * 1) + i) * 3 + 2] -= Slices;
    }
    //  側面設定
    for (UINT i = 0; i < Slices; ++i)
    {
      Indices[((Slices * 2) + i) * 3 + 0] = i + 1;
      Indices[((Slices * 2) + i) * 3 + 1] = i + 2;
      Indices[((Slices * 2) + i) * 3 + 2] = i + (Slices + 1) + 1;

      if (Indices[((Slices * 2) + i) * 3 + 0] > Slices)				Indices[((Slices * 2) + i) * 3 + 0] -= Slices;
      if (Indices[((Slices * 2) + i) * 3 + 1] > Slices)				Indices[((Slices * 2) + i) * 3 + 1] -= Slices;
      if (Indices[((Slices * 2) + i) * 3 + 2] > (Slices + 1) * 2 - 1) Indices[((Slices * 2) + i) * 3 + 2] -= Slices;

      Indices[((Slices * 3) + i) * 3 + 0] = i + 2;
      Indices[((Slices * 3) + i) * 3 + 1] = i + (Slices + 1) + 2;
      Indices[((Slices * 3) + i) * 3 + 2] = i + (Slices + 1) + 1;

      if (Indices[((Slices * 3) + i) * 3 + 0] > Slices)				Indices[((Slices * 3) + i) * 3 + 0] -= Slices;
      if (Indices[((Slices * 3) + i) * 3 + 1] > (Slices + 1) * 2 - 1) Indices[((Slices * 3) + i) * 3 + 1] -= Slices;
      if (Indices[((Slices * 3) + i) * 3 + 2] > (Slices + 1) * 2 - 1) Indices[((Slices * 3) + i) * 3 + 2] -= Slices;
    }
  }

  CreateBuffers(Vertices.get(), VertexNum, Indices.get(), IndexNum, Mesh.pVertexBuffer.GetAddressOf(), Mesh.pIndexBuffer.GetAddressOf());

  for (int i = 0; i < VertexNum; ++i)
  {
    ModelData.Vertices.push_back(Vertices[i].Position);
  }
  for (int i = 0; i < IndexNum; ++i)
  {
    ModelData.Indices.push_back(Indices[i]);
  }

  hdx::float3 Min, Max;

  Min = Max = 0.0f;

  for (int i = 0, Size = ModelData.Vertices.size(); i < Size; ++i)
  {
    const hdx::float3 Pos = ModelData.Vertices[i];

    Min.x = (Pos.x < Min.x) ? Pos.x : Min.x;
    Min.y = (Pos.y < Min.y) ? Pos.y : Min.y;
    Min.z = (Pos.z < Min.z) ? Pos.z : Min.z;

    Max.x = (Pos.x > Max.x) ? Pos.x : Max.x;
    Max.y = (Pos.y > Max.y) ? Pos.y : Max.y;
    Max.z = (Pos.z > Max.z) ? Pos.z : Max.z;
  }

  ModelData.Scale = Max - Min;

  return ModelMap_.insert(ModelName, ModelData);
}

const ModelData& CModel::GetModelData(int _ID)
{
  return ModelMap_[_ID];
}

const std::vector<hdx::float3>& CModel::GetVertices(int _ID)
{
  return ModelMap_[_ID].Vertices;
}

const std::vector<UINT>& CModel::GetIndices(int _ID)
{
  return ModelMap_[_ID].Indices;
}

const hdx::float3& CModel::GetScale(int _ID)
{
  return ModelMap_[_ID].Scale;
}

float CModel::GetFrame(int _ID, int _MotionNumber)
{
  const Mesh& Mesh = ModelMap_[_ID].Meshes[0];

  return kModelAnimationSamplingTime * Mesh.SkeletalAnimations[_MotionNumber].size();
}
