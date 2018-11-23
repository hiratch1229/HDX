#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct HWND__;
typedef HWND__* HWND;

class IGUI
{
public:
  ~IGUI();
public:
  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext,const HWND& _hWnd);
  void Update();
};
