#pragma once
#include "Type2.hpp"
#include "Color.hpp"

//  ���C�u����
namespace hdx
{
  //  �V�X�e��
  class System
  {
    System() = delete;
    System(const System&) = delete;
    System& operator=(const System&) = delete;
  public:
    //  ��ʕ����擾
    static int GetWindowWidth();
    //  ��ʍ����擾
    static int GetWindowHeight();
    //  ��ʃT�C�Y���擾
    static const int2& GetWindowSize();
    //  �o�ߎ��Ԃ��擾
    static float GetDeltaTime();
    //  ���݂̃t���[�����[�g���擾
    static int GetFPS();
  public:
    //  �E�B���h�E�̐ݒ�
    //  _LeftPos:������WX
    //  _TopPos:������WY
    static void SetWindowLeftTopPos(int _LeftPos, int _TopPos);
    //  �E�B���h�E�̐ݒ�
    //  _LeftTopPos:������W
    static void SetWindowLeftTopPos(const int2& _LeftTopPos);
    //  �E�B���h�E�̐ݒ�
    //  _Width:�E�B���h�E��
    //  _Height:�E�B���h�E��
    static void SetWindowSize(int _Width, int _Height);
    //  �E�B���h�E�̐ݒ�
    //  _Size:�E�B���h�E�c����
    static void SetWindowSize(const int2& _Size);
    //  �E�B���h�E�̐ݒ�
    //  _isFullScreen:��ʃ��[�h(true:�t���X�N���[��,false:�E�B���h�E���[�h)
    static void SetWindowMode(bool _isFullScreen);
    //  �E�B���h�E�̐ݒ�
    //  _LeftPos:������WX
    //  _TopPos:������WY
    //  _Width:�E�B���h�E��
    //  _Height:�E�B���h�E��
    //  _isFullScreen:��ʃ��[�h(true:�t���X�N���[��,false:�E�B���h�E���[�h)
    static void SettingWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen = false);
    //  �E�B���h�E�̐ݒ�
    //  _LeftTopPos:������W
    //  _Size:�E�B���h�E�c����
    //  _isFullScreen:��ʃ��[�h(true:�t���X�N���[��,false:�E�B���h�E���[�h)
    static void SettingWindow(const int2& _LeftTopPos, const int2& _Size, bool _isFullScreen = false);
    //  �J�[�\���\���ݒ�(true:�\��,false:��\��)
    static void ShowCursor(bool _isShowCursor);
    //  �E�B���h�E�̃^�C�g����ݒ�
    static void SetTitle(const char* _Title);
    //  �w�i�̐F�ύX
    static void SetBackColor(const ColorF& _Color);
    //  �t���[�����[�g����
    //  0�Ŗ�����
    static void SetFPS(UINT _MaxFPS);

    ////  �E�B���h�E�̃T�C�Y��ύX
    ////  _Width:�E�B���h�E��
    ////  _Height:�E�B���h�E�� 
    //static inline void ResizeWindow(int _Width, int _Height)
    //{
    //  detail::System::Get()->ResizeWindow(_Width, _Height);
    //}

    //  �E�B���h�E�̃��[�h��ύX
    //  �E�B���h�E���[�h�̃t���X�N���[��
    static void ChangeWindowMode();
    //  �E�B���h�E�̃^�C�g����ύX
    static void RenameTitle(const char* _Title);
    //  �X�N���[���V���b�g
    //  SCREENSHOT�t�H���_�ɕۑ�
    static void ScreenShot();
    //  �o�͂ɕ�����`��
    static void OutputDebug(const char* _Str);
    //  �\�t�g���I��
    static void Exit();
  public:
    //  �X�V
    static int Update();
  };
};
