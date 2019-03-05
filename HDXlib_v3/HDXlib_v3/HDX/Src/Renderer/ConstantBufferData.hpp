#pragma once

struct ConstantBufferData
{
  int ID = -1;
  void* pData;
public:
  ConstantBufferData() = default;
  ConstantBufferData(int _ID, void* _pData)
    : ID(_ID), pData(_pData)
  {

  }
};
