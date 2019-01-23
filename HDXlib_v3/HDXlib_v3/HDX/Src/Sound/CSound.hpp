#pragma once
#include "ISound.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>
#include <mfplay.h>
#include <string>

class CSound : public ISound
{
  struct Data
  {
    Microsoft::WRL::ComPtr<IMFPMediaPlayer> pMediaPlayer;
    bool isLoop = false;
  };
private:
  HWND hWnd_;
  NumberMap<std::string, Data> DataMap_;
public:
  void Initialize(const HWND& _hWnd)override;

  void Update()override;

  int Load(const char* _FilePath)override;

  void Play(int _ID, bool _Loop)override;

  void Pause(int _ID)override;

  void Stop(int _ID)override;

  bool isPlaying(int _ID)override;

  bool isPause(int _ID)override;

  bool isLoop(int _ID)override;

  void SetVolume(int _ID, float _Volume)override;

  void SetSpped(int _ID, float _Speed)override;
};
