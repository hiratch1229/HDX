#include "Src/Sound/ISound.hpp"

#include "Src/NumberMap.hpp"
#include "Src/Misc.hpp"

#include "Include/Constants.hpp"

#include <d3d11.h>
#include <Mfplay.h>
#include <wrl.h>
#include <string>

namespace
{
  struct Data
  {
    Microsoft::WRL::ComPtr<IMFPMediaPlayer> pMediaPlayer;
    bool isLoop = false;
  };

  HWND hWnd;
  NumberMap<std::string, Data> DataMap;
}

void ISound::Initialize(const HWND& _hWnd)
{
  hWnd = _hWnd;
}

int ISound::Load(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = DataMap.find(_FilePath);
    if (ID >= 0)
    {
      return ID;
    }
  }

  wchar_t wFilePath[hdx::Constants::CharMaxNum]{};
  mbstowcs_s(nullptr, wFilePath, _FilePath, hdx::Constants::CharMaxNum);

  Data Data;

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = MFPCreateMediaPlayer(wFilePath, false, MFP_OPTION_NONE, nullptr, hWnd, Data.pMediaPlayer.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return DataMap.insert(_FilePath, Data);
}

void ISound::Update()
{
  for (int i = 0, Size = DataMap.size(); i < Size; ++i)
  {
    Data& Data = DataMap[i];

    if (Data.isLoop)
    {
      if (!isPlaying(i))
      {
        Data.pMediaPlayer->Play();
      }
    }
  }
}

void ISound::Play(int _ID, bool _Loop)
{
  Data& Data = DataMap[_ID];
  Data.isLoop = _Loop;
  Data.pMediaPlayer->Play();
}

void ISound::Pause(int _ID)
{
  DataMap[_ID].pMediaPlayer->Pause();
}

void ISound::Stop(int _ID)
{
  Data& Data = DataMap[_ID];
  Data.isLoop = false;
  Data.pMediaPlayer->Stop();
}

bool ISound::isPlaying(int _ID)
{
  MFP_MEDIAPLAYER_STATE State = MFP_MEDIAPLAYER_STATE_EMPTY;
  DataMap[_ID].pMediaPlayer->GetState(&State);

  return (State == MFP_MEDIAPLAYER_STATE_PLAYING);
}

bool ISound::isPause(int _ID)
{
  MFP_MEDIAPLAYER_STATE State = MFP_MEDIAPLAYER_STATE_EMPTY;
  DataMap[_ID].pMediaPlayer->GetState(&State);

  return (State == MFP_MEDIAPLAYER_STATE_PAUSED);
}

bool ISound::isLoop(int _ID)
{
  return DataMap[_ID].isLoop;
}

void ISound::SetVolume(int _ID, float _Volume)
{
  DataMap[_ID].pMediaPlayer->SetVolume(_Volume);
}

void ISound::SetSpped(int _ID, float _Speed)
{
  DataMap[_ID].pMediaPlayer->SetRate(_Speed);
}
