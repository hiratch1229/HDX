#include "Src/ConstantBuffer/IConstantBuffer.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <unordered_map>

namespace
{
  std::unordered_map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>> BufferMap;
  ID3D11Device* pDevice;
}

void IConstantBuffer::Initialize(ID3D11Device* _pDevice)
{
  pDevice = _pDevice;
}

inline void IConstantBuffer::Create(UINT _Size)
{
  //  ���ɍ쐬����Ă�����I��
  if (BufferMap.find(_Size) != BufferMap.end())
  {
    return;
  }

  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;

  D3D11_BUFFER_DESC ConstantBufferDesc{};
  {
    ConstantBufferDesc.ByteWidth = _Size;
    ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ConstantBufferDesc.CPUAccessFlags = 0;
    ConstantBufferDesc.MiscFlags = 0;
    ConstantBufferDesc.StructureByteStride = 0;
  }
  hr = pDevice->CreateBuffer(&ConstantBufferDesc, nullptr, pConstantBuffer.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

  BufferMap.insert(std::make_pair(_Size, pConstantBuffer));
}

ID3D11Buffer* IConstantBuffer::GetConstantBuffer(UINT _Size)
{
  //  �쐬����ċ��Ȃ���΍쐬
  if (BufferMap.find(_Size) == BufferMap.end())
  {
    Create(_Size);
  }

  return BufferMap[_Size].Get();
}
