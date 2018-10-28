#include <HDX/System/System.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

#include <Windows.h>
#include <crtdbg.h>

#include <time.h>
#include <locale>

//  ���b�Z�[�W�v���V�[�W���̃v���g�^�C�v�錾
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//  ���C���֐��̃v���g�^�C�v�錾
void Main();

//  ���b�Z�[�W�v���V�[�W��
//LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//  return detail::Engine::GetSystem()->MsgProc(hWnd, msg, wParam, lParam);
//}

//  �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
  //  ���������[�N���o
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  //  ���ԂŃ����_��
  srand(static_cast<unsigned int>(time(nullptr)));

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
    WindowClass.hIcon = nullptr;
    WindowClass.hCursor = nullptr;
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WindowClass.lpszMenuName = nullptr;
    WindowClass.lpszClassName = L"HDXlib";
    WindowClass.hIconSm = nullptr;
    RegisterClassEx(&WindowClass);
  }

  //  �E�B���h�E&�f�o�C�X&�X���b�v�`�F�[������
  //detail::System::Get()->CreateWindowAndDeviceAndSwapChain(hInstance);

  //  �G���W���̍쐬
  detail::Engine();

  //  �v���O�����̎��s
  Main();

  //  �\�t�g�I��
  return 0;
}
