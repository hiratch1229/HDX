#include "IPixelShader.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../Misc.hpp"

#include "../NumberMap.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <assert.h>
#include <memory>

namespace
{
  NumberMap<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> PixelShaderMap;
}

hdx::PixelShader IPixelShader::CreateDefault2D()
{
  return hdx::PixelShader(kDefault2DFilePath);
}

//  �s�N�Z���V�F�[�_�[�쐬
int IPixelShader::Create(const char* _FilePath)
{
  int ID = PixelShaderMap.find(_FilePath);

  //  ���݂��Ȃ������ꍇ
  if (ID < 0)
  {
    //  �G���[�`�F�b�N�p
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

    Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
    //  �s�N�Z���V�F�[�_�[�̍쐬
    hr = Engine::GetSystem()->GetDevice()->CreatePixelShader(Data.get(), Size, nullptr, pPixelShader.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    ID = PixelShaderMap.insert(_FilePath, pPixelShader);
  }

  return ID;
}

ID3D11PixelShader* IPixelShader::GetPixeShader(const hdx::PixelShader& _PixelShader)
{
  const int ID = _PixelShader.GetID();

  if (ID < 0)
  {
    return nullptr;
  }

  return PixelShaderMap[ID].Get();
}
