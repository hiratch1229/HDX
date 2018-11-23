#pragma once

//  ���C�u����
namespace hdx
{
  //  �T�E���h
  class Sound
  {
  private:
    int ID_;
  public:
    //  �t�@�C���p�X����T�E���h���쐬
    Sound(const char* _FilePath);
  public:
    //  �Đ�
    //  _Loop:true�Ŏ������[�v
    void Play(bool _Loop = false)const;
    //  �ꎞ��~
    void Pause()const;
    //  ��~
    //  ���[�v�ݒ肪��������܂�
    void Stop()const;
    //  �Đ����Ȃ�true��Ԃ��܂�
    bool isPlaying()const;
    //  ��~���Ȃ�true��Ԃ��܂�
    bool isPause()const;
    //  ���[�v�ݒ�Ȃ�true��Ԃ��܂�
    bool isLoop()const;
    //  ���ʂ�ݒ�
    //  0�͏����A1�͒ʏ�
    void SetVolume(float _Volume)const;
    //  ������ݒ�
    //  ���̒l�ŋt�Đ��A���̒l�ōĐ�
    void SetSpeed(float _Speed)const;
  };
}
