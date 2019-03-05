#include "CConstantBuffer.hpp"

void CConstantBuffer::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

ID3D11Buffer* CConstantBuffer::GetConstantBuffer(UINT _ID)
{
  return Buffers_[_ID].Get();
}

int CConstantBuffer::Add(UINT _Size)
{
  //  エラーチェック用
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
  hr = pDevice_->CreateBuffer(&ConstantBufferDesc, nullptr, pConstantBuffer.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

  Buffers_.emplace_back(pConstantBuffer);

  return Buffers_.size() - 1;
}
