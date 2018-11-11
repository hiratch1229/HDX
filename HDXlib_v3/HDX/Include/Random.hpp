#pragma once
#include "Types.hpp"

namespace hdx
{
  class Random
  {
    Random() = default;
  public:
    //  �͈͂��w��
    static int Range(int _Max, int _Min = 0);
    //  �͈͂��w��
    static float Range(float _Max, float _Min = 0.0f);
    //  �V�[�h��ݒ�
    static void SetSeed(UINT _Seed);
  };
}
