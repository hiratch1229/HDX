#include <HDX/Sound.hpp>
#include <HDX/System.hpp>
#include <HDX/Error.hpp>

namespace hdx
{
  Sound::Sound(const char* FilePath)
  {
    wchar_t wFilePath[256]{};
    size_t Num;
    mbstowcs_s(&Num, wFilePath, FilePath, 256);
    
    HRESULT hr = MFPCreateMediaPlayer(wFilePath, false, MFP_OPTION_NONE, nullptr, detail::System::Get()->GetHWND(), pMediaPlayer_.GetAddressOf());

    //  �G���[����
    NOT_FOUND(hr, wFilePath);
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
