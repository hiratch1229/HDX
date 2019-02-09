#pragma once
#include "IVertexShader.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>
#include <string>
#include <memory>

class CVertexShader : public IVertexShader
{
  ID3D11Device* pDevice_ = nullptr;
  NumberMap<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>> VertexShaderMap_;
private:
  int CreateVertexShader(const char* _FilePath, std::unique_ptr<unsigned char[]>* _pData, size_t* _pSize);
  void CreateInputLayout(const char* _FilePath, const D3D11_INPUT_ELEMENT_DESC _InputElementDescs[], UINT _NumElements, ID3D11InputLayout** _ppInputLayout);
public:
  void Initialize(ID3D11Device* _pDevice)override;

  int Create(const char* _FilePath)override;

  hdx::VertexShader CreateGUI(ID3D11InputLayout** _ppInputLayout)override;

  hdx::VertexShader CreateDefault2D(ID3D11InputLayout** _ppInputLayout)override;

  hdx::VertexShader CreateDefault3D(ID3D11InputLayout** _ppInputLayout)override;

  ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader)override;
};
