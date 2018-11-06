#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/System/System.hpp>
#include <HDX/InputElementDesc.hpp>
#include <HDX/NumberMap.hpp>

#include <d3d11.h>
#include <wrl.h>
#include <memory>

namespace detail
{
  class IVertexShader::Impl
  {
  public:
    struct State
    {
      Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
      Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
    };
  public:
    NumberMap<std::string, State> StateMap_;
  public:
    Impl() { StateMap_.clear(); }
    ~Impl() { StateMap_.clear(); }
  };

  //  初期化
  IVertexShader::IVertexShader()
    : pImpl_(new Impl)
  {

  }

  //  解放
  IVertexShader::~IVertexShader()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  hdx::VertexShader IVertexShader::CreateDefault2D()
  {
    hdx::InputElementDesc InputElementDescs[] =
    {
      { "POSITION", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "COLOR", 0, hdx::Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, hdx::Format::R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
    };

    return hdx::VertexShader(kDefault2DFilePath, InputElementDescs, ARRAYSIZE(InputElementDescs));
  }

  //  バーテックスシェーダー作成
  int IVertexShader::Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], UINT _NumElements)
  {
    int ID = pImpl_->StateMap_.find(_FilePath);

    //  存在しなかった場合
    if (ID < 0)
    {
      //  エラーチェック用
      HRESULT hr = S_OK;

      FILE* fp;
      fopen_s(&fp, _FilePath, "rb");
      _ASSERT_EXPR(fp, L"fopen_s");

      fseek(fp, 0, SEEK_END);
      long Size = ftell(fp);
      fseek(fp, 0, SEEK_SET);

      std::unique_ptr<unsigned char[]> Data = std::make_unique<unsigned char[]>(Size);
      fread(Data.get(), Size, 1, fp);
      fclose(fp);

      Impl::State State;
      {
        //  頂点シェーダーの作成
        hr = detail::System::Get()->GetDevice()->CreateVertexShader(Data.get(), Size, nullptr, State.pVertexShader.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateVertexShader");

        std::unique_ptr<D3D11_INPUT_ELEMENT_DESC[]> InputElementDescs = std::make_unique<D3D11_INPUT_ELEMENT_DESC[]>(_NumElements);

        for (unsigned int i = 0; i < _NumElements; ++i)
        {
          InputElementDescs[i].SemanticName = _InputElementDescs[i].SemanticName;
          InputElementDescs[i].SemanticIndex = _InputElementDescs[i].SemanticIndex;
          InputElementDescs[i].Format = static_cast<DXGI_FORMAT>(_InputElementDescs[i].Format);
          InputElementDescs[i].InputSlot = _InputElementDescs[i].InputSlot;
          InputElementDescs[i].AlignedByteOffset = _InputElementDescs[i].AlignedByteOffset;
          InputElementDescs[i].InputSlotClass = static_cast<D3D11_INPUT_CLASSIFICATION>(_InputElementDescs[i].InputSlotClass);
          InputElementDescs[i].InstanceDataStepRate = _InputElementDescs[i].InstanceDataStepRate;
        }

        //  入力レイアウトの作成
        hr = detail::System::Get()->GetDevice()->CreateInputLayout(InputElementDescs.get(), _NumElements, Data.get(), Size, State.pInputLayout.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateInputLayout");
      }

      ID = pImpl_->StateMap_.insert(_FilePath, State);
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

    return pImpl_->StateMap_[ID].pInputLayout.Get();
  }

  ID3D11VertexShader* IVertexShader::GetVertexShader(const hdx::VertexShader& _VertexShader)
  {
    const int ID = _VertexShader.GetID();

    if (ID < 0)
    {
      return nullptr;
    }

    return pImpl_->StateMap_[ID].pVertexShader.Get();
  }
}
