#include "IGamepad.hpp"

#include "../../Input/InputState.hpp"

#include "../../Engine.hpp"
#include "../../System/ISystem.hpp"
#include "../../Input/XInput/IXInput.hpp"

#include "../../../Include/Math.hpp"
#include "../../../Include/Macro.hpp"

#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>
#include <wbemidl.h>
#include <wrl.h>
#include <vector>
#include <memory>

#define SAFE_RELEASE(Obj)  if( Obj ){ Obj->Release(); Obj = nullptr; }	

namespace
{
  //  DirectInputの数
  int DirectInputNum = 0;
  //  XInputの数
  int XInputNum = 0;
  //  コントローラの数
  int ControllerNum = 0;

  struct DirectInputData
  {
    //  ジョイスティック
    LPDIRECTINPUTDEVICE8 pJoyStick;
    //  振動エフェクト
    LPDIRECTINPUTEFFECT pEffect;
  public:
    DirectInputData()
    {

    }
    ~DirectInputData()
    {
      SAFE_RELEASE(pJoyStick);
      SAFE_RELEASE(pEffect);
    }
  };

  Microsoft::WRL::ComPtr<IDirectInput8W> pDirectInput;

  std::unique_ptr<DirectInputData[]> pDirectInputDatas;

  //  XInput判別用リスト
  std::vector<LONG> XInputList;

  constexpr int kStickMaxValue = 10000;
  constexpr int kTriggerMaxValue = 65535;

  void CreateDirectInputDevice(const GUID& GuidProductFromDirectInput)
  {
    //  作成済みジョイスティック数
    static int CreateDeviceNum = 0;

    DirectInputData& pDirectInputData = pDirectInputDatas[CreateDeviceNum];

    //  ジョイスティックを作成
    pDirectInput->CreateDevice(GuidProductFromDirectInput, &pDirectInputData.pJoyStick, nullptr);
    pDirectInputData.pJoyStick->SetDataFormat(&c_dfDIJoystick);
    pDirectInputData.pJoyStick->SetCooperativeLevel(Engine::GetSystem()->GetHWND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

    // 軸の値の範囲を設定
    DIPROPRANGE DirectInputPropatyRange;
    {
      DirectInputPropatyRange.diph.dwSize = sizeof(DirectInputPropatyRange);
      DirectInputPropatyRange.diph.dwHeaderSize = sizeof(DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_X;
      DirectInputPropatyRange.diph.dwHow = DIPH_BYOFFSET;
      DirectInputPropatyRange.lMin = -kStickMaxValue;
      DirectInputPropatyRange.lMax = +kStickMaxValue;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_Y;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_Z;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_RZ;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
    }

    //  振動を設定
    {
      // エフェクト周期設定
      DIPERIODIC diPeriodic;
      diPeriodic.dwMagnitude = DI_FFNOMINALMAX;
      diPeriodic.lOffset = 0;
      diPeriodic.dwPhase = 0;
      diPeriodic.dwPeriod = (DWORD)(0.5f * DI_SECONDS);

      // 振動エフェクト設定
      DIEFFECT DirectInputEffect{};
      DirectInputEffect.dwSize = sizeof(DIEFFECT);
      DirectInputEffect.dwFlags = DIEFF_OBJECTOFFSETS;
      DirectInputEffect.dwDuration = 0;
      DirectInputEffect.dwSamplePeriod = 0;
      DirectInputEffect.dwGain = DI_FFNOMINALMAX;

      //  トリガー設定
      DirectInputEffect.dwTriggerButton = DIEB_NOTRIGGER;
      DirectInputEffect.dwTriggerRepeatInterval = 0;
      //  エフェクト軸設定
      DirectInputEffect.dwFlags |= DIEFF_POLAR;
      DWORD Axes[] = { DIJOFS_X, DIJOFS_Y };  // エフェクト軸
      LONG Direction[] = { 1, 1 };            // エフェクト方向
      DirectInputEffect.cAxes = 2;
      DirectInputEffect.rgdwAxes = Axes;
      DirectInputEffect.rglDirection = Direction;
      //  周期設定
      DirectInputEffect.lpEnvelope = nullptr; // エンベロープ構造体
      DirectInputEffect.cbTypeSpecificParams = sizeof(diPeriodic); // エフェクト周期構造体のサイズ
      DirectInputEffect.lpvTypeSpecificParams = &diPeriodic; // エフェクト周期構造体

      pDirectInputData.pJoyStick->CreateEffect(GUID_Square, &DirectInputEffect, &pDirectInputData.pEffect, nullptr);
    }

    //  ジョイスティック初期化終了
    pDirectInputData.pJoyStick->Acquire();
    ++CreateDeviceNum;
  }
}

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void*)
{
  //  XInput判別用関数
  auto isXInput = [&](const GUID& GuidProductFromDirectInput)->bool
  {
    for (int i = 0, size = XInputList.size(); i < size; ++i)
    {
      //  XInputである
      if (XInputList[i] == GuidProductFromDirectInput.Data1)
      {
        return true;
      }
    }

    //  XInputではない
    return false;
  };

  //  XInputの時次へ
  if (isXInput(pdidInstance->guidProduct))
  {
    return DIENUM_CONTINUE;
  }

  //  DirectInputを作成
  CreateDirectInputDevice(pdidInstance->guidProduct);

  //  次へ
  return DIENUM_CONTINUE;
}

//struct IGamepad::Impl
//{
//  static constexpr int kButtonNum = 32; //  DirectInputの最大ボタン数
//private:
//  struct Status
//  {
//    bool isConnect_ = true;
//    //  入力状態
//    InputState InputStatus_[kButtonNum];
//    //  左のアナログスティックの入力状態
//    hdx::float2 LeftStick_;
//    //  右のアナログスティックの入力状態
//    hdx::float2 RightStick_;
//    //  左のトリガーの入力状態
//    float LeftTrigger_;
//    //  右のトリガーの入力状態
//    float RightTrigger_;
//  };
//public:
//  const int DirectInputNum_;  //  DirectInputゲームパッドの数
//  const int XInputNum_;       //  XInputゲームパッドの数
//  const int GamepadNum_;      //  ゲームパッドの数
//public:
//  Microsoft::WRL::ComPtr<IDirectInput8W> pDirectInput_;       //  DirectInput
//  LPDIRECTINPUTDEVICE8* pJoySticks_;  //  ジョイスティック
//  LPDIRECTINPUTEFFECT* pEffects_;     //  振動エフェクト
//public:
//  Status* Status_;
//public:
//  std::vector<LONG> XInputList_;  //  XInput判別用リスト
//public:
//  Impl(int _DirectInputNum, int _XInputNum)
//    : DirectInputNum_(_DirectInputNum), XInputNum_(_XInputNum), GamepadNum_(_DirectInputNum + _XInputNum),
//    pJoySticks_(new LPDIRECTINPUTDEVICE8[_DirectInputNum]), pEffects_(new LPDIRECTINPUTEFFECT[_DirectInputNum]),
//    Status_(new Status[_DirectInputNum])
//  {
//    HRESULT hr = S_OK;
//
//    //  繋がっているXInputを検索
//    if (_XInputNum > 0)
//    {
//      class BString
//      {
//      public:
//        BSTR    m_bstr;
//        BString(TCHAR* pStr) { if ((m_bstr = SysAllocString((OLECHAR*)pStr)) == NULL) throw - 1; }
//        ~BString() { if (m_bstr != NULL) SysFreeString(m_bstr); }
//        operator BSTR&() { return m_bstr; }
//      };
//
//      static constexpr int kDeviceNum = 20;
//
//      // CoInit if needed
//      const bool bCleanupCOM = SUCCEEDED(CoInitialize(nullptr));
//
//      bool isXinput = false;
//
//      // Create WMI
//      Microsoft::WRL::ComPtr<IWbemLocator> pIWbemLocator;
//      hr = CoCreateInstance(__uuidof(WbemLocator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator), (LPVOID*)pIWbemLocator.GetAddressOf());
//      if (SUCCEEDED(hr))
//      {
//        // Connect to WMI
//        BString bstrNamespace(L"\\\\.\\root\\cimv2");
//
//        Microsoft::WRL::ComPtr<IWbemServices> pIWbemServices;
//        hr = pIWbemLocator->ConnectServer(bstrNamespace, nullptr, nullptr, 0L, 0L, nullptr, nullptr, pIWbemServices.GetAddressOf());
//        if (SUCCEEDED(hr))
//        {
//          // Switch security level to IMPERSONATE.
//          BString bstrClassName(L"Win32_PNPEntity");
//          Microsoft::WRL::ComPtr<IEnumWbemClassObject> pEnumDevices;
//          CoSetProxyBlanket(pIWbemServices.Get(), RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
//          hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, nullptr, pEnumDevices.GetAddressOf());
//
//          if (SUCCEEDED(hr))
//          {
//            const LPCWSTR bstrDeviceID = L"DeviceID";
//
//            // Loop over all devices
//            for (; !isXinput;)
//            {
//              // Get 20 at a time
//              DWORD dwReturned = 0;
//
//              IWbemClassObject* pDevices[kDeviceNum] = { 0 };
//              hr = pEnumDevices->Next(10000, kDeviceNum, pDevices, &dwReturned);
//              if (FAILED(hr) || dwReturned == 0) break;
//
//              for (DWORD i = 0; i < dwReturned; ++i)
//              {
//                // For each device, get its device ID
//                VARIANT var;
//                hr = pDevices[i]->Get(bstrDeviceID, 0L, &var, nullptr, nullptr);
//                if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != nullptr)
//                {
//                  // Check if the device ID contains "IG_".  If it does, then it's an XInput device
//                  // This information can not be found from DirectInput
//                  if (wcsstr(var.bstrVal, L"IG_"))
//                  {
//                    DWORD dwPid, dwVid;
//                    WCHAR *strVid, *strPid;
//
//                    // If it does, then get the VID/PID from var.bstrVal
//                    dwVid = dwVid = 0;
//                    strVid = wcsstr(var.bstrVal, L"VID_");
//                    strPid = wcsstr(var.bstrVal, L"PID_");
//                    if (strVid && swscanf_s(strVid, L"VID_%4X", &dwVid) != 1) dwVid = 0;
//                    if (strPid && swscanf_s(strPid, L"PID_%4X", &dwPid) != 1) dwPid = 0;
//
//                    //  XInputとして既に保存されていた場合true
//                    auto CheckList = [this](LONG _XInputValue)->bool
//                    {
//                      for (int i = 0, size = XInputList_.size(); i < size; ++i)
//                      {
//                        if (XInputList_[i] == _XInputValue)
//                        {
//                          return true;
//                        }
//                      }
//
//                      return false;
//                    };
//
//                    const LONG XInputValue = MAKELONG(dwVid, dwPid);
//
//                    if (!CheckList(XInputValue))
//                    {
//                      XInputList_.push_back(XInputValue);
//                    }
//                  }
//                }
//                SAFE_RELEASE(pDevices[i]);
//              }
//            }
//          }
//        }
//      }
//
//      if (bCleanupCOM)
//      {
//        CoUninitialize();
//      }
//    }
//
//    //  ボタンを初期化
//    for (int i = 0; i < DirectInputNum_; ++i)
//    {
//      for (int j = 0; j < kButtonNum; ++j)
//      {
//        Status_[i].InputStatus_[j] = InputState::Released;
//      }
//    }
//  }
//  ~Impl()
//  {
//    for (int i = 0; i < DirectInputNum_; ++i)
//    {
//      if (pJoySticks_[i])
//      {
//        pJoySticks_[i]->Unacquire();
//      }
//
//      SAFE_RELEASE(pJoySticks_[i]);
//    }
//
//    SAFE_DELETE_ARRAY(pJoySticks_);
//    SAFE_DELETE_ARRAY(pEffects_);
//
//    //SAFE_RELEASE(pDirectInput_);
//    SAFE_DELETE_ARRAY(Status_);
//  }
//public:
//  void Initiliaze()
//  {
//    HRESULT hr = S_OK;
//
//    //  DirectInputを作成
//    hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDirectInput_, NULL);
//    _ASSERT_EXPR(SUCCEEDED(hr), L"DirectInput8Create");
//
//    //  Joystickを作成
//    hr = pDirectInput_->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);
//    _ASSERT_EXPR(SUCCEEDED(hr), L"EnumDevices");
//  }
//};


//--------------------------------------------------

//  作成
IGamepad::IGamepad()
{
  //  接続されているXInputコントローラの数を取得
  {
    for (; XInputNum < XUSER_MAX_COUNT; ++XInputNum)
    {
      XINPUT_STATE State;

      //  取得失敗の時終了
      if (XInputGetState(XInputNum, &State) == ERROR_DEVICE_NOT_CONNECTED)
      {
        break;
      }
    }
  }

  //  接続されているジョイスティックの数を取得
  {
    JOYINFOEX JoyInfoEx;
    JoyInfoEx.dwSize = sizeof(JOYINFOEX);
    JoyInfoEx.dwFlags = JOY_RETURNALL;

    for (UINT i = 0, Num = joyGetNumDevs(); i < Num; ++i)
    {
      if (JOYERR_NOERROR == joyGetPosEx(i, &JoyInfoEx))
      {
        ++DirectInputNum;
      }
    }
  }

  ControllerNum = DirectInputNum;

  //  XInputコントローラの数を減らす
  DirectInputNum -= XInputNum;

  if (ControllerNum > kControllerNum)
  {
    DirectInputNum -= ControllerNum - kControllerNum;
    ControllerNum = kControllerNum;
  }

  pDirectInputDatas = std::make_unique<DirectInputData[]>(ControllerNum);

  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    //  繋がっているXInputを検索
    if (XInputNum > 0)
    {
      class BString
      {
      public:
        BSTR    m_bstr;
        BString(TCHAR* pStr) { if ((m_bstr = SysAllocString((OLECHAR*)pStr)) == NULL) throw - 1; }
        ~BString() { if (m_bstr != NULL) SysFreeString(m_bstr); }
        operator BSTR&() { return m_bstr; }
      };

      static constexpr int kDeviceNum = 20;

      // CoInit if needed
      const bool bCleanupCOM = SUCCEEDED(CoInitialize(nullptr));

      // Create WMI
      Microsoft::WRL::ComPtr<IWbemLocator> pIWbemLocator;
      hr = CoCreateInstance(__uuidof(WbemLocator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator), (LPVOID*)pIWbemLocator.GetAddressOf());

      if (SUCCEEDED(hr))
      {
        // Connect to WMI
        BString bstrNamespace(L"\\\\.\\root\\cimv2");

        Microsoft::WRL::ComPtr<IWbemServices> pIWbemServices;
        hr = pIWbemLocator->ConnectServer(bstrNamespace, nullptr, nullptr, 0L, 0L, nullptr, nullptr, pIWbemServices.GetAddressOf());
        if (SUCCEEDED(hr))
        {
          // Switch security level to IMPERSONATE.
          BString bstrClassName(L"Win32_PNPEntity");
          Microsoft::WRL::ComPtr<IEnumWbemClassObject> pEnumDevices;
          CoSetProxyBlanket(pIWbemServices.Get(), RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
          hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, nullptr, pEnumDevices.GetAddressOf());

          if (SUCCEEDED(hr))
          {
            const LPCWSTR bstrDeviceID = L"DeviceID";

            // Loop over all devices
            while (true)
            {
              // Get 20 at a time
              DWORD dwReturned = 0;

              Microsoft::WRL::ComPtr<IWbemClassObject> pDevices[kDeviceNum];
              hr = pEnumDevices->Next(10000, kDeviceNum, pDevices[0].GetAddressOf(), &dwReturned);
              if (FAILED(hr) || dwReturned == 0) break;

              for (DWORD i = 0; i < dwReturned; ++i)
              {
                // For each device, get its device ID
                VARIANT var;
                hr = pDevices[i]->Get(bstrDeviceID, 0L, &var, nullptr, nullptr);
                if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != nullptr)
                {
                  // Check if the device ID contains "IG_".  If it does, then it's an XInput device
                  // This information can not be found from DirectInput
                  if (wcsstr(var.bstrVal, L"IG_"))
                  {
                    DWORD dwPid, dwVid;
                    WCHAR *strVid, *strPid;

                    // If it does, then get the VID/PID from var.bstrVal
                    dwVid = dwVid = 0;
                    strVid = wcsstr(var.bstrVal, L"VID_");
                    strPid = wcsstr(var.bstrVal, L"PID_");
                    if (strVid && swscanf_s(strVid, L"VID_%4X", &dwVid) != 1) dwVid = 0;
                    if (strPid && swscanf_s(strPid, L"PID_%4X", &dwPid) != 1) dwPid = 0;

                    //  XInputとして既に保存されていた場合true
                    auto CheckList = [&](LONG _XInputValue)->bool
                    {
                      for (int i = 0, size = XInputList.size(); i < size; ++i)
                      {
                        if (XInputList[i] == _XInputValue)
                        {
                          return true;
                        }
                      }

                      return false;
                    };

                    const LONG XInputValue = MAKELONG(dwVid, dwPid);

                    if (CheckList(XInputValue)) continue;

                    XInputList.push_back(XInputValue);
                  }
                }
              }
            }
          }
        }
      }

      if (bCleanupCOM)
      {
        CoUninitialize();
      }

      //  DirectInputを作成
      hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDirectInput, NULL);
      _ASSERT_EXPR(SUCCEEDED(hr), L"DirectInput8Create");

      //  Joystickを作成
      hr = pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);
      _ASSERT_EXPR(SUCCEEDED(hr), L"EnumDevices");
    }
  }
}

//  状態の更新
void IGamepad::Update()
{
  IXInput* pXInput = Engine::GetXInput();

  auto XInputUpdate = [&](int _Index)->void
  {
    Status& Status = Status_[_Index];

    Status.isConnect = pXInput->isConnect(_Index);
    Status.LeftStick = pXInput->GetLeftStick(_Index, 0.0f);
    Status.RightStick = pXInput->GetRightStick(_Index, 0.0f);
    Status.LeftTrigger = pXInput->GetLeftTrigger(_Index, 0.0f);
    Status.RightTrigger = pXInput->GetLeftTrigger(_Index, 0.0f);
  };

  auto DirectInputUpdate = [&](int _Index)->void
  {
    Status& Status = Status_[_Index];

    const int DirectInputIndex = _Index - XInputNum;

    DIJOYSTATE State;

    LPDIRECTINPUTDEVICE8& pJoyStick = pDirectInputDatas[_Index].pJoyStick;
    pJoyStick->Poll();

    if (pJoyStick->GetDeviceState(sizeof(DIJOYSTATE), &State) != DI_OK)
    {
      Status.isConnect = false;
      return;
    }

    Status.isConnect = true;

    Status.LeftStick = hdx::float2(static_cast<float>(State.lX), static_cast<float>(State.lY)) / kStickMaxValue;
    Status.RightStick = hdx::float2(static_cast<float>(State.lZ), static_cast<float>(State.lRz)) / kStickMaxValue;
    Status.LeftTrigger = State.lRx / static_cast<float>(kTriggerMaxValue);
    Status.RightTrigger = State.lRy / static_cast<float>(kTriggerMaxValue);

    for (int j = 0; j < kButtonNum; ++j)
    {
      Status.InputStatus[j].Update((State.rgbButtons[j] & 0x80) != 0);
    }
  };

  for (int i = 0; i < ControllerNum; ++i)
  {
    if (i < XInputNum)
    {
      XInputUpdate(i);
    }
    else
    {
      DirectInputUpdate(i);
    }
  }
}

//  解放
IGamepad::~IGamepad()
{
  for (int i = 0; i < ControllerNum; ++i)
  {
    if (pDirectInputDatas[i].pJoyStick)
    {
      pDirectInputDatas[i].pJoyStick->Unacquire();
    }
  }
}


//--------------------------------------------------

//  押されているならtrueを返す
bool IGamepad::Press(int _Number, int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->Press(_Number, _Index);
  }

  return Status_[_Index].InputStatus[_Number].Press();
}

//  押された瞬間ならtrueを返す
bool IGamepad::Pressed(int _Number, int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->Pressed(_Number, _Index);
  }

  return Status_[_Index].InputStatus[_Number].Pressed();
}

//  離された瞬間ならtrueを返す
bool IGamepad::Released(int _Number, int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->Released(_Number, _Index);
  }

  return Status_[_Index].InputStatus[_Number].Released();
}

//  押されていないならtrueを返す
bool IGamepad::Release(int _Number, int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->Release(_Number, _Index);
  }

  return Status_[_Index].InputStatus[_Number].Release();
}

//  接続されているか確認
bool IGamepad::isConnect(int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->isConnect(_Index);
  }

  return Status_[_Index].isConnect;
}

//  何かのボタンが押されていればtrueを返す
bool IGamepad::AnyButtonPress(int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->AnyButtonPress(_Index);
  }

  for (int i = 0; i < kButtonNum; ++i)
  {
    if (Press(i, _Index))
    {
      return true;
    }
  }

  //  何も押されていない
  return false;
}

//  何かのボタンが押されたならtrueを返す
bool IGamepad::AnyButtonPressed(int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->AnyButtonPressed(_Index);
  }

  for (int i = 0; i < kButtonNum; ++i)
  {
    if (Pressed(i, _Index))
    {
      return true;
    }
  }

  //  何も押されていない
  return false;
}

//  何かのボタンが離されたならtrueを返す
bool IGamepad::AnyButtonReleased(int _Index)const
{
  if (_Index < XInputNum)
  {
    return Engine::GetXInput()->AnyButtonReleased(_Index);
  }

  for (int i = 0; i < kButtonNum; ++i)
  {
    if (Released(i, _Index))
    {
      return true;
    }
  }

  //  何も押されていない
  return false;
}

//  ボタンを取得
hdx::Button IGamepad::GetButton(int _Index, int _Number)const
{
  //  XInputの入力を返す
  if (_Index < XInputNum)
  {
    if (IXInput::kButtonNum < _Number)
    {
      return hdx::Button();
    }
    else
    {
      return hdx::Button(hdx::InputDevice::XInput, _Number, _Index);
    }
  }

  return hdx::Button(hdx::InputDevice::Gamepad, _Number, _Index);
}

inline hdx::float2 GetStick(hdx::float2 _Value, float _DeadZone)
{
  if (hdx::Math::GetAbsoluteValue(_Value.X) < _DeadZone) _Value.X = 0.0f;
  if (hdx::Math::GetAbsoluteValue(_Value.Y) < _DeadZone) _Value.Y = 0.0f;

  return _Value;
}

//  左スティックの入力状態を取得
hdx::float2 IGamepad::GetLeftStick(int _Index, float _DeadZone)const
{
  return GetStick(Status_[_Index].LeftStick, _DeadZone);
}

//  右スティックの入力状態を取得
hdx::float2 IGamepad::GetRightStick(int _Index, float _DeadZone)const
{
  return GetStick(Status_[_Index].RightStick, _DeadZone);
}

inline float GetTrigger(float _Value, float _DeadZone)
{
  if (_Value < _DeadZone) _Value = 0.0f;

  return _Value;
}

//  左トリガーの入力状態を取得
float IGamepad::GetLeftTrigger(int _Index, float _DeadZone)const
{
  return GetTrigger(Status_[_Index].LeftTrigger, _DeadZone);
}

//  右トリガーの入力状態を取得
float IGamepad::GetRightTrigger(int _Index, float _DeadZone)const
{
  return GetTrigger(Status_[_Index].RightTrigger, _DeadZone);
}

//  コントローラを振動させます
void IGamepad::SetVibration(int _Index, float _Speed)const
{
  //  XInputを振動させる
  if (_Index < XInputNum)
  {
    Engine::GetXInput()->SetVibration(_Index, _Speed);
    return;
  }

  //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
  //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Start(1, 0);
}

//  コントローラの振動を止めます
void IGamepad::StopVibration(int _Index)const
{
  //  XInputの振動を止める
  if (_Index < XInputNum)
  {
    Engine::GetXInput()->StopVibration(_Index);
    return;
  }

  //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
  //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Stop();
}
