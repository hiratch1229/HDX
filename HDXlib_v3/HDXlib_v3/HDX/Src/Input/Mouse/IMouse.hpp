#pragma once
#include "Include/Type2.hpp"
#include "Src/Input/InputState.hpp"

class IMouse
{
public:
  static IMouse* Create();

  IMouse() = default;

  virtual ~IMouse() = default;

  virtual void Update() = 0;

  virtual bool Press(int _Number)const = 0;

  virtual bool Pressed(int _Number)const = 0;

  virtual bool Released(int _Number)const = 0;

  virtual bool Release(int _Number)const = 0;

  virtual const hdx::int2& GetPos()const = 0;

  virtual const hdx::int2& GetDelta()const = 0;

  virtual const hdx::int2& GetWheel()const = 0;

  virtual void SetPos(const hdx::int2& _Pos) = 0;

  virtual void SetWheel(const hdx::int2& _Wheel) = 0;

  virtual bool AnyButtonPress()const = 0;

  virtual bool AnyButtonPressed()const = 0;

  virtual bool AnyButtonReleased()const = 0;
};
