#include <HDX/SkinnedMesh.hpp>
#include <HDX/System/System.hpp>
#include <HDX/ConstantBuffer.hpp>
#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>

#include <fbxsdk.h>
#include <vector>
#include <functional>
#include <crtdbg.h>
#include <WICTextureLoader.h>

namespace hdx
{
  SkinnedMesh::SkinnedMesh(const char* FilePath)
  {
    //  Create the FBX SDK manager
    fbxsdk::FbxManager* pManager = fbxsdk::FbxManager::Create();

    //  Create an IOSettings object. IOSROOT is defined in Fbxiosettingspath.h
    pManager->SetIOSettings(fbxsdk::FbxIOSettings::Create(pManager, IOSROOT));

    //  Create an importer.
    fbxsdk::FbxImporter* pImporter = fbxsdk::FbxImporter::Create(pManager, "");

    //  Initialize the importer.
    bool ImportStatus = pImporter->Initialize(FilePath, -1, pManager->GetIOSettings());
    _ASSERT_EXPR(ImportStatus, pImporter->GetStatus().GetErrorString());

    //  Create a new scene so it can be populated by the imported file.
    fbxsdk::FbxScene* pScene = fbxsdk::FbxScene::Create(pManager, "");

    //  Import the contentts of the file into the scene.
    ImportStatus = pImporter->Import(pScene);
    _ASSERT_EXPR(ImportStatus, pImporter->GetStatus().GetErrorString());

    //  Convert mesh,NURBS and patch into triangle mesh
    fbxsdk::FbxGeometryConverter GeometryConverter(pManager);
    GeometryConverter.Triangulate(pScene, true/*replace*/);

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

    //fbxsdk::FbxMesh* pFbxMesh = FetchedMeshed.at(0)->GetMesh(); //  Currently only one mesh.
    const int NumberOfMeshes = FetchedMeshed.size();
    Meshes_.resize(NumberOfMeshes);

    for (int i = 0; i < NumberOfMeshes; ++i)
    {
      fbxsdk::FbxMesh* pFbxMesh = FetchedMeshed.at(i)->GetMesh();
      fbxsdk::FbxAMatrix GlobalTransform = pFbxMesh->GetNode()->EvaluateGlobalTransform(0);

      Mesh& Mesh = Meshes_.at(i);

      for (int Row = 0; Row < 4; ++Row)
      {
        for (int Column = 0; Column < 4; ++Column)
        {
          Mesh.GlobalTransform.m[Row][Column] = static_cast<float>(GlobalTransform[Row][Column]);
        }
      }

      FetchBoneInfluences(pFbxMesh, &BoneInfluences_);

      //fbxsdk::FbxTime FrameTime;
      //FrameTime.SetTime(0, 0, 0, 1, 0, pFbxMesh->GetScene()->GetGlobalSettings().GetTimeMode());
      //FetchBoneMatrices(pFbxMesh, Mesh.Skeletal, FrameTime * 20);

      FetchAnimations(pFbxMesh, Mesh.SkeletalAnimation);

      std::vector<Subset>& Subsets = Mesh.Subsets;

      //  Fetch mesh data
      std::vector<Vertex3D> Vertices; //  VertexBuffer
      std::vector<UINT> Indices;      //  IndexBuffer
      UINT VertexCount = 0;

      //  Fetch material properties.
      const int NumberOfMaterials = pFbxMesh->GetNode()->GetMaterialCount();
      //  1つも無い時は1つ作成(仮)
      Subsets.resize((NumberOfMaterials == 0) ? 1 : NumberOfMaterials);

      const int NumberOfPolygons = pFbxMesh->GetPolygonCount();
      Indices.resize(NumberOfPolygons * 3);

      //  Count the polygon count of each material
      if (NumberOfMaterials > 0)
      {
        //  Count the faces of each material
        const int NumberOfPolygons = pFbxMesh->GetPolygonCount();

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
          Vertex3D Vertex;
          const int IndexOfControlPoint = pFbxMesh->GetPolygonVertex(IndexOfPolygon, IndexOfVertex);
          Vertex.Position.X = static_cast<float>(ArrayOfControlPoints[IndexOfControlPoint][0]);
          Vertex.Position.Y = static_cast<float>(ArrayOfControlPoints[IndexOfControlPoint][1]);
          Vertex.Position.Z = static_cast<float>(ArrayOfControlPoints[IndexOfControlPoint][2]);

          BoneInfluencePerControlPoint& InfluencesPerControlPoint = BoneInfluences_.at(IndexOfControlPoint);
          for (int IndexOfInfluence = 0, Size = InfluencesPerControlPoint.size(); IndexOfInfluence < Size; ++IndexOfInfluence)
          {
            Vertex.BoneWeights[IndexOfInfluence] = InfluencesPerControlPoint.at(IndexOfInfluence).Weight;
            Vertex.BoneIndices[IndexOfInfluence] = InfluencesPerControlPoint.at(IndexOfInfluence).Index;
          }

          if (pFbxMesh->GetElementNormalCount())
          {
            fbxsdk::FbxVector4 Normal;
            pFbxMesh->GetPolygonVertexNormal(IndexOfPolygon, IndexOfVertex, Normal);
            Vertex.Normal.X = static_cast<float>(Normal[0]);
            Vertex.Normal.Y = static_cast<float>(Normal[1]);
            Vertex.Normal.Z = static_cast<float>(Normal[2]);
          }

          if (pFbxMesh->GetElementUVCount())
          {
            fbxsdk::FbxStringList UVNames;
            pFbxMesh->GetUVSetNames(UVNames);

            fbxsdk::FbxVector2 UV;
            bool UnMappedUV = false;
            pFbxMesh->GetPolygonVertexUV(IndexOfPolygon, IndexOfVertex, UVNames[0], UV, UnMappedUV);
            Vertex.Texcoord.X = static_cast<float>(UV[0]);
            Vertex.Texcoord.Y = 1.0f - static_cast<float>(UV[1]);
          }

          Vertices.push_back(Vertex);
          //Indices.push_back(VertexCount++);
          Indices.at(IndexOffset + IndexOfVertex) = static_cast<UINT>(VertexCount++);
        }
        Subset.IndexCount += 3;
      }

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
          Subset.Diffuse.Color_.R = static_cast<float>(Color[0] * f);
          Subset.Diffuse.Color_.G = static_cast<float>(Color[1] * f);
          Subset.Diffuse.Color_.B = static_cast<float>(Color[2] * f);
          Subset.Diffuse.Color_.A = 1.0f;
        }

        if (Property.IsValid())
        {
          const int NumberOfTextures = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();

          if (NumberOfTextures > 0)
          {
            const fbxsdk::FbxFileTexture* pFileTexture = Property.GetSrcObject<fbxsdk::FbxFileTexture>();
            if (pFileTexture)
            {
              wchar_t wFbxFileName[256];
              mbstowcs_s(nullptr, wFbxFileName, FilePath, 256);

              //  区切り文字
              static constexpr wchar_t kDelimiters[] = { L'\\', L'/' };
              //  objファイルが存在するフォルダ
              wchar_t Directory[256]{};

              for (wchar_t Delimiter : kDelimiters)
              {
                //  後ろから区切り文字を判別
                const wchar_t* p = wcsrchr(wFbxFileName, Delimiter);

                //  区切り文字があれば
                if (p)
                {
                  //  区切り文字までをフォルダ名として格納
                  wcsncpy_s(Directory, wFbxFileName, (p + 1) - wFbxFileName);
                }
              }

              wchar_t wFilePath[256]{};
              bool isFbxModel = strstr(FilePath, ".fbx") != nullptr;

              if (isFbxModel)
              {
                wchar_t wFileName[256];
                mbstowcs_s(nullptr, wFileName, pFileTexture->GetRelativeFileName(), 256);

                //  objファイルが存在するフォルダ
                wchar_t wTextureFileName[256];
                wcsncpy_s(wTextureFileName, wFileName, 256);
                
                for (wchar_t Delimiter : kDelimiters)
                {
                  //  後ろから区切り文字を判別
                  const wchar_t* p = wcsrchr(wFileName, Delimiter);

                  //  区切り文字があれば
                  if (p)
                  {
                    //  区切り文字までをフォルダ名として格納
                    wcsncpy_s(wTextureFileName, p, 256);
                  }
                }

                //  Mtlファイルのファイルパスを作成
                wcscpy_s(wFilePath, Directory);
                wcscat_s(wFilePath, wTextureFileName);
              }
              else
              {
                mbstowcs_s(nullptr, wFilePath, pFileTexture->GetFileName(), 256);
              }

              HRESULT hr = DirectX::CreateWICTextureFromFile(detail::System::Get()->GetDevice(), wFilePath, nullptr, Subset.Diffuse.pShaderResourceView_.GetAddressOf());
              _ASSERT_EXPR(SUCCEEDED(hr), L"CreateWICTextureFromFile");
            }
          }
        }
      }

      for (auto& Subset : Subsets)
      {
        //  既に作成されている時はスルー
        if (Subset.Diffuse.pShaderResourceView_) continue;

        detail::System::Get()->MakeDummyTexture(Subset.Diffuse.pShaderResourceView_.GetAddressOf());
      }

      //  バッファの作成
      CreateBuffers(Vertices.data(), Vertices.size(), Indices.data(), Indices.size(), i);
    }

    pManager->Destroy();
  }

  void SkinnedMesh::Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, float _ElapsedTime, const ColorF& _MaterialColor, bool isWireFrame, const VertexShader* _pVertexShader, const PixelShader* _pPixelShader)
  {
    UINT Strides = sizeof(Vertex3D);
    UINT Offsets = 0;

    auto System = detail::System::Get();
    auto FbxManager = System->GetFbxManager();

    System->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    System->RSSetState((isWireFrame) ? FbxManager->GetWireFrameState() : FbxManager->GetSolidState());
    System->IASetInputLayout(System->GetVertexShader()->GetInputLayout((_pVertexShader) ? _pVertexShader->ID_ : FbxManager->GetVertexShaderID()));
    System->VSSetShader(System->GetVertexShader()->GetVertexShader((_pVertexShader) ? _pVertexShader->ID_ : FbxManager->GetVertexShaderID()));
    System->PSSetShader(System->GetPixelShader()->GetPixeShader((_pPixelShader) ? _pPixelShader->ID_ : FbxManager->GetPixelShaderID()));
    System->OMSetDepthStencilState(FbxManager->GetDepthStencilState());
    System->PSSetSamplers(FbxManager->GetAddressOfSamplerState());

    //D3D11_BUFFER_DESC BufferDesc;
    //pIndexBuffer_->GetDesc(&BufferDesc);
    //detail::System::Get()->GetDeviceContext()->DrawIndexed(BufferDesc.ByteWidth / sizeof(UINT), 0, 0);
    //for (auto& Material : Materials)
    //{
    //  ConstantBuffer.MaterialColor = { _MaterialColor.R,_MaterialColor.G,_MaterialColor.B,_MaterialColor.A };
    //  ConstantBuffer.MaterialColor.x *= Material.Kd.x;
    //  ConstantBuffer.MaterialColor.y *= Material.Kd.y;
    //  ConstantBuffer.MaterialColor.z *= Material.Kd.z;
    //
    //  detail::System::Get()->GetDeviceContext()->UpdateSubresource(detail::System::Get()->GetFbxManager()->GetConstantBuffer(), 0, 0, &ConstantBuffer, 0, 0);
    //  detail::System::Get()->GetDeviceContext()->VSSetConstantBuffers(0, 1, detail::System::Get()->GetFbxManager()->GetAddressOfConstantBuffer());
    //
    //  detail::System::Get()->GetDeviceContext()->PSSetShaderResources(0, (Material.pShaderResourceView_ == nullptr) ? 0 : 1, Material.pShaderResourceView_.GetAddressOf());
    //

    ConstantBuffer ConstantBuffer;
    ConstantBuffer.LightDirection = _LightDirection;

    //static float angle = 0.0f;
    //DirectX::XMStoreFloat4x4(&ConstantBuffer.BoneTransforms[0], DirectX::XMMatrixIdentity());
    //DirectX::XMStoreFloat4x4(&ConstantBuffer.BoneTransforms[1], DirectX::XMMatrixRotationRollPitchYaw(0, 0, angle*0.01745f));
    //DirectX::XMStoreFloat4x4(&ConstantBuffer.BoneTransforms[2], DirectX::XMMatrixIdentity());
    //angle += 0.1f;

    for (auto& Mesh : Meshes_)
    {
      detail::System::Get()->IASetVertexBuffers(Mesh.pVertexBuffer.GetAddressOf(), Strides, Offsets);
      detail::System::Get()->GetDeviceContext()->IASetIndexBuffer(Mesh.pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

      const DirectX::XMMATRIX GlobalTransform = DirectX::XMLoadFloat4x4(&Mesh.GlobalTransform);

      DirectX::XMStoreFloat4x4(&ConstantBuffer.WorldViewProjection, GlobalTransform * DirectX::XMLoadFloat4x4(&CoordinateConversion) * DirectX::XMLoadFloat4x4(&_WorldViewProjection));
      DirectX::XMStoreFloat4x4(&ConstantBuffer.World, GlobalTransform * DirectX::XMLoadFloat4x4(&CoordinateConversion) * DirectX::XMLoadFloat4x4(&_World));

      //const std::vector<Bone>& Skeletal = Mesh.Skeletal;
      //for (int i = 0, Size = Mesh.Skeletal.size(); i < Size; ++i)
      //{
      //  DirectX::XMStoreFloat4x4(&ConstantBuffer.BoneTransforms[i], DirectX::XMLoadFloat4x4(&Skeletal.at(i).Transform));
      //}

      const int SkeletalAnimationNum = Mesh.SkeletalAnimation.size();

      if (SkeletalAnimationNum > 0)
      {
        int Frame = static_cast<int>(Mesh.SkeletalAnimation.AnimationTick / Mesh.SkeletalAnimation.SamplingTime);
        if (Frame > SkeletalAnimationNum - 1)
        {
          Frame = 0;
          Mesh.SkeletalAnimation.AnimationTick = 0.0f;
        }
        const Skeletal& Skeletal = Mesh.SkeletalAnimation.at(Frame);

        const int NumberOfBones = Skeletal.size();
        _ASSERT_EXPR(NumberOfBones < kMaxBoneInfluences, L"'the NumberOfBones' exceeds kMaxBoneInfluences");

        for (int i = 0; i < NumberOfBones; ++i)
        {
          DirectX::XMStoreFloat4x4(&ConstantBuffer.BoneTransforms[i], DirectX::XMLoadFloat4x4(&Skeletal.at(i).Transform));
        }
        Mesh.SkeletalAnimation.AnimationTick += _ElapsedTime;
      }

      for (auto& Subset : Mesh.Subsets)
      {
        ConstantBuffer.MaterialColor = { _MaterialColor.R*Subset.Diffuse.Color_.R,_MaterialColor.G*Subset.Diffuse.Color_.G,_MaterialColor.B*Subset.Diffuse.Color_.B,_MaterialColor.A*Subset.Diffuse.Color_.A };
        System->GetDeviceContext()->UpdateSubresource(FbxManager->GetConstantBuffer(), 0, 0, &ConstantBuffer, 0, 0);
        System->GetDeviceContext()->VSSetConstantBuffers(0, 1, FbxManager->GetAddressOfConstantBuffer());

        System->PSSetShaderResources(Subset.Diffuse.pShaderResourceView_.GetAddressOf());

        System->GetDeviceContext()->DrawIndexed(Subset.IndexCount, Subset.IndexStart, 0);
      }
    }
  }

  inline void SkinnedMesh::CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum, int Index)
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    D3D11_BUFFER_DESC VertexBufferDesc{};
    VertexBufferDesc.ByteWidth = sizeof(Vertex3D)*VerticesNum;
    VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA InitialData{};
    InitialData.pSysMem = Vertices;
    InitialData.SysMemPitch = 0;
    InitialData.SysMemSlicePitch = 0;

    hr = detail::System::Get()->GetDevice()->CreateBuffer(&VertexBufferDesc, &InitialData, Meshes_[Index].pVertexBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    D3D11_BUFFER_DESC IndexBufferDesc{};
    IndexBufferDesc.ByteWidth = sizeof(UINT)*IndicesNum;
    IndexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    InitialData.pSysMem = Indices;

    hr = detail::System::Get()->GetDevice()->CreateBuffer(&IndexBufferDesc, &InitialData, Meshes_[Index].pIndexBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");
  }

  inline void SkinnedMesh::FetchBoneInfluences(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<BoneInfluencePerControlPoint>* _pInfluences)
  {
    const int NumberOfControlPoints = _pFbxMesh->GetControlPointsCount();
    _pInfluences->resize(NumberOfControlPoints);

    const int NumberOfDeformers = _pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);

    for (int IndexOfDeformer = 0; IndexOfDeformer < NumberOfDeformers; ++IndexOfDeformer)
    {
      FbxSkin *pSkin = static_cast<FbxSkin*>(_pFbxMesh->GetDeformer(IndexOfDeformer, FbxDeformer::eSkin));
      const int NumberOfClusters = pSkin->GetClusterCount();

      for (int IndexOfClusters = 0; IndexOfClusters < NumberOfClusters; ++IndexOfClusters)
      {
        FbxCluster* pCluster = pSkin->GetCluster(IndexOfClusters);
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

  inline void SkinnedMesh::FetchBoneMatrices(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<Bone>& _Skeletal, const fbxsdk::FbxTime& _Time)
  {
    const int NumberOfDeformers = _pFbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);

    for (int IndexOfDeformer = 0; IndexOfDeformer < NumberOfDeformers; ++IndexOfDeformer)
    {
      fbxsdk::FbxSkin* pSkin = static_cast<FbxSkin*>(_pFbxMesh->GetDeformer(IndexOfDeformer, fbxsdk::FbxDeformer::eSkin));

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
        const fbxsdk::FbxAMatrix Transform = ReferenceGlobalCurrentPosition.Inverse() * ClusterGlobalCurrentPosition *
          ClusterGlobalInitPosition.Inverse() * ReferenceGlobalInitPosition;

        for (int Row = 0; Row < 4; ++Row)
        {
          for (int Column = 0; Column < 4; ++Column)
          {
            Bone.Transform.m[Row][Column] = static_cast<float>(Transform.Get(Row, Column));
          }
        }
      }
    }
  }

  inline void SkinnedMesh::FetchAnimations(const fbxsdk::FbxMesh* _pFbxMesh, SkeletalAnimation& SkeletalAnimation, UINT _SamplingRate)
  {
    // Get the list of all the animation stack.
    fbxsdk::FbxArray<FbxString*> ArrayOfAnimationStackNames;
    _pFbxMesh->GetScene()->FillAnimStackNameArray(ArrayOfAnimationStackNames);

    // Get the number of animations.
    const int NumberOfAnimations = ArrayOfAnimationStackNames.Size();

    if (NumberOfAnimations > 0)
    {
      // Get the FbxTime per animation's frame.
      const fbxsdk::FbxTime::EMode TimeMode = _pFbxMesh->GetScene()->GetGlobalSettings().GetTimeMode();
      fbxsdk::FbxTime FrameTime;
      FrameTime.SetTime(0, 0, 0, 1, 0, TimeMode);

      _SamplingRate = (_SamplingRate > 0) ? _SamplingRate : static_cast<UINT>(FrameTime.GetFrameRate(TimeMode));

      float SamplingTime = 1.0f / _SamplingRate;
      SkeletalAnimation.SamplingTime = SamplingTime;
      SkeletalAnimation.AnimationTick = 0.0f;

      fbxsdk::FbxString* AnimationStackName = ArrayOfAnimationStackNames.GetAt(0);
      fbxsdk::FbxAnimStack* CurrentAnimationStack = _pFbxMesh->GetScene()->FindMember<fbxsdk::FbxAnimStack>(AnimationStackName->Buffer());
      _pFbxMesh->GetScene()->SetCurrentAnimationStack(CurrentAnimationStack);

      const fbxsdk::FbxTakeInfo* TakeInfo = _pFbxMesh->GetScene()->GetTakeInfo(AnimationStackName->Buffer());
      const fbxsdk::FbxTime StartTime = TakeInfo->mLocalTimeSpan.GetStart();
      const fbxsdk::FbxTime EndTime = TakeInfo->mLocalTimeSpan.GetStop();

      fbxsdk::FbxTime SamplingStep;
      SamplingStep.SetTime(0, 0, 1, 0, 0, TimeMode);
      SamplingStep = static_cast<fbxsdk::FbxLongLong>(SamplingStep.Get() * SamplingTime);

      for (fbxsdk::FbxTime CurrentTime = StartTime; CurrentTime < EndTime; CurrentTime += SamplingStep)
      {
        Skeletal Skeletal;
        FetchBoneMatrices(_pFbxMesh, Skeletal, CurrentTime);
        SkeletalAnimation.push_back(Skeletal);
      }
    }
    for (int i = 0; i < NumberOfAnimations; ++i)
    {
      delete ArrayOfAnimationStackNames[i];
    }
  }
}
