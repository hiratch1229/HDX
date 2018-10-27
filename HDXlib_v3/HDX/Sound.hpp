#pragma once
#include <Mfplay.h>
#include <wrl.h>

//  ライブラリ
namespace hdx
{
  //  サウンド
  class Sound
  {
  private:
    Microsoft::WRL::ComPtr<IMFPMediaPlayer>	pMediaPlayer_;
  public:
    //  ファイルパスからサウンドを作成
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
