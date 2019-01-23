#pragma once
#include "IConstantBuffer.hpp"

#include <wrl.h>
#include <unordered_map>

class CConstatBuffer : public IConstantBuffer
{
  std::unordered_map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>> BufferMap_;
  ID3D11Device* pDevice_;
private:
  void Create(UINT _Size);
public:
  ID3D11Buffer* GetConstantBuffer(UINT _Size);
public:
  void Initialize(ID3D11Device* _pDevice);
};
