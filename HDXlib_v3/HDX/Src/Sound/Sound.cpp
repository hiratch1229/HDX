#include "../../Include/Sound.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../Error.hpp"

#include "../../Include/Constants.hpp"

namespace hdx
{
  Sound::Sound(const char* FilePath)
  {
    wchar_t wFilePath[MaxCharLimit]{};
    size_t Num;
    mbstowcs_s(&Num, wFilePath, FilePath, MaxCharLimit);
    
    HRESULT hr = MFPCreateMediaPlayer(wFilePath, false, MFP_OPTION_NONE, nullptr, GetActiveWindow(), pMediaPlayer_.GetAddressOf());

    //  �G���[����
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  //  ���ʐݒ�
  void Sound::SetVolume(float Volume)const
  {
    pMediaPlayer_->SetVolume(Volume);
  }

  //  �Đ�
  void Sound::Play()const
  {
    pMediaPlayer_->Play();
  }

  //  �ꎞ��~
  void Sound::Pause()const
  {
    pMediaPlayer_->Pause();
  }

  //  ��~
  void Sound::Stop()const
  {
    pMediaPlayer_->Stop();
  }

  //  �Đ������m�F
  bool Sound::NowPlaying()const
  {
    MFP_MEDIAPLAYER_STATE state = MFP_MEDIAPLAYER_STATE_EMPTY;
    pMediaPlayer_->GetState(&state);

    return (state == MFP_MEDIAPLAYER_STATE_PLAYING);
  }

  //  �������[�v
  void Sound::Loop()const
  {
    if (!NowPlaying()) Play();
  }
}
