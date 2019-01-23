#pragma once
#include <d3d11.h>

class IGUI
{
public:
  static IGUI* Create();

  IGUI() = default;

  virtual ~IGUI() = default;

  virtual void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, const HWND& _hWnd) = 0;

  virtual void Update() = 0;
};
