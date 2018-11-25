#include "../../Include/System.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"

#include "../../Include/Type2.hpp"
#include "../../Include/Constants.hpp"

#include <Windows.h>

namespace hdx
{
  //**************************************************
  //**************************************************
  //  System�N���X
  //**************************************************
  //**************************************************

  //  �X�V
  int System::Update()
  {
    return Engine::Get<ISystem>()->Update();
  }

  //  ��ʕ����擾
  int System::GetWindowWidth()
  {
    return Engine::Get<ISystem>()->GetWindowWidth();
  }

  //  ��ʍ����擾
  int System::GetWindowHeight()
  {
    return Engine::Get<ISystem>()->GetWindowHeight();
  }

  //  ��ʃT�C�Y���擾
  const int2& System::GetWindowSize()
  {
    return Engine::Get<ISystem>()->GetWindowSize();
  }

  float System::GetDeltaTime()
  {
    return Engine::Get<ISystem>()->GetDeltaTime();
  }

  //  �E�B���h�E�̐ݒ�
  void System::SetWindowLeftTopPos(int _LeftPos, int _TopPos)
  {
    Engine::Get<ISystem>()->SetWindowLeftTopPos({ _LeftPos, _TopPos });
  }

  //  �E�B���h�E�̐ݒ�
  void System::SetWindowLeftTopPos(const int2& _LeftTopPos)
  {
    Engine::Get<ISystem>()->SetWindowLeftTopPos(_LeftTopPos);
  }

  //  �E�B���h�E�̐ݒ�
  void System::SetWindowSize(int _Width, int _Height)
  {
    Engine::Get<ISystem>()->SetWindowSize({ _Width, _Height });
  }

  //  �E�B���h�E�̐ݒ�
  void System::SetWindowSize(const int2& _Size)
  {
    Engine::Get<ISystem>()->SetWindowSize(_Size);
  }

  //  �E�B���h�E�̐ݒ�
  void System::SetWindowMode(bool _isFullScreen)
  {
    Engine::Get<ISystem>()->SetWindowMode(_isFullScreen);
  }

  //  �E�B���h�E�̐ݒ�
  void System::SettingWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen)
  {
    Engine::Get<ISystem>()->SetWindow({ _LeftPos, _TopPos }, { _Width, _Height }, _isFullScreen);
  }

  //  �E�B���h�E�̐ݒ�
  void System::SettingWindow(const int2& _LeftTopPos, const int2& _Size, bool _isFullScreen)
  {
    Engine::Get<ISystem>()->SetWindow(_LeftTopPos, _Size, _isFullScreen);
  }

  //  �J�[�\���\���ݒ�
  void System::ShowCursor(bool _isShowCursor)
  {
    Engine::Get<ISystem>()->ShowCursor(_isShowCursor);
  }

  //  �E�B���h�E�̃^�C�g����ݒ�
  void System::SetTitle(const char* _Title)
  {
    Engine::Get<ISystem>()->SetTitle(_Title);
  }

  //  �w�i�̐F�ύX
  void System::SetBackColor(const ColorF& _Color)
  {
    Engine::Get<ISystem>()->SetBackColor(_Color);
  }

  //  �E�B���h�E�̃��[�h��ύX
  void System::ChangeWindowMode()
  {
    Engine::Get<ISystem>()->ChangeWindowMode();
  }

  //  �E�B���h�E�̃^�C�g����ύX
  void System::RenameTitle(const char* _Title)
  {
    Engine::Get<ISystem>()->RenameTitle(_Title);
  }

  //  �X�N���[���V���b�g
  void System::ScreenShot()
  {
    Engine::Get<ISystem>()->ScreenShot();
  }

  //  �o�͂ɕ�����`��
  void System::OutputDebug(const char* _Str)
  {
    wchar_t Str[Constants::CharMaxNum];
    mbstowcs_s(nullptr, Str, _Str, Constants::CharMaxNum);
    OutputDebugString(Str);
  }

  //  �\�t�g���I��
  void System::Exit()
  {
    Engine::Get<ISystem>()->Exit();
  }
}
