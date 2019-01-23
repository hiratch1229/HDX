#include "CConstatBuffer.hpp"

void CConstatBuffer::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

inline void CConstatBuffer::Create(UINT _Size)
{
  //  既に作成されていたら終了
  if (BufferMap_.find(_Size) != BufferMap_.end())
  {
    return;
  }

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

  BufferMap_.insert(std::make_pair(_Size, pConstantBuffer));
}

ID3D11Buffer* CConstatBuffer::GetConstantBuffer(UINT _Size)
{
  //  作成されて居なければ作成
  if (BufferMap_.find(_Size) == BufferMap_.end())
  {
    Create(_Size);
  }

  return BufferMap_[_Size].Get();
}
