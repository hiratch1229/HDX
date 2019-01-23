#pragma once
#include <d3d11.h>

class IConstantBuffer
{
public:
  static IConstantBuffer* Create();

  IConstantBuffer() = default;

  virtual ~IConstantBuffer() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual ID3D11Buffer* GetConstantBuffer(UINT _Size) = 0;
};
