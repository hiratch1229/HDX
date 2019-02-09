#include "CPixelShader.hpp"

#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include <memory>
#include <assert.h>

void CPixelShader::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

//  ピクセルシェーダー作成
int CPixelShader::Create(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = PixelShaderMap_.find(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  //  エラーチェック用
  HRESULT hr = S_OK;

  FILE* fp;
  fopen_s(&fp, _FilePath, "rb");
  _ASSERT_EXPR_A(fp, (std::string(_FilePath) + "が存在しません。").c_str());

  fseek(fp, 0, SEEK_END);
  long Size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::unique_ptr<unsigned char[]> Data = std::make_unique<unsigned char[]>(Size);
  fread(Data.get(), Size, 1, fp);
  fclose(fp);

  Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
  //  ピクセルシェーダーの作成
  hr = pDevice_->CreatePixelShader(Data.get(), Size, nullptr, pPixelShader.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return PixelShaderMap_.insert(_FilePath, pPixelShader);
}

hdx::PixelShader CPixelShader::CreateGUI()
{
  return hdx::PixelShader(kGUIPixelShaderFilePath);
}

hdx::PixelShader CPixelShader::CreateDefault2D()
{
  return hdx::PixelShader(kDefault2DPixelShaderFilePath);
}

hdx::PixelShader CPixelShader::CreateDefault3D()
{
  return hdx::PixelShader(kDefault3DPixelShaderFilePath);
}

ID3D11PixelShader* CPixelShader::GetPixeShader(const hdx::PixelShader& _PixelShader)
{
  const int ID = _PixelShader.GetID();

  if (ID < 0)
  {
    return nullptr;
  }

  return PixelShaderMap_[ID].Get();
}
