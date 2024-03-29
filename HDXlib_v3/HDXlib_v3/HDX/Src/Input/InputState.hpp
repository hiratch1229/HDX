#pragma once

class InputState
{
public:
  enum class State
  {
    Release,  //  押されていない
    Press,    //  押されている
    Released, //  離された瞬間
    Pressed,  //  押された瞬間
  };
private:
  State State_ = State::Release;
public:
  bool Press()const { return (static_cast<int>(State_) & 0x01) != 0; }
  bool Pressed()const { return State_ == State::Pressed; }
  bool Released()const { return State_ == State::Released; }
  bool Release()const { return !Press(); }
public:
  void Update(bool _isPress)
  {
    //  前回が押されていた時
    if (Press())
    {
      State_ = (_isPress) ? State::Press : State::Released;
    }
    //  前回が離されていた時
    else
    {
      State_ = (_isPress) ? State::Pressed : State::Release;
    }
  }
};
