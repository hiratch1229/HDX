#include <HDX/PixelShader/IPixelShader.hpp>
#include <HDX/System.hpp>
#include <HDX/NumberMap.hpp>
#include <HDX/Macro.hpp>

#include <d3d11.h>
#include <wrl.h>
#include <memory>

namespace detail
{
  class IPixelShader::Impl
  {
  public:
    NumberMap<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> PixelShaderMap_;
  public:
    Impl() { PixelShaderMap_.clear(); }
    ~Impl() { PixelShaderMap_.clear(); }
  };

  //  ������
  IPixelShader::IPixelShader()
    : pImpl_(new Impl)
  {

  }

  //  ���
  IPixelShader::~IPixelShader()
  {
    SAFE_DELETE(pImpl_);
  }

  //  �s�N�Z���V�F�[�_�[�쐬
  int IPixelShader::Create(const char* _FilePath)
  {
    int ID = pImpl_->PixelShaderMap_.find(_FilePath);

    //  ���݂��Ȃ������ꍇ
    if (ID < 0)
    {
      //  �G���[�`�F�b�N�p
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

      Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
      //  �s�N�Z���V�F�[�_�[�̍쐬
      hr = detail::System::Get()->GetDevice()->CreatePixelShader(Data.get(), Size, nullptr, pPixelShader.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), L"CreatePixelShader");

      ID = pImpl_->PixelShaderMap_.insert(_FilePath, pPixelShader);
    }

    return ID;
  }

  ID3D11PixelShader* IPixelShader::GetPixeShader(int _ID)
  {
    return pImpl_->PixelShaderMap_[_ID].Get();
  }
}
