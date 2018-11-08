#include <HDX/VertexShader/IVertexShader.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

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
      hdx::InputElementDesc::Position,
      hdx::InputElementDesc::Color,
      hdx::InputElementDesc::Texcoord
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
        hr = detail::Engine::GetSystem()->GetDevice()->CreateVertexShader(Data.get(), Size, nullptr, State.pVertexShader.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateVertexShader");

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
        hr = detail::Engine::GetSystem()->GetDevice()->CreateInputLayout(InputElementDescs.get(), _NumElements, Data.get(), Size, State.pInputLayout.GetAddressOf());
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
