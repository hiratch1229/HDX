#pragma once
#include "IGUI.hpp"

class CGUI : public IGUI
{
public:
  ~CGUI();

  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, const HWND& _hWnd)override;

  void Update()override;
};
