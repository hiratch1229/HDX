#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/Input/InputState.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>
#include <HDX/Input/XInput/IXInput.hpp>

#include <HDX/Math.hpp>
#include <HDX/Macro.hpp>

#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>
#include <wbemidl.h>
#include <wrl.h>
#include <vector>

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void*)
{
  //  DirectInputを作成
  GetGamepad()->CreateDirectInputDevice(pdidInstance->guidProduct);

  //  次へ
  return DIENUM_CONTINUE;
}

namespace detail
{
  struct IGamepad::Impl
  {
    static constexpr int kButtonNum = 32; //  DirectInputの最大ボタン数
  private:
    struct Status
    {
      bool isConnect_ = true;
      //  入力状態
      InputState InputStatus_[kButtonNum];
      //  左のアナログスティックの入力状態
      hdx::float2 LeftStick_;
      //  右のアナログスティックの入力状態
      hdx::float2 RightStick_;
      //  左のトリガーの入力状態
      float LeftTrigger_;
      //  右のトリガーの入力状態
      float RightTrigger_;
    };
  public:
    static constexpr int kStickMaxValue = 10000;
    static constexpr int kTriggerMaxValue = 65535;
  public:
    const int DirectInputNum_;  //  DirectInputゲームパッドの数
    const int XInputNum_;       //  XInputゲームパッドの数
    const int GamepadNum_;      //  ゲームパッドの数
  public:
    Microsoft::WRL::ComPtr<IDirectInput8W> pDirectInput_;       //  DirectInput
    LPDIRECTINPUTDEVICE8* pJoySticks_;  //  ジョイスティック
    LPDIRECTINPUTEFFECT* pEffects_;     //  振動エフェクト
  public:
    Status* Status_;
  public:
    std::vector<LONG> XInputList_;  //  XInput判別用リスト
  public:
    Impl(int _DirectInputNum, int _XInputNum)
      : DirectInputNum_(_DirectInputNum), XInputNum_(_XInputNum), GamepadNum_(_DirectInputNum + _XInputNum),
      pJoySticks_(new LPDIRECTINPUTDEVICE8[_DirectInputNum]), pEffects_(new LPDIRECTINPUTEFFECT[_DirectInputNum]),
      Status_(new Status[_DirectInputNum])
    {
      HRESULT hr = S_OK;

      //  繋がっているXInputを検索
      if (_XInputNum > 0)
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

        bool isXinput = false;

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
              for (; !isXinput;)
              {
                // Get 20 at a time
                DWORD dwReturned = 0;

                IWbemClassObject* pDevices[kDeviceNum] = { 0 };
                hr = pEnumDevices->Next(10000, kDeviceNum, pDevices, &dwReturned);
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
                      auto CheckList = [this](LONG _XInputValue)->bool
                      {
                        for (int i = 0, size = XInputList_.size(); i < size; ++i)
                        {
                          if (XInputList_[i] == _XInputValue)
                          {
                            return true;
                          }
                        }

                        return false;
                      };

                      const LONG XInputValue = MAKELONG(dwVid, dwPid);

                      if (!CheckList(XInputValue))
                      {
                        XInputList_.push_back(XInputValue);
                      }
                    }
                  }
                  SAFE_RELEASE(pDevices[i]);
                }
              }
            }
          }
        }

        if (bCleanupCOM)
        {
          CoUninitialize();
        }
      }

      //  ボタンを初期化
      for (int i = 0; i < DirectInputNum_; ++i)
      {
        for (int j = 0; j < kButtonNum; ++j)
        {
          Status_[i].InputStatus_[j] = InputState::Released;
        }
      }
    }
    ~Impl()
    {
      for (int i = 0; i < DirectInputNum_; ++i)
      {
        if (pJoySticks_[i])
        {
          pJoySticks_[i]->Unacquire();
        }

        SAFE_RELEASE(pJoySticks_[i]);
      }

      SAFE_DELETE_ARRAY(pJoySticks_);
      SAFE_DELETE_ARRAY(pEffects_);

      //SAFE_RELEASE(pDirectInput_);
      SAFE_DELETE_ARRAY(Status_);
    }
  public:
    void Initiliaze()
    {
      HRESULT hr = S_OK;

      //  DirectInputを作成
      hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDirectInput_, NULL);
      _ASSERT_EXPR(SUCCEEDED(hr), L"DirectInput8Create");

      //  Joystickを作成
      hr = pDirectInput_->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);
      _ASSERT_EXPR(SUCCEEDED(hr), L"EnumDevices");
    }
  };


  //--------------------------------------------------

  //  作成
  IGamepad::IGamepad()
  {
    UINT XInputNum = 0;

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

    UINT DirectInputNum = 0;

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

    //  XInputコントローラの数を減らす
    DirectInputNum -= XInputNum;

    //  コントローラを初期化
    pImpl_ = new Impl(DirectInputNum, XInputNum);
  }

  //  初期化
  void IGamepad::Initialize()
  {
    pImpl_->Initiliaze();
  }

  //  状態の更新
  void IGamepad::Update()
  {
    for (int i = 0; i < pImpl_->DirectInputNum_; ++i)
    {
      DIJOYSTATE State;

      pImpl_->pJoySticks_[i]->Poll();
      //  接続されていない時
      if (pImpl_->pJoySticks_[i]->GetDeviceState(sizeof(DIJOYSTATE), &State) != DI_OK)
      {
        pImpl_->Status_[i].isConnect_ = false;
        continue;
      }

      pImpl_->Status_[i].isConnect_ = true;

      pImpl_->Status_[i].LeftStick_ = hdx::float2(static_cast<float>(State.lX), static_cast<float>(State.lY)) / static_cast<float>(pImpl_->kStickMaxValue);
      pImpl_->Status_[i].RightStick_ = hdx::float2(static_cast<float>(State.lZ), static_cast<float>(State.lRz)) / static_cast<float>(pImpl_->kStickMaxValue);
      pImpl_->Status_[i].LeftTrigger_ = State.lRx / static_cast<float>(pImpl_->kTriggerMaxValue);
      pImpl_->Status_[i].RightTrigger_ = State.lRy / static_cast<float>(pImpl_->kTriggerMaxValue);

      for (int j = 0; j < pImpl_->kButtonNum; ++j)
      {
        InputState& InputState = pImpl_->Status_[i].InputStatus_[j];

        //  状態の補間
        {
          //  押した瞬間
          if (InputState == InputState::Pressed)
          {
            InputState = InputState::Press;
          }
          //  離した瞬間
          else if (InputState == InputState::Released)
          {
            InputState = InputState::Release;
          }
        }

        //  状態を取得
        {
          //  押しているならtrue
          if (State.rgbButtons[j] & 0x80)
          {
            //  押した瞬間
            if (InputState == InputState::Release)
            {
              InputState = InputState::Pressed;
            }
          }
          else
          {
            //  離した瞬間
            if (InputState == InputState::Press)
            {
              InputState = InputState::Released;
            }
          }
        }
      }
    }
  }

  //  解放
  IGamepad::~IGamepad()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  //  DirectInputコントローラを作成
  void IGamepad::CreateDirectInputDevice(const GUID& GuidProductFromDirectInput)
  {
    //  作成済みジョイスティック数
    static int CreateDeviceNum = 0;

    //  XInput判別用関数
    auto isXInput = [this](const GUID& GuidProductFromDirectInput)->bool
    {
      for (int i = 0, size = pImpl_->XInputList_.size(); i < size; ++i)
      {
        //  XInputである
        if (pImpl_->XInputList_[i] == GuidProductFromDirectInput.Data1)
        {
          return true;
        }
      }

      //  XInputではない
      return false;
    };

    //  XInputで無い時
    if (!isXInput(GuidProductFromDirectInput))
    {
      //  ジョイスティックを作成
      pImpl_->pDirectInput_->CreateDevice(GuidProductFromDirectInput, &pImpl_->pJoySticks_[CreateDeviceNum], NULL);
      pImpl_->pJoySticks_[CreateDeviceNum]->SetDataFormat(&c_dfDIJoystick);
      pImpl_->pJoySticks_[CreateDeviceNum]->SetCooperativeLevel(GetSystem()->GetHWND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

      // 軸の値の範囲を設定
      DIPROPRANGE DirectInputPropatyRange;
      DirectInputPropatyRange.diph.dwSize = sizeof(DirectInputPropatyRange);
      DirectInputPropatyRange.diph.dwHeaderSize = sizeof(DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_X;
      DirectInputPropatyRange.diph.dwHow = DIPH_BYOFFSET;
      DirectInputPropatyRange.lMin = -pImpl_->kStickMaxValue;
      DirectInputPropatyRange.lMax = +pImpl_->kStickMaxValue;
      pImpl_->pJoySticks_[CreateDeviceNum]->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_Y;
      pImpl_->pJoySticks_[CreateDeviceNum]->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_Z;
      pImpl_->pJoySticks_[CreateDeviceNum]->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_RZ;
      pImpl_->pJoySticks_[CreateDeviceNum]->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);

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

        //	トリガー設定
        DirectInputEffect.dwTriggerButton = DIEB_NOTRIGGER;
        DirectInputEffect.dwTriggerRepeatInterval = 0;
        //	エフェクト軸設定
        DirectInputEffect.dwFlags |= DIEFF_POLAR;
        DWORD Axes[] = { DIJOFS_X, DIJOFS_Y };  // エフェクト軸
        LONG Direction[] = { 1, 1 };            // エフェクト方向
        DirectInputEffect.cAxes = 2;
        DirectInputEffect.rgdwAxes = Axes;
        DirectInputEffect.rglDirection = Direction;
        //	周期設定
        DirectInputEffect.lpEnvelope = NULL; // エンベロープ構造体
        DirectInputEffect.cbTypeSpecificParams = sizeof(diPeriodic); // エフェクト周期構造体のサイズ
        DirectInputEffect.lpvTypeSpecificParams = &diPeriodic; // エフェクト周期構造体

        pImpl_->pJoySticks_[CreateDeviceNum]->CreateEffect(GUID_Square, &DirectInputEffect, &pImpl_->pEffects_[CreateDeviceNum], NULL);
      }

      //  ジョイスティック初期化終了
      pImpl_->pJoySticks_[CreateDeviceNum]->Acquire();
      ++CreateDeviceNum;
    }
  }


  //--------------------------------------------------

  //  押されているならtrueを返す
  bool IGamepad::Press(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Press(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Press || pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Pressed;
  }

  //  押された瞬間ならtrueを返す
  bool IGamepad::Pressed(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Pressed(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Pressed;
  }

  //  離された瞬間ならtrueを返す
  bool IGamepad::Released(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Released(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Released;
  }

  //  押されていないならtrueを返す
  bool IGamepad::Release(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Release(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Release || pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Released;
  }

  //  何かのボタンが押されていればtrueを返す
  bool IGamepad::AnyButtonPress(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->AnyButtonPress(_Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    for (int i = 0; i < pImpl_->kButtonNum; ++i)
    {
      if (Press(i, DirectInputIndex))
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
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->AnyButtonPressed(_Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    for (int i = 0; i < pImpl_->kButtonNum; ++i)
    {
      if (Pressed(i, DirectInputIndex))
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
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->AnyButtonReleased(_Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    for (int i = 0; i < pImpl_->kButtonNum; ++i)
    {
      if (Released(i, DirectInputIndex))
      {
        return true;
      }
    }

    //  何も離されていない
    return false;
  }

  hdx::Button IGamepad::GetButton(int _Index, int _Number)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_
      || _Number < 0 || _Number > pImpl_->kButtonNum) return hdx::Button();

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      if (detail::IXInput::kButtonNum < _Number)
      {
        return hdx::Button();
      }
      else
      {
        return hdx::Button(detail::InputDevice::XInput, _Number, _Index);
      }
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return hdx::Button(detail::InputDevice::Gamepad, _Number, _Index);
  }

  //  左スティックの入力状態を取得
  hdx::float2 IGamepad::GetLeftStick(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return hdx::float2(0.0f);

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->GetLeftStick(_Index, _DeadZone);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    hdx::float2 Value = pImpl_->Status_[DirectInputIndex].LeftStick_;

    if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
    if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

    return Value;
  }

  //  右スティックの入力状態を取得
  hdx::float2 IGamepad::GetRightStick(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return hdx::float2(0.0f);

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->GetRightStick(_Index, _DeadZone);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    hdx::float2 Value = pImpl_->Status_[DirectInputIndex].RightStick_;

    if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
    if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

    return Value;
  }

  //  左トリガーの入力状態を取得
  float IGamepad::GetLeftTrigger(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return 0.0f;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->GetLeftTrigger(_Index, _DeadZone);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    float Value = pImpl_->Status_[DirectInputIndex].LeftTrigger_;

    if (hdx::Math::GetAbsoluteValue(Value) < _DeadZone) Value = 0.0f;

    return Value;
  }

  //  右トリガーの入力状態を取得
  float IGamepad::GetRightTrigger(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return 0.0f;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->GetRightTrigger(_Index, _DeadZone);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    float Value = pImpl_->Status_[DirectInputIndex].RightTrigger_;

    if (hdx::Math::GetAbsoluteValue(Value) < _DeadZone) Value = 0.0f;

    return Value;
  }

  //  接続されているか確認
  bool IGamepad::isConnect(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInputの入力を返す
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->isConnect(_Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].isConnect_;
  }

  //  コントローラを振動させます
  void IGamepad::SetVibration(int _Index, float _Speed)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return;

    //  XInputを振動させる
    if (_Index < pImpl_->XInputNum_)
    {
      GetXInput()->SetVibration(_Index, _Speed);
      return;
    }

    //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Start(1, 0);
  }

  //  コントローラの振動を止めます
  void IGamepad::StopVibration(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return;

    //  XInputの振動を止める
    if (_Index < pImpl_->XInputNum_)
    {
      GetXInput()->StopVibration(_Index);
      return;
    }

    //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Stop();
  }
}
