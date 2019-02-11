#include "CGamepad.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/XInput/IXInput.hpp"
#include "Src/Misc.hpp"

#include "Include/Math.hpp"
#include "Include/Macro.hpp"

#include <Xinput.h>
#include <windows.h>
#include <wbemidl.h>

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void*)
{
  //  DirectInput���쐬
  Engine::Get<IGamepad>()->CreateDirectInputDevice(pdidInstance->guidProduct);

  //  ����
  return DIENUM_CONTINUE;
}

//  �쐬
CGamepad::CGamepad()
{
  TIMER_START("Gamepad");

  //  �ڑ�����Ă���XInput�R���g���[���̐����擾
  {
    for (; XInputNum_ < XUSER_MAX_COUNT; ++XInputNum_)
    {
      XINPUT_STATE State;

      //  �擾���s�̎��I��
      if (XInputGetState(XInputNum_, &State) == ERROR_DEVICE_NOT_CONNECTED)
      {
        break;
      }
    }
  }

  //  �ڑ�����Ă���W���C�X�e�B�b�N�̐����擾
  {
    JOYINFOEX JoyInfoEx;
    JoyInfoEx.dwSize = sizeof(JOYINFOEX);
    JoyInfoEx.dwFlags = JOY_RETURNALL;

    for (UINT i = 0, Num = joyGetNumDevs(); i < Num; ++i)
    {
      if (JOYERR_NOERROR == joyGetPosEx(i, &JoyInfoEx))
      {
        ++DirectInputNum_;
        JoyIDList_.push_back(i);
      }
    }
  }

  ControllerNum_ = DirectInputNum_;

  //  XInput�R���g���[���̐������炷
  DirectInputNum_ -= XInputNum_;

  if (ControllerNum_ > kControllerNum)
  {
    DirectInputNum_ -= ControllerNum_ - kControllerNum;
    ControllerNum_ = kControllerNum;
  }

  if (ControllerNum_ > 0)
  {
    pDirectInputDatas_ = std::make_unique<DirectInputData[]>(ControllerNum_);

    //  �G���[�`�F�b�N�p
    HRESULT hr = S_OK;

    //  �q�����Ă���XInput������
    if (XInputNum_ > 0)
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
                    DWORD dwVid, dwPid;
                    WCHAR *strVid, *strPid;

                    // If it does, then get the VID/PID from var.bstrVal
                    dwVid = dwPid = 0;
                    strVid = wcsstr(var.bstrVal, L"VID_");
                    strPid = wcsstr(var.bstrVal, L"PID_");
                    if (strVid && swscanf_s(strVid, L"VID_%4X", &dwVid) != 1) dwVid = 0;
                    if (strPid && swscanf_s(strPid, L"PID_%4X", &dwPid) != 1) dwPid = 0;

                    //  XInput�Ƃ��Ċ��ɕۑ�����Ă����ꍇtrue
                    auto CheckList = [&](LONG _XInputValue)->bool
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

                    if (CheckList(XInputValue)) continue;

                    XInputList_.push_back(XInputValue);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  TIMER_END("Gamepad");
}

void CGamepad::Initialize(const HWND& _hWnd)
{
  hWnd_ = _hWnd;

  HRESULT hr = S_OK;

  //  DirectInput���쐬
  hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)pDirectInput_.GetAddressOf(), NULL);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  //  Joystick���쐬
  hr = pDirectInput_->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  //  �{�^���̐���ۑ�
  {
    for (int i = 0; i < XInputNum_; ++i)
    {
      Status_[i].ButtonNum = IXInput::kButtonNum;
      Status_[i].InputStatus = new InputState[IXInput::kButtonNum];
    }

    JOYCAPS JoyCaps;
    for (int i = XInputNum_; i < ControllerNum_; ++i)
    {
      joyGetDevCaps(JoyIDList_[i - XInputNum_], &JoyCaps, sizeof(JoyCaps));

      const int ButtonNum = JoyCaps.wNumButtons + kPovDirectionNum;

      Status_[i].ButtonNum = ButtonNum;
      Status_[i].InputStatus = new InputState[ButtonNum];
    }
  }
}

void CGamepad::CreateDirectInputDevice(const GUID& GuidProductFromDirectInput)
{
  ++DeviceNum_;

  //  XInput����
  for (int i = 0, Size = XInputList_.size(); i < Size; ++i)
  {
    //  XInput�ł���
    if (static_cast<ULONG>(XInputList_[i]) == GuidProductFromDirectInput.Data1)
    {
      return;
    }
  }

  HRESULT hr = S_OK;

  DirectInputData& pDirectInputData = pDirectInputDatas_[CreateDeviceNum_++];

  //  �W���C�X�e�B�b�N���쐬
  hr = pDirectInput_->CreateDevice(GuidProductFromDirectInput, &pDirectInputData.pJoyStick, nullptr);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  hr = pDirectInputData.pJoyStick->SetDataFormat(&c_dfDIJoystick);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  hr = pDirectInputData.pJoyStick->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  // ���̒l�͈̔͂�ݒ�
  DIPROPRANGE DirectInputPropatyRange;
  {
    DirectInputPropatyRange.diph.dwSize = sizeof(DirectInputPropatyRange);
    DirectInputPropatyRange.diph.dwHeaderSize = sizeof(DirectInputPropatyRange.diph);
    DirectInputPropatyRange.diph.dwObj = DIJOFS_X;
    DirectInputPropatyRange.diph.dwHow = DIPH_BYOFFSET;
    DirectInputPropatyRange.lMin = -kStickMaxValue;
    DirectInputPropatyRange.lMax = +kStickMaxValue;
    hr = pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
    DirectInputPropatyRange.diph.dwObj = DIJOFS_Y;
    hr = pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
    DirectInputPropatyRange.diph.dwObj = DIJOFS_Z;
    hr = pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
    DirectInputPropatyRange.diph.dwObj = DIJOFS_RZ;
    hr = pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
  }

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

    //  �g���K�[�ݒ�
    DirectInputEffect.dwTriggerButton = DIEB_NOTRIGGER;
    DirectInputEffect.dwTriggerRepeatInterval = 0;
    //  �G�t�F�N�g���ݒ�
    DirectInputEffect.dwFlags |= DIEFF_POLAR;
    DWORD Axes[] = { DIJOFS_X, DIJOFS_Y };  // �G�t�F�N�g��
    LONG Direction[] = { 1, 1 };            // �G�t�F�N�g����
    DirectInputEffect.cAxes = 2;
    DirectInputEffect.rgdwAxes = Axes;
    DirectInputEffect.rglDirection = Direction;
    //  �����ݒ�
    DirectInputEffect.lpEnvelope = nullptr; // �G���x���[�v�\����
    DirectInputEffect.cbTypeSpecificParams = sizeof(diPeriodic); // �G�t�F�N�g�����\���̂̃T�C�Y
    DirectInputEffect.lpvTypeSpecificParams = &diPeriodic; // �G�t�F�N�g�����\����

    pDirectInputData.pJoyStick->CreateEffect(GUID_Square, &DirectInputEffect, &pDirectInputData.pEffect, nullptr);
  }

  //  �W���C�X�e�B�b�N�������I��
  pDirectInputData.pJoyStick->Acquire();
  JoyIDList_.push_back(DeviceNum_ - 1);
}

//  ��Ԃ̍X�V
void CGamepad::Update()
{
  IXInput* pXInput = Engine::Get<IXInput>();

  auto XInputUpdate = [&](int _Index)
  {
    Status& Status = Status_[_Index];

    for (int i = 0; i < IXInput::kButtonNum; ++i)
    {
      Status.InputStatus[i].Update(pXInput->Press(i, _Index));
    }

    Status.isConnect = pXInput->isConnect(_Index);
    Status.LeftStick = pXInput->GetLeftStick(_Index, 0.0f);
    Status.RightStick = pXInput->GetRightStick(_Index, 0.0f);
    Status.LeftTrigger = pXInput->GetLeftTrigger(_Index, 0.0f);
    Status.RightTrigger = pXInput->GetRightTrigger(_Index, 0.0f);
  };

  auto DirectInputUpdate = [&](int _Index)->void
  {
    Status& Status = Status_[_Index];

    DIJOYSTATE State;

    LPDIRECTINPUTDEVICE8& pJoyStick = pDirectInputDatas_[_Index - XInputNum_].pJoyStick;
    pJoyStick->Poll();

    if (pJoyStick->GetDeviceState(sizeof(DIJOYSTATE), &State) != DI_OK)
    {
      Status.isConnect = false;
      return;
    }

    Status.isConnect = true;

    Status.LeftStick = hdx::float2(State.lX, -State.lY) / kStickMaxValue;
    Status.RightStick = hdx::float2(State.lZ, -State.lRz) / kStickMaxValue;
    Status.LeftTrigger = State.lRx / static_cast<float>(kTriggerMaxValue);
    Status.RightTrigger = State.lRy / static_cast<float>(kTriggerMaxValue);

    const int PovInput = State.rgdwPOV[0] / 4500;

    bool isInput[kPovDirectionNum]{};

    switch (PovInput)
    {
    case 0:
      isInput[static_cast<int>(PovDirection::Up)] = true;
      break;
    case 1:
      isInput[static_cast<int>(PovDirection::Up)] = true;
      isInput[static_cast<int>(PovDirection::Right)] = true;
      break;
    case 2:
      isInput[static_cast<int>(PovDirection::Right)] = true;
      break;
    case 3:
      isInput[static_cast<int>(PovDirection::Right)] = true;
      isInput[static_cast<int>(PovDirection::Down)] = true;
      break;
    case 4:
      isInput[static_cast<int>(PovDirection::Down)] = true;
      break;
    case 5:
      isInput[static_cast<int>(PovDirection::Down)] = true;
      isInput[static_cast<int>(PovDirection::Left)] = true;
      break;
    case 6:
      isInput[static_cast<int>(PovDirection::Left)] = true;
      break;
    case 7:
      isInput[static_cast<int>(PovDirection::Left)] = true;
      isInput[static_cast<int>(PovDirection::Up)] = true;
      break;
    }

    for (int j = 0; j < kPovDirectionNum; ++j)
    {
      Status.InputStatus[j].Update(isInput[j]);
    }

    for (int j = kPovDirectionNum; j < Status.ButtonNum; ++j)
    {
      Status.InputStatus[j].Update((State.rgbButtons[j - kPovDirectionNum] & 0x80) != 0);
    }
  };

  for (int i = 0; i < ControllerNum_; ++i)
  {
    if (i < XInputNum_)
    {
      XInputUpdate(i);
    }
    else
    {
      DirectInputUpdate(i);
    }
  }
}

//  ���
CGamepad::~CGamepad()
{
  for (int i = 0; i < DirectInputNum_; ++i)
  {
    if (pDirectInputDatas_[i].pJoyStick)
    {
      pDirectInputDatas_[i].pJoyStick->Unacquire();
    }
  }

  for (int i = 0; i < ControllerNum_; ++i)
  {
    delete[] Status_[i].InputStatus;
  }
}

inline hdx::float2 GetStick(hdx::float2 _Value, float _DeadZone)
{
  if (hdx::Math::GetAbsoluteValue(_Value.x) < _DeadZone) _Value.x = 0.0f;
  if (hdx::Math::GetAbsoluteValue(_Value.y) < _DeadZone) _Value.y = 0.0f;

  return _Value;
}

//  ���X�e�B�b�N�̓��͏�Ԃ��擾
hdx::float2 CGamepad::GetLeftStick(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return hdx::float2(0.0f, 0.0f);

  return GetStick(Status_[_Index].LeftStick, _DeadZone);
}

//  �E�X�e�B�b�N�̓��͏�Ԃ��擾
hdx::float2 CGamepad::GetRightStick(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return hdx::float2(0.0f, 0.0f);

  return GetStick(Status_[_Index].RightStick, _DeadZone);
}

inline float GetTrigger(float _Value, float _DeadZone)
{
  if (_Value < _DeadZone) _Value = 0.0f;

  return _Value;
}

//  ���g���K�[�̓��͏�Ԃ��擾
float CGamepad::GetLeftTrigger(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return 0.0f;

  return GetTrigger(Status_[_Index].LeftTrigger, _DeadZone);
}

//  �E�g���K�[�̓��͏�Ԃ��擾
float CGamepad::GetRightTrigger(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return 0.0f;

  return GetTrigger(Status_[_Index].RightTrigger, _DeadZone);
}

//  �R���g���[����U�������܂�
void CGamepad::SetVibration(int _Index, float _Speed)const
{
  if (!(isWithinRange(_Index))) return;

  //  XInput��U��������
  if (_Index < XInputNum_)
  {
    Engine::Get<IXInput>()->SetVibration(_Index, _Speed);
    return;
  }

  //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
  //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Start(1, 0);
}

//  �R���g���[���̐U�����~�߂܂�
void CGamepad::StopVibration(int _Index)const
{
  if (!(isWithinRange(_Index))) return;

  //  XInput�̐U�����~�߂�
  if (_Index < XInputNum_)
  {
    Engine::Get<IXInput>()->StopVibration(_Index);
    return;
  }

  //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
  //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Stop();
}
