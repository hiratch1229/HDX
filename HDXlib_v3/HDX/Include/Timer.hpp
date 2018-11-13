#pragma once
#include <chrono>

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  class Timer
  {
    std::chrono::system_clock::time_point Start_;
  public:
    Timer()
      : Start_(std::chrono::system_clock::now())
    {

    }
    void Start()
    {
      Start_ = std::chrono::system_clock::now();
    }
    template <class Duration>
    float End()
    {
      return static_cast<float>(std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - Start_).count());
    }
  };
}
