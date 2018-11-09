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
  //  DirectInput���쐬
  GetGamepad()->CreateDirectInputDevice(pdidInstance->guidProduct);

  //  ����
  return DIENUM_CONTINUE;
}

namespace detail
{
  struct IGamepad::Impl
  {
    static constexpr int kButtonNum = 32; //  DirectInput�̍ő�{�^����
  private:
    struct Status
    {
      bool isConnect_ = true;
      //  ���͏��
      InputState InputStatus_[kButtonNum];
      //  ���̃A�i���O�X�e�B�b�N�̓��͏��
      hdx::float2 LeftStick_;
      //  �E�̃A�i���O�X�e�B�b�N�̓��͏��
      hdx::float2 RightStick_;
      //  ���̃g���K�[�̓��͏��
      float LeftTrigger_;
      //  �E�̃g���K�[�̓��͏��
      float RightTrigger_;
    };
  public:
    static constexpr int kStickMaxValue = 10000;
    static constexpr int kTriggerMaxValue = 65535;
  public:
    const int DirectInputNum_;  //  DirectInput�Q�[���p�b�h�̐�
    const int XInputNum_;       //  XInput�Q�[���p�b�h�̐�
    const int GamepadNum_;      //  �Q�[���p�b�h�̐�
  public:
    Microsoft::WRL::ComPtr<IDirectInput8W> pDirectInput_;       //  DirectInput
    LPDIRECTINPUTDEVICE8* pJoySticks_;  //  �W���C�X�e�B�b�N
    LPDIRECTINPUTEFFECT* pEffects_;     //  �U���G�t�F�N�g
  public:
    Status* Status_;
  public:
    std::vector<LONG> XInputList_;  //  XInput���ʗp���X�g
  public:
    Impl(int _DirectInputNum, int _XInputNum)
      : DirectInputNum_(_DirectInputNum), XInputNum_(_XInputNum), GamepadNum_(_DirectInputNum + _XInputNum),
      pJoySticks_(new LPDIRECTINPUTDEVICE8[_DirectInputNum]), pEffects_(new LPDIRECTINPUTEFFECT[_DirectInputNum]),
      Status_(new Status[_DirectInputNum])
    {
      HRESULT hr = S_OK;

      //  �q�����Ă���XInput������
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

                      //  XInput�Ƃ��Ċ��ɕۑ�����Ă����ꍇtrue
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

      //  �{�^����������
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

      //  DirectInput���쐬
      hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDirectInput_, NULL);
      _ASSERT_EXPR(SUCCEEDED(hr), L"DirectInput8Create");

      //  Joystick���쐬
      hr = pDirectInput_->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);
      _ASSERT_EXPR(SUCCEEDED(hr), L"EnumDevices");
    }
  };


  //--------------------------------------------------

  //  �쐬
  IGamepad::IGamepad()
  {
    UINT XInputNum = 0;

    //  �ڑ�����Ă���XInput�R���g���[���̐����擾
    {
      for (; XInputNum < XUSER_MAX_COUNT; ++XInputNum)
      {
        XINPUT_STATE State;

        //  �擾���s�̎��I��
        if (XInputGetState(XInputNum, &State) == ERROR_DEVICE_NOT_CONNECTED)
        {
          break;
        }
      }
    }

    UINT DirectInputNum = 0;

    //  �ڑ�����Ă���W���C�X�e�B�b�N�̐����擾
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

    //  XInput�R���g���[���̐������炷
    DirectInputNum -= XInputNum;

    //  �R���g���[����������
    pImpl_ = new Impl(DirectInputNum, XInputNum);
  }

  //  ������
  void IGamepad::Initialize()
  {
    pImpl_->Initiliaze();
  }

  //  ��Ԃ̍X�V
  void IGamepad::Update()
  {
    for (int i = 0; i < pImpl_->DirectInputNum_; ++i)
    {
      DIJOYSTATE State;

      pImpl_->pJoySticks_[i]->Poll();
      //  �ڑ�����Ă��Ȃ���
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

        //  ��Ԃ̕��
        {
          //  �������u��
          if (InputState == InputState::Pressed)
          {
            InputState = InputState::Press;
          }
          //  �������u��
          else if (InputState == InputState::Released)
          {
            InputState = InputState::Release;
          }
        }

        //  ��Ԃ��擾
        {
          //  �����Ă���Ȃ�true
          if (State.rgbButtons[j] & 0x80)
          {
            //  �������u��
            if (InputState == InputState::Release)
            {
              InputState = InputState::Pressed;
            }
          }
          else
          {
            //  �������u��
            if (InputState == InputState::Press)
            {
              InputState = InputState::Released;
            }
          }
        }
      }
    }
  }

  //  ���
  IGamepad::~IGamepad()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  //  DirectInput�R���g���[�����쐬
  void IGamepad::CreateDirectInputDevice(const GUID& GuidProductFromDirectInput)
  {
    //  �쐬�ς݃W���C�X�e�B�b�N��
    static int CreateDeviceNum = 0;

    //  XInput���ʗp�֐�
    auto isXInput = [this](const GUID& GuidProductFromDirectInput)->bool
    {
      for (int i = 0, size = pImpl_->XInputList_.size(); i < size; ++i)
      {
        //  XInput�ł���
        if (pImpl_->XInputList_[i] == GuidProductFromDirectInput.Data1)
        {
          return true;
        }
      }

      //  XInput�ł͂Ȃ�
      return false;
    };

    //  XInput�Ŗ�����
    if (!isXInput(GuidProductFromDirectInput))
    {
      //  �W���C�X�e�B�b�N���쐬
      pImpl_->pDirectInput_->CreateDevice(GuidProductFromDirectInput, &pImpl_->pJoySticks_[CreateDeviceNum], NULL);
      pImpl_->pJoySticks_[CreateDeviceNum]->SetDataFormat(&c_dfDIJoystick);
      pImpl_->pJoySticks_[CreateDeviceNum]->SetCooperativeLevel(GetSystem()->GetHWND(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

      // ���̒l�͈̔͂�ݒ�
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

      //  �U����ݒ�
      {
        // �G�t�F�N�g�����ݒ�
        DIPERIODIC diPeriodic;
        diPeriodic.dwMagnitude = DI_FFNOMINALMAX;
        diPeriodic.lOffset = 0;
        diPeriodic.dwPhase = 0;
        diPeriodic.dwPeriod = (DWORD)(0.5f * DI_SECONDS);

        // �U���G�t�F�N�g�ݒ�
        DIEFFECT DirectInputEffect{};
        DirectInputEffect.dwSize = sizeof(DIEFFECT);
        DirectInputEffect.dwFlags = DIEFF_OBJECTOFFSETS;
        DirectInputEffect.dwDuration = 0;
        DirectInputEffect.dwSamplePeriod = 0;
        DirectInputEffect.dwGain = DI_FFNOMINALMAX;

        //	�g���K�[�ݒ�
        DirectInputEffect.dwTriggerButton = DIEB_NOTRIGGER;
        DirectInputEffect.dwTriggerRepeatInterval = 0;
        //	�G�t�F�N�g���ݒ�
        DirectInputEffect.dwFlags |= DIEFF_POLAR;
        DWORD Axes[] = { DIJOFS_X, DIJOFS_Y };  // �G�t�F�N�g��
        LONG Direction[] = { 1, 1 };            // �G�t�F�N�g����
        DirectInputEffect.cAxes = 2;
        DirectInputEffect.rgdwAxes = Axes;
        DirectInputEffect.rglDirection = Direction;
        //	�����ݒ�
        DirectInputEffect.lpEnvelope = NULL; // �G���x���[�v�\����
        DirectInputEffect.cbTypeSpecificParams = sizeof(diPeriodic); // �G�t�F�N�g�����\���̂̃T�C�Y
        DirectInputEffect.lpvTypeSpecificParams = &diPeriodic; // �G�t�F�N�g�����\����

        pImpl_->pJoySticks_[CreateDeviceNum]->CreateEffect(GUID_Square, &DirectInputEffect, &pImpl_->pEffects_[CreateDeviceNum], NULL);
      }

      //  �W���C�X�e�B�b�N�������I��
      pImpl_->pJoySticks_[CreateDeviceNum]->Acquire();
      ++CreateDeviceNum;
    }
  }


  //--------------------------------------------------

  //  ������Ă���Ȃ�true��Ԃ�
  bool IGamepad::Press(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Press(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Press || pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IGamepad::Pressed(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Pressed(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IGamepad::Released(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Released(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Released;
  }

  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool IGamepad::Release(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->Release(_Number, _Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Release || pImpl_->Status_[DirectInputIndex].InputStatus_[_Number] == InputState::Released;
  }

  //  �����̃{�^����������Ă����true��Ԃ�
  bool IGamepad::AnyButtonPress(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
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

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool IGamepad::AnyButtonPressed(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
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

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool IGamepad::AnyButtonReleased(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
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

    //  ����������Ă��Ȃ�
    return false;
  }

  hdx::Button IGamepad::GetButton(int _Index, int _Number)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_
      || _Number < 0 || _Number > pImpl_->kButtonNum) return hdx::Button();

    //  XInput�̓��͂�Ԃ�
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

  //  ���X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 IGamepad::GetLeftStick(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return hdx::float2(0.0f);

    //  XInput�̓��͂�Ԃ�
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

  //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 IGamepad::GetRightStick(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return hdx::float2(0.0f);

    //  XInput�̓��͂�Ԃ�
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

  //  ���g���K�[�̓��͏�Ԃ��擾
  float IGamepad::GetLeftTrigger(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return 0.0f;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->GetLeftTrigger(_Index, _DeadZone);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    float Value = pImpl_->Status_[DirectInputIndex].LeftTrigger_;

    if (hdx::Math::GetAbsoluteValue(Value) < _DeadZone) Value = 0.0f;

    return Value;
  }

  //  �E�g���K�[�̓��͏�Ԃ��擾
  float IGamepad::GetRightTrigger(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return 0.0f;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->GetRightTrigger(_Index, _DeadZone);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    float Value = pImpl_->Status_[DirectInputIndex].RightTrigger_;

    if (hdx::Math::GetAbsoluteValue(Value) < _DeadZone) Value = 0.0f;

    return Value;
  }

  //  �ڑ�����Ă��邩�m�F
  bool IGamepad::isConnect(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return false;

    //  XInput�̓��͂�Ԃ�
    if (_Index < pImpl_->XInputNum_)
    {
      return GetXInput()->isConnect(_Index);
    }

    const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    return pImpl_->Status_[DirectInputIndex].isConnect_;
  }

  //  �R���g���[����U�������܂�
  void IGamepad::SetVibration(int _Index, float _Speed)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return;

    //  XInput��U��������
    if (_Index < pImpl_->XInputNum_)
    {
      GetXInput()->SetVibration(_Index, _Speed);
      return;
    }

    //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Start(1, 0);
  }

  //  �R���g���[���̐U�����~�߂܂�
  void IGamepad::StopVibration(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > pImpl_->GamepadNum_) return;

    //  XInput�̐U�����~�߂�
    if (_Index < pImpl_->XInputNum_)
    {
      GetXInput()->StopVibration(_Index);
      return;
    }

    //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
    //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Stop();
  }
}
