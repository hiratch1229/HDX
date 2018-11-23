#pragma once

struct HWND__;
typedef HWND__* HWND;

class ISound
{
public:
  int Load(const char* _FilePath);
public:
  void Play(int _ID, bool _Loop);
  void Pause(int _ID);
  void Stop(int _ID);
  bool isPlaying(int _ID);
  bool isPause(int _ID);
  bool isLoop(int _ID);
  void SetVolume(int _ID,float _Volume);
  void SetSpped(int _ID, float _Speed);
public:
  void Initialize(const HWND& _hWnd);
  void Update();
};
