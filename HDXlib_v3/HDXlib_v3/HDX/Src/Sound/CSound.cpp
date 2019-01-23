#include "CSound.hpp"

#include "Src/Misc.hpp"

#include "Include/Constants.hpp"

void CSound::Initialize(const HWND& _hWnd)
{
  hWnd_ = _hWnd;
}

int CSound::Load(const char* _FilePath)
{
  //  既に作成されているか確認
  {
    const int ID = DataMap_.find(_FilePath);
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

  hr = MFPCreateMediaPlayer(wFilePath, false, MFP_OPTION_NONE, nullptr, hWnd_, Data.pMediaPlayer.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return DataMap_.insert(_FilePath, Data);
}

void CSound::Update()
{
  for (int i = 0, Size = DataMap_.size(); i < Size; ++i)
  {
    Data& Data = DataMap_[i];

    if (Data.isLoop)
    {
      if (!isPlaying(i))
      {
        Data.pMediaPlayer->Play();
      }
    }
  }
}

void CSound::Play(int _ID, bool _Loop)
{
  Data& Data = DataMap_[_ID];
  Data.isLoop = _Loop;
  Data.pMediaPlayer->Play();
}

void CSound::Pause(int _ID)
{
  DataMap_[_ID].pMediaPlayer->Pause();
}

void CSound::Stop(int _ID)
{
  Data& Data = DataMap_[_ID];
  Data.isLoop = false;
  Data.pMediaPlayer->Stop();
}

bool CSound::isPlaying(int _ID)
{
  MFP_MEDIAPLAYER_STATE State = MFP_MEDIAPLAYER_STATE_EMPTY;
  DataMap_[_ID].pMediaPlayer->GetState(&State);

  return (State == MFP_MEDIAPLAYER_STATE_PLAYING);
}

bool CSound::isPause(int _ID)
{
  MFP_MEDIAPLAYER_STATE State = MFP_MEDIAPLAYER_STATE_EMPTY;
  DataMap_[_ID].pMediaPlayer->GetState(&State);

  return (State == MFP_MEDIAPLAYER_STATE_PAUSED);
}

bool CSound::isLoop(int _ID)
{
  return DataMap_[_ID].isLoop;
}

void CSound::SetVolume(int _ID, float _Volume)
{
  DataMap_[_ID].pMediaPlayer->SetVolume(_Volume);
}

void CSound::SetSpped(int _ID, float _Speed)
{
  DataMap_[_ID].pMediaPlayer->SetRate(_Speed);
}
