#pragma once
#include <Mfplay.h>
#include <wrl.h>

//  ���C�u����
namespace hdx
{
  //  �T�E���h
  class Sound
  {
  private:
    Microsoft::WRL::ComPtr<IMFPMediaPlayer>	pMediaPlayer_;
  public:
    //  �t�@�C���p�X����T�E���h���쐬
    Sound(const char* FilePath);
  public:
    void SetVolume(float Volume)const;
    void Play()const;
    void Pause()const;
    void Stop()const;
    bool NowPlaying()const;
    void Loop()const;
  };
}
