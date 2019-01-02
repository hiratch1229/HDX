#include "Include/Sound.hpp"

#include "Src/Engine.hpp"
#include "Src/Sound/ISound.hpp"

#include "Include/Constants.hpp"

namespace hdx
{
  //  ファイルパスからサウンドを作成
  Sound::Sound(const char* _FilePath)
    : ID_(Engine::Get<ISound>()->Load(_FilePath))
  {

  }

  //  再生
  void Sound::Play(bool _Loop)const
  {
    Engine::Get<ISound>()->Play(ID_, _Loop);
  }

  //  一時停止
  void Sound::Pause()const
  {
    Engine::Get<ISound>()->Pause(ID_);
  }

  //  停止
  void Sound::Stop()const
  {
    Engine::Get<ISound>()->Stop(ID_);
  }

  //  再生中ならtrueを返します
  bool Sound::isPlaying()const
  {
    return Engine::Get<ISound>()->isPlaying(ID_);
  }

  //  停止中ならtrueを返します
  bool Sound::isPause()const
  {
    return Engine::Get<ISound>()->isPause(ID_);
  }

  //  ループ設定ならtrueを返します
  bool Sound::isLoop()const
  {
    return Engine::Get<ISound>()->isLoop(ID_);
  }

  //  音量を設定
  void Sound::SetVolume(float _Volume)const
  {
    Engine::Get<ISound>()->SetVolume(ID_, _Volume);
  }

  //  速さを設定
  void Sound::SetSpeed(float _Speed)const
  {
    Engine::Get<ISound>()->SetVolume(ID_, _Speed);
  }
}
