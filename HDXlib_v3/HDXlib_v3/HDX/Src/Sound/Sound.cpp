#include "Include/Sound.hpp"

#include "Src/Engine.hpp"
#include "Src/Sound/ISound.hpp"

#include "Include/Constants.hpp"

namespace hdx
{
  //  �t�@�C���p�X����T�E���h���쐬
  Sound::Sound(const char* _FilePath)
    : ID_(Engine::Get<ISound>()->Load(_FilePath))
  {

  }

  //  �Đ�
  void Sound::Play(bool _Loop)const
  {
    Engine::Get<ISound>()->Play(ID_, _Loop);
  }

  //  �ꎞ��~
  void Sound::Pause()const
  {
    Engine::Get<ISound>()->Pause(ID_);
  }

  //  ��~
  void Sound::Stop()const
  {
    Engine::Get<ISound>()->Stop(ID_);
  }

  //  �Đ����Ȃ�true��Ԃ��܂�
  bool Sound::isPlaying()const
  {
    return Engine::Get<ISound>()->isPlaying(ID_);
  }

  //  ��~���Ȃ�true��Ԃ��܂�
  bool Sound::isPause()const
  {
    return Engine::Get<ISound>()->isPause(ID_);
  }

  //  ���[�v�ݒ�Ȃ�true��Ԃ��܂�
  bool Sound::isLoop()const
  {
    return Engine::Get<ISound>()->isLoop(ID_);
  }

  //  ���ʂ�ݒ�
  void Sound::SetVolume(float _Volume)const
  {
    Engine::Get<ISound>()->SetVolume(ID_, _Volume);
  }

  //  ������ݒ�
  void Sound::SetSpeed(float _Speed)const
  {
    Engine::Get<ISound>()->SetVolume(ID_, _Speed);
  }
}
