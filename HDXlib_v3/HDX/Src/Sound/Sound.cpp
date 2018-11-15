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

    //  エラー処理
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  //  音量設定
  void Sound::SetVolume(float Volume)const
  {
    pMediaPlayer_->SetVolume(Volume);
  }

  //  再生
  void Sound::Play()const
  {
    pMediaPlayer_->Play();
  }

  //  一時停止
  void Sound::Pause()const
  {
    pMediaPlayer_->Pause();
  }

  //  停止
  void Sound::Stop()const
  {
    pMediaPlayer_->Stop();
  }

  //  再生中か確認
  bool Sound::NowPlaying()const
  {
    MFP_MEDIAPLAYER_STATE state = MFP_MEDIAPLAYER_STATE_EMPTY;
    pMediaPlayer_->GetState(&state);

    return (state == MFP_MEDIAPLAYER_STATE_PLAYING);
  }

  //  無限ループ
  void Sound::Loop()const
  {
    if (!NowPlaying()) Play();
  }
}
