#pragma once
#include "../../Include/Types.hpp"

struct ID3D11Device;
struct ID3D11Buffer;

class IConstantBuffer
{
private:
  void Create(UINT _Size);
public:
  ID3D11Buffer* GetConstantBuffer(UINT _Size);
public:
  void Initialize(ID3D11Device* _pDevice);
};
