#include <HDX/System.hpp>

#include <Windows.h>
#include <crtdbg.h>

#include <time.h>
#include <locale>

//  ���C���֐��̃v���g�^�C�v�錾
void Main();

//  ���b�Z�[�W�v���V�[�W��
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return detail::System::Get()->MsgProc(hWnd, msg, wParam, lParam);
}

//  �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  //  ���������[�N���o
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  //  ���ԂŃ����_��
  srand((unsigned)time(nullptr));
  
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
  detail::System::Get()->CreateWindowAndDeviceAndSwapChain(hInstance);

  //  �v���O�����̎��s
  Main();

  //  �\�t�g�I��
  return 0;
}
