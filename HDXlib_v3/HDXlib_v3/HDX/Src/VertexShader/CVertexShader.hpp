#pragma once
#include "IVertexShader.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>
#include <string>

class CVertexShader : public IVertexShader
{
  static constexpr char* kDefault2DFilePath = "DATA/Shader/SpriteVS.cso";
  static constexpr char* kDefault3DFilePath = "DATA/Shader/ModelVS.cso";
private:
  struct State
  {
    Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
  };
private:
  ID3D11Device* pDevice_ = nullptr;
  NumberMap<std::string, State> StateMap_;
public:
  void Initialize(ID3D11Device* _pDevice)override;

  int Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], UINT _NumElements)override;
  
  hdx::VertexShader CreateDefault2D()override;
  
  hdx::VertexShader CreateDefault3D()override;

  ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader)override;

  ID3D11InputLayout* GetInputLayout(const hdx::VertexShader& _VertexShader)override;
};
