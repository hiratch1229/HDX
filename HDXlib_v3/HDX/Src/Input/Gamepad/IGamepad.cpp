#include "IGamepad.hpp"

#include "../../Input/InputState.hpp"

#include "../../Engine.hpp"
#include "../../System/ISystem.hpp"
#include "../../Input/XInput/IXInput.hpp"
#include "../../Error.hpp"

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

namespace
{
  //  DirectInput�̐�
  int DirectInputNum = 0;
  //  XInput�̐�
  int XInputNum = 0;
  //  �R���g���[���̐�
  int ControllerNum = 0;

  struct DirectInputData
  {
    //  �W���C�X�e�B�b�N
    LPDIRECTINPUTDEVICE8 pJoyStick;
    //  �U���G�t�F�N�g
    LPDIRECTINPUTEFFECT pEffect;
  };

  Microsoft::WRL::ComPtr<IDirectInput8W> pDirectInput;

  std::unique_ptr<DirectInputData[]> pDirectInputDatas;

  //  XInput���ʗp���X�g
  std::vector<LONG> XInputList;

  constexpr int kStickMaxValue = 10000;
  constexpr int kTriggerMaxValue = 65535;

  void CreateDirectInputDevice(const GUID& GuidProductFromDirectInput)
  {
    //  �쐬�ς݃W���C�X�e�B�b�N��
    static int CreateDeviceNum = 0;

    HRESULT hr = S_OK;

    DirectInputData& pDirectInputData = pDirectInputDatas[CreateDeviceNum];

    //  �W���C�X�e�B�b�N���쐬
    hr = pDirectInput->CreateDevice(GuidProductFromDirectInput, &pDirectInputData.pJoyStick, nullptr);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    hr = pDirectInputData.pJoyStick->SetDataFormat(&c_dfDIJoystick);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    hr = pDirectInputData.pJoyStick->SetCooperativeLevel(::GetActiveWindow(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
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
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_Y;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_Z;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
      DirectInputPropatyRange.diph.dwObj = DIJOFS_RZ;
      pDirectInputData.pJoyStick->SetProperty(DIPROP_RANGE, &DirectInputPropatyRange.diph);
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
    ++CreateDeviceNum;
  }
}

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void*)
{
  //  XInput���ʗp�֐�
  auto isXInput = [&](const GUID& GuidProductFromDirectInput)->bool
  {
    for (int i = 0, size = XInputList.size(); i < size; ++i)
    {
      //  XInput�ł���
      if (XInputList[i] == GuidProductFromDirectInput.Data1)
      {
        return true;
      }
    }

    //  XInput�ł͂Ȃ�
    return false;
  };

  //  XInput�̎�����
  if (isXInput(pdidInstance->guidProduct))
  {
    return DIENUM_CONTINUE;
  }

  //  DirectInput���쐬
  CreateDirectInputDevice(pdidInstance->guidProduct);

  //  ����
  return DIENUM_CONTINUE;
}


//--------------------------------------------------

//  �쐬
IGamepad::IGamepad()
{
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

  ControllerNum = DirectInputNum;

  //  XInput�R���g���[���̐������炷
  DirectInputNum -= XInputNum;

  if (ControllerNum > kControllerNum)
  {
    DirectInputNum -= ControllerNum - kControllerNum;
    ControllerNum = kControllerNum;
  }

  pDirectInputDatas = std::make_unique<DirectInputData[]>(ControllerNum);

  {
    //  �G���[�`�F�b�N�p
    HRESULT hr = S_OK;

    //  �q�����Ă���XInput������
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

                    //  XInput�Ƃ��Ċ��ɕۑ�����Ă����ꍇtrue
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
    }

    //  DirectInput���쐬
    hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)pDirectInput.GetAddressOf(), NULL);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    //  Joystick���쐬
    hr = pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }
}

//  ��Ԃ̍X�V
void IGamepad::Update()
{
  IXInput* pXInput = Engine::GetXInput();

  auto XInputUpdate = [&](int _Index)
  {
    Status& Status = Status_[_Index];

    for (int i = 0; i < IXInput::kButtonNum; ++i)
    {
      Status.InputStatus[i] = pXInput->GetInputState(i, _Index);
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

    LPDIRECTINPUTDEVICE8& pJoyStick = pDirectInputDatas[_Index - XInputNum].pJoyStick;
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

    const int PovInput = State.rgdwPOV[0] / 4500;

    bool isInput[kPovDirectionNum];
    for (int j = 0; j < kPovDirectionNum; ++j)
    {
      isInput[j] = false;
    }

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

    for (int j = kPovDirectionNum; j < kButtonNum; ++j)
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

//  ���
IGamepad::~IGamepad()
{
  for (int i = 0; i < DirectInputNum; ++i)
  {
    if (pDirectInputDatas[i].pJoyStick)
    {
      pDirectInputDatas[i].pJoyStick->Unacquire();
    }
  }
}


//--------------------------------------------------

inline hdx::float2 GetStick(hdx::float2 _Value, float _DeadZone)
{
  if (hdx::Math::GetAbsoluteValue(_Value.X) < _DeadZone) _Value.X = 0.0f;
  if (hdx::Math::GetAbsoluteValue(_Value.Y) < _DeadZone) _Value.Y = 0.0f;

  return _Value;
}

//  ���X�e�B�b�N�̓��͏�Ԃ��擾
hdx::float2 IGamepad::GetLeftStick(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return 0.0f;

  return GetStick(Status_[_Index].LeftStick, _DeadZone);
}

//  �E�X�e�B�b�N�̓��͏�Ԃ��擾
hdx::float2 IGamepad::GetRightStick(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return 0.0f;

  return GetStick(Status_[_Index].RightStick, _DeadZone);
}

inline float GetTrigger(float _Value, float _DeadZone)
{
  if (_Value < _DeadZone) _Value = 0.0f;

  return _Value;
}

//  ���g���K�[�̓��͏�Ԃ��擾
float IGamepad::GetLeftTrigger(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return 0.0f;

  return GetTrigger(Status_[_Index].LeftTrigger, _DeadZone);
}

//  �E�g���K�[�̓��͏�Ԃ��擾
float IGamepad::GetRightTrigger(int _Index, float _DeadZone)const
{
  if (!(isWithinRange(_Index))) return 0.0f;

  return GetTrigger(Status_[_Index].RightTrigger, _DeadZone);
}

//  �R���g���[����U�������܂�
void IGamepad::SetVibration(int _Index, float _Speed)const
{
  if (!(isWithinRange(_Index))) return;

  //  XInput��U��������
  if (_Index < XInputNum)
  {
    Engine::GetXInput()->SetVibration(_Index, _Speed);
    return;
  }

  //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
  //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Start(1, 0);
}

//  �R���g���[���̐U�����~�߂܂�
void IGamepad::StopVibration(int _Index)const
{
  if (!(isWithinRange(_Index))) return;

  //  XInput�̐U�����~�߂�
  if (_Index < XInputNum)
  {
    Engine::GetXInput()->StopVibration(_Index);
    return;
  }

  //const int DirectInputIndex = _Index - pImpl_->XInputNum_;
  //if (pImpl_->pEffects_[DirectInputIndex]) pImpl_->pEffects_[DirectInputIndex]->Stop();
}
