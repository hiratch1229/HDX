#pragma once
#include "IConstantBuffer.hpp"

#include <wrl.h>
#include <unordered_map>

class CConstantBuffer : public IConstantBuffer
{
  std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> Buffers_;
  ID3D11Device* pDevice_;
public:
  ID3D11Buffer* GetConstantBuffer(UINT _ID)override;

  int Add(UINT _Size)override;
public:
  void Initialize(ID3D11Device* _pDevice)override;
};
