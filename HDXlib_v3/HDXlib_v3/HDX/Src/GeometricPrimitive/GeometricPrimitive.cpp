#include "../../Include/GeometricPrimitive.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../VertexShader/IVertexShader.hpp"
#include "../PixelShader/IPixelShader.hpp"

#include "../../Include/ConstantBuffer.hpp"
#include "../../Include/MathConstants.hpp"
#include "../../Include/VertexShader.hpp"
#include "../../Include/PixelShader.hpp"
#include "../../Include/Constants.hpp"

#include <WICTextureLoader.h>

#include <memory>

namespace hdx
{
  GeometricPrimitive::GeometricPrimitive(const char* _FilePath)
  {
    ////detail::System* pSystem = pSystem->pSystem_;
    ////
    //////  エラーチェック用
    ////HRESULT hr = S_OK;
    ////
    ////D3D11_INPUT_ELEMENT_DESC InputElementDescs[] =
    ////{
    ////  { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    ////  { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    ////};
    ////
    ////pSystem->CreateVS("geometric_primitive_vs.cso", InputElementDescs, ARRAYSIZE(InputElementDescs), pVertexShader_.GetAddressOf(), pInputLayout_.GetAddressOf());
    ////pSystem->CreatePS("geometric_primitive_ps.cso", pPixelShader_.GetAddressOf());
    ////
    ////DXGI_SWAP_CHAIN_DESC SwapDesc;
    ////pSystem->GetSwapChain()->GetDesc(&SwapDesc);
    ////
    ////D3D11_RASTERIZER_DESC RasterizerDesc{};
    ////RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    ////RasterizerDesc.CullMode = D3D11_CULL_BACK;
    ////RasterizerDesc.FrontCounterClockwise = false;
    ////RasterizerDesc.DepthBias = 0;
    ////RasterizerDesc.DepthBiasClamp = 0;
    ////RasterizerDesc.SlopeScaledDepthBias = 0;
    ////RasterizerDesc.DepthClipEnable = true;
    ////RasterizerDesc.ScissorEnable = false;
    ////RasterizerDesc.MultisampleEnable = (SwapDesc.SampleDesc.Count != 1) ? true : false; //  スワップチェーンのマルチサンプリング設定に合わせる
    ////RasterizerDesc.AntialiasedLineEnable = false;
    ////hr = pSystem->GetDevice()->CreateRasterizerState(&RasterizerDesc, pSolidState_.GetAddressOf());
    ////_ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");
    ////
    ////RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    ////RasterizerDesc.CullMode = D3D11_CULL_NONE;
    ////hr = pSystem->GetDevice()->CreateRasterizerState(&RasterizerDesc, pWireFrameState_.GetAddressOf());
    ////_ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");
    ////
    ////D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    ////DepthStencilDesc.DepthEnable = true;
    ////DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    ////DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    ////DepthStencilDesc.StencilEnable = false;
    ////DepthStencilDesc.StencilReadMask = 0xFF;
    ////DepthStencilDesc.StencilWriteMask = 0xFF;
    ////DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    ////DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    ////DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    ////DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    ////DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    ////DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    ////DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    ////DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    ////hr = pSystem->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState_.GetAddressOf());
    ////_ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilState");
    ////
    ////D3D11_BUFFER_DESC ConstantBufferDesc{};
    ////ConstantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
    ////ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ////ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ////ConstantBufferDesc.CPUAccessFlags = 0;
    ////ConstantBufferDesc.MiscFlags = 0;
    ////ConstantBufferDesc.StructureByteStride = 0;
    ////
    ////hr = pSystem->GetDevice()->CreateBuffer(&ConstantBufferDesc, nullptr, pConstantBuffer_.GetAddressOf());
    ////_ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    //if (_FilePath == "")
    //{
    //  detail::System::Get()->MakeDummyTexture(pShaderResourceView_.GetAddressOf());
    //}
    //else
    //{
    //  wchar_t FilePath[MaxCharLimit]{};
    //  mbstowcs_s(nullptr, FilePath, _FilePath, MaxCharLimit);

    //  HRESULT hr = DirectX::CreateWICTextureFromFile(detail::System::Get()->GetDevice(), FilePath, nullptr, pShaderResourceView_.GetAddressOf());
    //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateWICTextureFromFile");
    //}
  }

  GeometricPrimitive::~GeometricPrimitive()
  {

  }

  //void GeometricPrimitive::Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, const ColorF& _MaterialColor, bool isWireFrame, const VertexShader* _pVertexShader, const PixelShader* _pPixelShader)const
  //{
  //  ConstantBuffer ConstantBuffer;
  //  ConstantBuffer.World = _World;
  //  ConstantBuffer.WorldViewProjection = _WorldViewProjection;
  //  ConstantBuffer.LightDirection = _LightDirection;
  //  ConstantBuffer.MaterialColor = { _MaterialColor.R,_MaterialColor.G,_MaterialColor.B,_MaterialColor.A };
  //
  //  UINT Strides = sizeof(Vertex3D);
  //  UINT Offsets = 0;
  //
  //  detail::System::Get()->IASetVertexBuffers(pVertexBuffer_.GetAddressOf(), Strides, Offsets);
  //  detail::System::Get()->GetDeviceContext()->IASetIndexBuffer(pIndexBuffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
  //
  //  detail::System::Get()->GetDeviceContext()->UpdateSubresource(detail::System::Get()->GetPrimitiveManager()->GetConstantBuffer(), 0, nullptr, &ConstantBuffer, 0, 0);
  //  detail::System::Get()->GetDeviceContext()->VSSetConstantBuffers(0, 1, detail::System::Get()->GetPrimitiveManager()->GetAddressOfConstantBuffer());
  //
  //  detail::System::Get()->PSSetSamplers(detail::System::Get()->GetPrimitiveManager()->GetAddressOfSamplerState());
  //
  //  detail::System::Get()->RSSetState((isWireFrame) ? detail::System::Get()->GetPrimitiveManager()->GetWireFrameState() : detail::System::Get()->GetPrimitiveManager()->GetSolidState());
  //  detail::System::Get()->IASetInputLayout(detail::System::Get()->GetVertexShader()->GetInputLayout((_pVertexShader) ? _pVertexShader->ID_ : detail::System::Get()->GetPrimitiveManager()->GetVertexShaderID()));
  //  detail::System::Get()->VSSetShader(detail::System::Get()->GetVertexShader()->GetVertexShader((_pVertexShader) ? _pVertexShader->ID_ : detail::System::Get()->GetPrimitiveManager()->GetVertexShaderID()));
  //  detail::System::Get()->PSSetShader(detail::System::Get()->GetPixelShader()->GetPixeShader((_pPixelShader) ? _pPixelShader->ID_ : detail::System::Get()->GetPrimitiveManager()->GetPixelShaderID()));
  //  detail::System::Get()->OMSetDepthStencilState(detail::System::Get()->GetPrimitiveManager()->GetDepthStencilState());
  //  detail::System::Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  //
  //  D3D11_BUFFER_DESC BufferDesc;
  //  pIndexBuffer_->GetDesc(&BufferDesc);
  //  detail::System::Get()->GetDeviceContext()->DrawIndexed(BufferDesc.ByteWidth / sizeof(UINT), 0, 0);
  //}

  //void GeometricPrimitive::Render(const ConstantBuffer& _ConstantBuffer, bool isWireFrame, const VertexShader* _pVertexShader, const PixelShader* _pPixelShader)const
  //{
  //  //UINT Strides = sizeof(Vertex3D);
  //  //UINT Offsets = 0;

  //  //auto PrimitiveManager = detail::System::Get()->GetPrimitiveManager();

  //  ////detail::System::Get()->IASetVertexBuffers(pVertexBuffer_.GetAddressOf(), Strides, Offsets);
  //  ////detail::System::Get()->GetDeviceContext()->IASetIndexBuffer(pIndexBuffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
  //  ////
  //  ////detail::System::Get()->GetDeviceContext()->UpdateSubresource(PrimitiveManager->GetConstantBuffer(), 0, nullptr, &_ConstantBuffer, 0, 0);
  //  ////detail::System::Get()->GetDeviceContext()->VSSetConstantBuffers(0, 1, PrimitiveManager->GetAddressOfConstantBuffer());
  //  ////
  //  ////detail::System::Get()->PSSetSamplers(PrimitiveManager->GetAddressOfSamplerState());
  //  ////
  //  ////detail::System::Get()->RSSetState((isWireFrame) ? PrimitiveManager->GetWireFrameState() : PrimitiveManager->GetSolidState());
  //  ////detail::System::Get()->IASetInputLayout(detail::System::Get()->GetVertexShader()->GetInputLayout((_pVertexShader) ? _pVertexShader->GetID() : PrimitiveManager->GetVertexShaderID()));
  //  ////detail::System::Get()->VSSetShader(detail::System::Get()->GetVertexShader()->GetVertexShader((_pVertexShader) ? _pVertexShader->GetID() : PrimitiveManager->GetVertexShaderID()));
  //  ////detail::System::Get()->PSSetShader(detail::System::Get()->GetPixelShader()->GetPixeShader((_pPixelShader) ? _pPixelShader->GetID() : PrimitiveManager->GetPixelShaderID()));
  //  ////detail::System::Get()->OMSetDepthStencilState(PrimitiveManager->GetDepthStencilState());
  //  ////detail::System::Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  //  ////
  //  ////D3D11_BUFFER_DESC BufferDesc;
  //  ////pIndexBuffer_->GetDesc(&BufferDesc);
  //  ////detail::System::Get()->GetDeviceContext()->DrawIndexed(BufferDesc.ByteWidth / sizeof(UINT), 0, 0);
  //}

  inline void GeometricPrimitive::CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum)
  {
    //ID3D11Device* pDevice = detail::System::Get()->GetDevice();

    ////  エラーチェック用
    //HRESULT hr = S_OK;

    //D3D11_BUFFER_DESC VertexBufferDesc{};
    //VertexBufferDesc.ByteWidth = sizeof(Vertex3D)*VerticesNum;
    //VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    //VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    //VertexBufferDesc.CPUAccessFlags = 0;
    //VertexBufferDesc.MiscFlags = 0;
    //VertexBufferDesc.StructureByteStride = 0;

    //D3D11_SUBRESOURCE_DATA InitialData{};
    //InitialData.pSysMem = Vertices;
    //InitialData.SysMemPitch = 0;
    //InitialData.SysMemSlicePitch = 0;

    //hr = pDevice->CreateBuffer(&VertexBufferDesc, &InitialData, pVertexBuffer_.GetAddressOf());
    //_ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    //D3D11_BUFFER_DESC IndexBufferDesc{};
    //IndexBufferDesc.ByteWidth = sizeof(UINT)*IndicesNum;
    //IndexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    //IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    //IndexBufferDesc.CPUAccessFlags = 0;
    //IndexBufferDesc.MiscFlags = 0;
    //IndexBufferDesc.StructureByteStride = 0;

    //InitialData.pSysMem = Indices;

    //hr = pDevice->CreateBuffer(&IndexBufferDesc, &InitialData, pIndexBuffer_.GetAddressOf());
    //_ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");
  }

  Rectangle::Rectangle(const char* _FilePath)
    : GeometricPrimitive(_FilePath)
  {
    //  頂点情報設定
    Vertex3D Vertices[4];
    {
      Vertices[0].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[1].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[2].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[3].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[0].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[1].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[2].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[3].Normal = { +0.0f, +0.0f, -1.0f };
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

    CreateBuffers(Vertices, 4, Indices, 6);
  }

  Cube::Cube(const char* _FilePath)
    : GeometricPrimitive(_FilePath)
  {
    //  頂点情報設定
    Vertex3D Vertices[24];
    {
      //  手前
      Vertices[0].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[1].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[2].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[3].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[0].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[1].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[2].Normal = { +0.0f, +0.0f, -1.0f };
      Vertices[3].Normal = { +0.0f, +0.0f, -1.0f };

      //	右
      Vertices[4].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[5].Position = { +0.5f, +0.5f, +0.5f };
      Vertices[6].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[7].Position = { +0.5f, -0.5f, +0.5f };
      Vertices[4].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[5].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[6].Normal = { +1.0f, +0.0f, +0.0f };
      Vertices[7].Normal = { +1.0f, +0.0f, +0.0f };

      //	上
      Vertices[8].Position = { -0.5f, +0.5f, +0.5f };
      Vertices[9].Position = { +0.5f, +0.5f, +0.5f };
      Vertices[10].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[11].Position = { +0.5f, +0.5f, -0.5f };
      Vertices[8].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[9].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[10].Normal = { +0.0f, +1.0f, +0.0f };
      Vertices[11].Normal = { +0.0f, +1.0f, +0.0f };

      //	左
      Vertices[12].Position = { -0.5f, +0.5f, +0.5f };
      Vertices[13].Position = { -0.5f, +0.5f, -0.5f };
      Vertices[14].Position = { -0.5f, -0.5f, +0.5f };
      Vertices[15].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[12].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[13].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[14].Normal = { -1.0f, +0.0f, +0.0f };
      Vertices[15].Normal = { -1.0f, +0.0f, +0.0f };

      //	下
      Vertices[16].Position = { -0.5f, -0.5f, -0.5f };
      Vertices[17].Position = { +0.5f, -0.5f, -0.5f };
      Vertices[18].Position = { -0.5f, -0.5f, +0.5f };
      Vertices[19].Position = { +0.5f, -0.5f, +0.5f };
      Vertices[16].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[17].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[18].Normal = { +0.0f, -1.0f, +0.0f };
      Vertices[19].Normal = { +0.0f, -1.0f, +0.0f };

      //	奥
      Vertices[20].Position = { +0.5f, +0.5f, +0.5f };
      Vertices[21].Position = { -0.5f, +0.5f, +0.5f };
      Vertices[22].Position = { +0.5f, -0.5f, +0.5f };
      Vertices[23].Position = { -0.5f, -0.5f, +0.5f };
      Vertices[20].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[21].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[22].Normal = { +0.0f, +0.0f, +1.0f };
      Vertices[23].Normal = { +0.0f, +0.0f, +1.0f };
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

    CreateBuffers(Vertices, 24, Indices, 36);
  }

  Cylinder::Cylinder(UINT Slices, const char* _FilePath)
    : GeometricPrimitive(_FilePath)
  {
    std::unique_ptr<Vertex3D[]> Vertices(new Vertex3D[(Slices + 1) * 2]);
    std::unique_ptr<u_int[]>  Indices(new u_int[Slices * 6 + Slices * 6]);

    //  1つの三角形の角度
    const float Degree = 360.0f / Slices;

    //  頂点情報設定
    {
      //  上底の真ん中設定
      Vertices[0].Position = { 0.0f, +0.5f, 0.0f };
      //  上底の周り設定
      for (UINT i = 0; i < Slices; ++i)
      {
        Vertices[i + 1].Position = { 0.5f*cosf(Math::ToRadian(Degree*i)), +0.5f, 0.5f*sinf(Math::ToRadian(Degree*i)) };
      }
      //  下底の設定
      for (UINT i = 0; i <= Slices; ++i)
      {
        Vertices[(Slices + 1) + i] = Vertices[i];
        Vertices[(Slices + 1) + i].Position.Y = -Vertices[i].Position.Y;
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

    //  作成
    CreateBuffers(Vertices.get(), (Slices + 1) * 2, Indices.get(), Slices * 6 + Slices * 6);
  }
}
