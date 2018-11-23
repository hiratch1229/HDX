#pragma once

//  ライブラリ
namespace hdx
{
  //  サウンド
  class Sound
  {
  private:
    int ID_;
  public:
    //  ファイルパスからサウンドを作成
    Sound(const char* _FilePath);
  public:
    //  再生
    //  _Loop:trueで自動ループ
    void Play(bool _Loop = false)const;
    //  一時停止
    void Pause()const;
    //  停止
    //  ループ設定が解除されます
    void Stop()const;
    //  再生中ならtrueを返します
    bool isPlaying()const;
    //  停止中ならtrueを返します
    bool isPause()const;
    //  ループ設定ならtrueを返します
    bool isLoop()const;
    //  音量を設定
    //  0は消音、1は通常
    void SetVolume(float _Volume)const;
    //  速さを設定
    //  負の値で逆再生、正の値で再生
    void SetSpeed(float _Speed)const;
  };
}
