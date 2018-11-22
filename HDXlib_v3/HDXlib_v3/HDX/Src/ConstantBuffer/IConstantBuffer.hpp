#pragma once
#include "../../Include/Types.hpp"

struct ID3D11Buffer;

class IConstantBuffer
{
private:
  void Create(UINT _Size);
public:
  ID3D11Buffer* GetConstantBuffer(UINT _Size);
public:
  IConstantBuffer() = default;
public:
  void Initialize();
};
