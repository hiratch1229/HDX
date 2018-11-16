#include "IVertexShader.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../NumberMap.hpp"
#include "../Misc.hpp"

#include "../../Include/InputElementDesc.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <assert.h>
#include <memory>

namespace
{
  struct State
  {
    Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
  };

  NumberMap<std::string, State> StateMap;
}

hdx::VertexShader IVertexShader::CreateDefault2D()
{
  hdx::InputElementDesc InputElementDescs[] =
  {
    hdx::InputElementDesc::Position,
    hdx::InputElementDesc::Texcoord,
    { "NDC_TRANSFORM", 0, hdx::Format::R32G32B32A32_FLOAT, 1, hdx::AppendAlignedElement, hdx::InputClassification::PER_INSTANCE_DATA, 1 },
    { "NDC_TRANSFORM", 1, hdx::Format::R32G32B32A32_FLOAT, 1, hdx::AppendAlignedElement, hdx::InputClassification::PER_INSTANCE_DATA, 1 },
    { "NDC_TRANSFORM", 2, hdx::Format::R32G32B32A32_FLOAT, 1, hdx::AppendAlignedElement, hdx::InputClassification::PER_INSTANCE_DATA, 1 },
    { "NDC_TRANSFORM", 3, hdx::Format::R32G32B32A32_FLOAT, 1, hdx::AppendAlignedElement, hdx::InputClassification::PER_INSTANCE_DATA, 1 },
    { "TEXCOORD_TRANSFORM", 0, hdx::Format::R32G32B32A32_FLOAT, 1, hdx::AppendAlignedElement, hdx::InputClassification::PER_INSTANCE_DATA, 1 },
    { "COLOR", 0, hdx::Format::R32G32B32A32_FLOAT, 1, hdx::AppendAlignedElement, hdx::InputClassification::PER_INSTANCE_DATA, 1 },
  };

  return hdx::VertexShader(kDefault2DFilePath, InputElementDescs, ARRAYSIZE(InputElementDescs));
}

//  バーテックスシェーダー作成
int IVertexShader::Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], UINT _NumElements)
{
  int ID = StateMap.find(_FilePath);

  //  存在しなかった場合
  if (ID < 0)
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

    ISystem* pSystem = Engine::GetSystem();

    State State;
    {
      //  頂点シェーダーの作成
      hr = pSystem->GetDevice()->CreateVertexShader(Data.get(), Size, nullptr, State.pVertexShader.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

      std::unique_ptr<D3D11_INPUT_ELEMENT_DESC[]> InputElementDescs = std::make_unique<D3D11_INPUT_ELEMENT_DESC[]>(_NumElements);

      for (UINT i = 0; i < _NumElements; ++i)
      {
        InputElementDescs[i].SemanticName = _InputElementDescs[i].SemanticName_;
        InputElementDescs[i].SemanticIndex = _InputElementDescs[i].SemanticIndex_;
        InputElementDescs[i].Format = static_cast<DXGI_FORMAT>(_InputElementDescs[i].Format_);
        InputElementDescs[i].InputSlot = _InputElementDescs[i].InputSlot_;
        InputElementDescs[i].AlignedByteOffset = _InputElementDescs[i].AlignedByteOffset_;
        InputElementDescs[i].InputSlotClass = static_cast<D3D11_INPUT_CLASSIFICATION>(_InputElementDescs[i].InputSlotClass_);
        InputElementDescs[i].InstanceDataStepRate = _InputElementDescs[i].InstanceDataStepRate_;
      }

      //  入力レイアウトの作成
      hr = pSystem->GetDevice()->CreateInputLayout(InputElementDescs.get(), _NumElements, Data.get(), Size, State.pInputLayout.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    }

    ID = StateMap.insert(_FilePath, State);
  }

  return ID;
}

ID3D11InputLayout* IVertexShader::GetInputLayout(const hdx::VertexShader& _VertexShader)
{
  const int ID = _VertexShader.GetID();

  if (ID < 0)
  {
    return nullptr;
  }

  return StateMap[ID].pInputLayout.Get();
}

ID3D11VertexShader* IVertexShader::GetVertexShader(const hdx::VertexShader& _VertexShader)
{
  const int ID = _VertexShader.GetID();

  if (ID < 0)
  {
    return nullptr;
  }

  return StateMap[ID].pVertexShader.Get();
}
