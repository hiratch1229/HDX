#include "Src/Engine.hpp"

#include <Windows.h>
#include <crtdbg.h>
#include <locale>

#include "Src/Resource.hpp"

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
  Engine Engine;

  //  �v���O�����̎��s
  Main();

  //  �\�t�g�I��
  return 0;
}
