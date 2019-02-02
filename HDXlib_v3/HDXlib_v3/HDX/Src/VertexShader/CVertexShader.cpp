#include "CVertexShader.hpp"

#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include "Include/Macro.hpp"

#include <assert.h>

void CVertexShader::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

int CVertexShader::Create(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = VertexShaderMap_.find(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  return CreateVertexShader(_FilePath, nullptr, nullptr);
}

hdx::VertexShader CVertexShader::CreateDefault2D(ID3D11InputLayout** _ppInputLayout)
{
  D3D11_INPUT_ELEMENT_DESC InputElementDescs[] =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

    { "NDC_TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "NDC_TRANSFORM", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "NDC_TRANSFORM", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "NDC_TRANSFORM", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "TEXCOORD_TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
  };

  CreateInputLayout(kDefault2DVertexShaderFilePath, InputElementDescs, hdx::Macro::ArraySize(InputElementDescs), _ppInputLayout);

  return hdx::VertexShader(kDefault2DVertexShaderFilePath);
}

hdx::VertexShader CVertexShader::CreateDefault3D(ID3D11InputLayout** _ppInputLayout)
{
  D3D11_INPUT_ELEMENT_DESC InputElementDescs[] =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "BONES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

    { "WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
  };

  CreateInputLayout(kDefault3DVertexShaderFilePath, InputElementDescs, hdx::Macro::ArraySize(InputElementDescs), _ppInputLayout);

  return hdx::VertexShader(kDefault3DVertexShaderFilePath);
}

ID3D11VertexShader* CVertexShader::GetVertexShader(const hdx::VertexShader& _VertexShader)
{
  return VertexShaderMap_[_VertexShader.GetID()].Get();
}

int CVertexShader::CreateVertexShader(const char* _FilePath, std::unique_ptr<unsigned char[]>* _pData, size_t* _pSize)
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  FILE* fp;
  fopen_s(&fp, _FilePath, "rb");
  assert(fp);

  fseek(fp, 0, SEEK_END);
  long Size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::unique_ptr<unsigned char[]> Data = std::make_unique<unsigned char[]>(Size);
  fread(Data.get(), Size, 1, fp);
  fclose(fp);

  Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
  //  頂点シェーダーの作成
  hr = pDevice_->CreateVertexShader(Data.get(), Size, nullptr, pVertexShader.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  if (_pData && _pSize)
  {
    (*_pData) = std::move(Data);
    (*_pSize) = Size;
  }

  return VertexShaderMap_.insert(_FilePath, pVertexShader);
}

void CVertexShader::CreateInputLayout(const char* _FilePath, const D3D11_INPUT_ELEMENT_DESC _InputElementDescs[], UINT _NumElements, ID3D11InputLayout** _ppInputLayout)
{
  std::unique_ptr<unsigned char[]> Data;
  size_t Size;

  CreateVertexShader(_FilePath, &Data, &Size);

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = pDevice_->CreateInputLayout(_InputElementDescs, _NumElements, Data.get(), Size, _ppInputLayout);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
}
