#include <HDX/Model.hpp>
#include <HDX/System/System.hpp>
#include <HDX/ConstantBuffer.hpp>
#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
#include <HDX/Constants.hpp>

#include <WICTextureLoader.h>

#include <fstream>
#include <deque>

namespace hdx
{
  Model::Model(const char* FilePath, bool VCoordingFlip)
  {
    wchar_t wFilePath[MaxCharLimit];
    mbstowcs_s(nullptr, wFilePath, FilePath, MaxCharLimit);

    std::vector<Vertex3D> Vertices;
    std::vector<UINT> Indices;

    Load(wFilePath, &Vertices, &Indices, VCoordingFlip);

    CreateBuffers(Vertices.data(), Vertices.size(), Indices.data(), Vertices.size());

    //  サイズを計算
    {
      hdx::float3 MinPosition, MaxPosition;

      MinPosition = MaxPosition = Vertices[0].Position;

      //  値が小さい方を返す
      auto Min = [](float _Pos1, float _Pos2)->float
      {
        return (_Pos2 < _Pos1) ? _Pos1 : _Pos2;
      };
      //  値が大きさ方を返す
      auto Max = [](float _Pos1, float _Pos2)->float
      {
        return (_Pos2 > _Pos1) ? _Pos1 : _Pos2;
      };

      for (int i = 1, Size = Vertices.size(); i < Size; ++i)
      {
        hdx::float3& Position = Vertices[i].Position;

        MinPosition.X = Min(MinPosition.X, Position.X);
        MinPosition.Y = Min(MinPosition.Y, Position.Y);
        MinPosition.Z = Min(MinPosition.Z, Position.Z);

        MaxPosition.X = Max(MaxPosition.X, Position.X);
        MaxPosition.Y = Max(MaxPosition.Y, Position.Y);
        MaxPosition.Z = Max(MaxPosition.Z, Position.Z);
      }

      Scale_ = MaxPosition - MinPosition;
    }
  }

  Model::~Model()
  {

  }

  inline void Model::Load(const wchar_t* FilePath, std::vector<Vertex3D>* Vertices, std::vector<UINT>* Indices, bool VCoordingFlip)
  {
    UINT CurrentIndex = 0;
    UINT CurrentSubSetIndex = -1;

    std::vector<float3> Positions;
    std::vector<float3> Normals;
    std::vector<float2> TexCoords;

    std::wifstream fin(FilePath);

    _ASSERT_EXPR(fin, L"OBJ File not Found.");

    std::deque<std::wstring> MtlFileNames;

    while (fin)
    {
      wchar_t command[MaxCharLimit];
      fin >> command;

      if (wcscmp(command, L"mtllib") == 0)
      {
        wchar_t mtl[MaxCharLimit];

        fin >> mtl;
        MtlFileNames.push_back(mtl);
      }
      else if (wcscmp(command, L"v") == 0)
      {
        float x, y, z;
        fin >> x >> y >> z;
        Positions.push_back({ x, y, z });
      }
      else if (wcscmp(command, L"vt") == 0)
      {
        float u, v;
        fin >> u >> v;
        TexCoords.push_back({ u, (VCoordingFlip) ? 1.0f - v : v });
      }
      else if (wcscmp(command, L"vn") == 0)
      {
        float i, j, k;
        fin >> i >> j >> k;
        Normals.push_back({ i, j, k });
      }
      else if (wcscmp(command, L"usemtl") == 0)
      {
        wchar_t usemtl[MaxCharLimit]{};

        fin >> usemtl;
        Subset Subset;
        Subset.UseMtl = usemtl;
        Subset.IndexStart = CurrentIndex;
        ++CurrentSubSetIndex;
        Subsets.push_back(Subset);
      }
      else if (wcscmp(command, L"f") == 0)
      {
        for (UINT i = 0; i < 3; ++i)
        {
          ++Subsets[CurrentSubSetIndex].IndexCount;

          Vertex3D Vertex;

          u_int v, vt, vn;
          fin >> v;
          Vertex.Position = Positions[v - 1];
          if (L'/' == fin.peek())
          {
            fin.ignore();
            if (L'/' != fin.peek())
            {
              fin >> vt;
              Vertex.Texcoord = TexCoords[vt - 1];
            }
            if (L'/' == fin.peek())
            {
              fin.ignore();
              fin >> vn;
              Vertex.Normal = Normals[vn - 1];
            }
          }
          (*Vertices).push_back(Vertex);
          (*Indices).push_back(CurrentIndex++);
        }
      }

      fin.ignore(1024, L'\n');
    }

    fin.close();

    //  区切り文字
    static constexpr wchar_t kDelimiters[] = { L'\\', L'/' };
    //  objファイルが存在するフォルダ
    wchar_t Directory[MaxCharLimit]{};

    for (wchar_t Delimiter : kDelimiters)
    {
      //  後ろから区切り文字を判別
      const wchar_t* p = wcsrchr(const_cast<wchar_t*>(FilePath), Delimiter);

      //  区切り文字があれば
      if (p)
      {
        //  区切り文字までをフォルダ名として格納
        wcsncpy_s(Directory, FilePath, (p + 1) - FilePath);
      }
    }

    //  Mtlファイルの数ループ
    while (!MtlFileNames.empty())
    {
      int CurrentMaterialIndex = -1;

      //  Mtlファイルのファイルパスを作成
      wchar_t MtlFilePath[MaxCharLimit]{};
      wcscpy_s(MtlFilePath, Directory);
      wcscat_s(MtlFilePath, MtlFileNames.front().c_str());

      //  Mtlファイル読み込み
      std::wifstream fin(MtlFilePath);
      MtlFileNames.pop_front();

      Material Material;

      while (fin)
      {
        wchar_t command[MaxCharLimit];
        fin >> command;

        if (wcscmp(command, L"newmtl") == 0)
        {
          wchar_t NewMtl[MaxCharLimit];
          fin >> NewMtl;

          Material.NewMtl = NewMtl;

          Materials.push_back(Material);
          ++CurrentMaterialIndex;
        }
        else if (wcscmp(command, L"Ka") == 0)
        {
          float x, y, z;
          fin >> x >> y >> z;

          Materials[CurrentMaterialIndex].Ka = DirectX::XMFLOAT3(x, y, z);
        }
        else if (wcscmp(command, L"Kd") == 0)
        {
          float x, y, z;
          fin >> x >> y >> z;

          Materials[CurrentMaterialIndex].Kd = DirectX::XMFLOAT3(x, y, z);
        }
        else if (wcscmp(command, L"Ks") == 0)
        {
          float x, y, z;
          fin >> x >> y >> z;

          Materials[CurrentMaterialIndex].Ks = DirectX::XMFLOAT3(x, y, z);
        }
        else if (wcscmp(command, L"illum") == 0)
        {
          UINT illum;
          fin >> illum;

          Materials[CurrentMaterialIndex].illum = illum;
        }
        else if (wcscmp(command, L"map_Kd") == 0)
        {
          wchar_t TextureFileName[MaxCharLimit]{};
          fin >> TextureFileName;

          //  テクスチャのファイルパスを作成
          wchar_t TextureFilePath[MaxCharLimit]{};
          wcscpy_s(TextureFilePath, Directory);
          wcscat_s(TextureFilePath, TextureFileName);

          Materials[CurrentMaterialIndex].map_Kd = TextureFileName;

          HRESULT hr = DirectX::CreateWICTextureFromFile(detail::System::Get()->GetDevice(), TextureFilePath, nullptr, Materials[CurrentMaterialIndex].pShaderResourceView_.GetAddressOf());
          _ASSERT_EXPR(SUCCEEDED(hr), L"CreateWICTextureFromFile");
        }
      }

      for (auto& Material : Materials)
      {
        if (!Material.pShaderResourceView_)
        {
          detail::System::Get()->MakeDummyTexture(Material.pShaderResourceView_.GetAddressOf());
        }
      }
    }
  }

  inline void Model::CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum)
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

    hr = detail::System::Get()->GetDevice()->CreateBuffer(&VertexBufferDesc, &InitialData, pVertexBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    D3D11_BUFFER_DESC IndexBufferDesc{};
    IndexBufferDesc.ByteWidth = sizeof(UINT)*IndicesNum;
    IndexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    InitialData.pSysMem = Indices;

    hr = detail::System::Get()->GetDevice()->CreateBuffer(&IndexBufferDesc, &InitialData, pIndexBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");
  }

  //void Model::Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, const ColorF& _MaterialColor,
  //  bool isWireFrame, const VertexShader* _pVertexShader, const PixelShader* _pPixelShader)const
  //{
  //  UINT Strides = sizeof(Vertex3D);
  //  UINT Offsets = 0;
  //
  //  detail::System::Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  //  detail::System::Get()->IASetVertexBuffers(pVertexBuffer_.GetAddressOf(), Strides, Offsets);
  //  detail::System::Get()->IASetInputLayout(detail::System::Get()->GetVertexShader()->GetInputLayout((_pVertexShader) ? _pVertexShader->ID_ : detail::System::Get()->GetMeshManager()->GetVertexShaderID()));
  //  detail::System::Get()->VSSetShader(detail::System::Get()->GetVertexShader()->GetVertexShader((_pVertexShader) ? _pVertexShader->ID_ : detail::System::Get()->GetMeshManager()->GetVertexShaderID()));
  //  detail::System::Get()->PSSetShader(detail::System::Get()->GetPixelShader()->GetPixeShader((_pPixelShader) ? _pPixelShader->ID_ : detail::System::Get()->GetMeshManager()->GetPixelShaderID()));
  //  detail::System::Get()->GetDeviceContext()->IASetIndexBuffer(pIndexBuffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
  //  detail::System::Get()->RSSetState((isWireFrame) ? detail::System::Get()->GetMeshManager()->GetWireFrameState() : detail::System::Get()->GetMeshManager()->GetSolidState());
  //  detail::System::Get()->OMSetDepthStencilState(detail::System::Get()->GetMeshManager()->GetDepthStencilState());
  //  detail::System::Get()->PSSetSamplers(detail::System::Get()->GetMeshManager()->GetAddressOfSamplerState());
  //
  //  hdx::ConstantBuffer ConstantBuffer;
  //  ConstantBuffer.World = _World;
  //  ConstantBuffer.WorldViewProjection = _WorldViewProjection;
  //  ConstantBuffer.LightDirection = _LightDirection;
  //
  //  for (auto& Material : Materials)
  //  {
  //    ConstantBuffer.MaterialColor = { _MaterialColor.R*Material.Kd.x,_MaterialColor.G*Material.Kd.y,_MaterialColor.B*Material.Kd.z,_MaterialColor.A };
  //
  //    detail::System::Get()->GetDeviceContext()->UpdateSubresource(detail::System::Get()->GetMeshManager()->GetConstantBuffer(), 0, 0, &ConstantBuffer, 0, 0);
  //    detail::System::Get()->GetDeviceContext()->VSSetConstantBuffers(0, 1, detail::System::Get()->GetMeshManager()->GetAddressOfConstantBuffer());
  //    detail::System::Get()->GetDeviceContext()->PSSetShaderResources(0, 1, Material.pShaderResourceView_.GetAddressOf());
  //
  //    for (auto& Subset : Subsets)
  //    {
  //      if (Material.NewMtl == Subset.UseMtl)
  //      {
  //        detail::System::Get()->GetDeviceContext()->DrawIndexed(Subset.IndexCount, Subset.IndexStart, 0);
  //      }
  //    }
  //  }
  //}

  void Model::Render(const ConstantBuffer& _ConstantBuffer, bool isWireFrame, const VertexShader* _pVertexShader, const PixelShader* _pPixelShader)const
  {
    UINT Strides = sizeof(Vertex3D);
    UINT Offsets = 0;

    auto MeshManager = detail::System::Get()->GetMeshManager();

    //detail::System::Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //detail::System::Get()->IASetVertexBuffers(pVertexBuffer_.GetAddressOf(), Strides, Offsets);
    //detail::System::Get()->IASetInputLayout(detail::System::Get()->GetVertexShader()->GetInputLayout((_pVertexShader) ? _pVertexShader->GetID() : MeshManager->GetVertexShaderID()));
    //detail::System::Get()->VSSetShader(detail::System::Get()->GetVertexShader()->GetVertexShader((_pVertexShader) ? _pVertexShader->GetID() : MeshManager->GetVertexShaderID()));
    //detail::System::Get()->PSSetShader(detail::System::Get()->GetPixelShader()->GetPixeShader((_pPixelShader) ? _pPixelShader->GetID() : MeshManager->GetPixelShaderID()));
    //detail::System::Get()->GetDeviceContext()->IASetIndexBuffer(pIndexBuffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
    //detail::System::Get()->RSSetState((isWireFrame) ? MeshManager->GetWireFrameState() : MeshManager->GetSolidState());
    //detail::System::Get()->OMSetDepthStencilState(MeshManager->GetDepthStencilState());
    //detail::System::Get()->PSSetSamplers(MeshManager->GetAddressOfSamplerState());

    for (auto& Material : Materials)
    {
      //ConstantBuffer ConstantBuffer = _ConstantBuffer;
      //ConstantBuffer.MaterialColor.R *= Material.Kd.x;
      //ConstantBuffer.MaterialColor.G *= Material.Kd.y;
      //ConstantBuffer.MaterialColor.B *= Material.Kd.z;
      //
      //detail::System::Get()->GetDeviceContext()->UpdateSubresource(detail::System::Get()->GetMeshManager()->GetConstantBuffer(), 0, 0, &ConstantBuffer, 0, 0);
      //detail::System::Get()->GetDeviceContext()->VSSetConstantBuffers(0, 1, detail::System::Get()->GetMeshManager()->GetAddressOfConstantBuffer());
      //detail::System::Get()->GetDeviceContext()->PSSetShaderResources(0, 1, Material.pShaderResourceView_.GetAddressOf());

      for (auto& Subset : Subsets)
      {
        if (Material.NewMtl == Subset.UseMtl)
        {
          //detail::System::Get()->GetDeviceContext()->DrawIndexed(Subset.IndexCount, Subset.IndexStart, 0);
        }
      }
    }
  }
}
