#pragma once
#include "Types.hpp"

namespace hdx
{
  class Random
  {
    Random() = default;
  public:
    //  範囲を指定
    static int Range(int _Max, int _Min = 0);
    //  範囲を指定
    static float Range(float _Max, float _Min = 0.0f);
    //  シードを設定
    static void SetSeed(UINT _Seed);
  };
}
