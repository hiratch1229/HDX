#include "../Include/System.hpp"

#include "Engine/Engine.hpp"
#include "../Include/Renderer2D.hpp"

#include <Windows.h>
#include <crtdbg.h>

#include <time.h>
#include <locale>

#include "Resource.hpp"

//  ���b�Z�[�W�v���V�[�W���̃v���g�^�C�v�錾
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//  ���C���֐��̃v���g�^�C�v�錾
void Main();

//  �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  //  ���������[�N���o
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  //  ���ԂŃ����_��
  srand(static_cast<UINT>(time(nullptr)));

  //  ���{��ɐݒ�
  setlocale(LC_CTYPE, "jpn");

  //  �E�B���h�E�N���X�̓o�^
  WNDCLASSEX WindowClass;
  {
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_CLASSDC;
    WindowClass.lpfnWndProc = MsgProc;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = hInstance;
    WindowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    WindowClass.hCursor = nullptr;
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WindowClass.lpszMenuName = nullptr;
    WindowClass.lpszClassName = L"HDXlib";
    WindowClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINI_ICON));
    RegisterClassEx(&WindowClass);
  }

  //  �G���W���̍쐬
  detail::Engine Engine;

  //  �V�F�[�_�[�̏����ݒ�
  {
    //  2D
    {
      hdx::Renderer2D::RestoreVertexShader();
      hdx::Renderer2D::RestorePixelShader();
    }
    //  3D
    {

    }
  }

  //  �v���O�����̎��s
  Main();

  //  �\�t�g�I��
  return 0;
}
