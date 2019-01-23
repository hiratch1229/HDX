#pragma once
#include <Windows.h>

class ISound
{
public:
  static ISound* Create();

  ISound() = default;

  virtual ~ISound() = default;

  virtual void Initialize(const HWND& _hWnd) = 0;

  virtual void Update() = 0;

  virtual int Load(const char* _FilePath) = 0;

  virtual void Play(int _ID, bool _Loop) = 0;

  virtual void Pause(int _ID) = 0;

  virtual void Stop(int _ID) = 0;

  virtual bool isPlaying(int _ID) = 0;

  virtual bool isPause(int _ID) = 0;

  virtual bool isLoop(int _ID) = 0;

  virtual void SetVolume(int _ID, float _Volume) = 0;

  virtual void SetSpped(int _ID, float _Speed) = 0;
};
