#pragma once
#include <HDX/Types.hpp>

namespace hdx
{
  class Random
  {
    mutable unsigned int X_ = 123456789U;
    mutable unsigned int Y_ = 362436069U;
    mutable unsigned int Z_ = 521288629U;
    mutable unsigned int W_ = 88675123U;
  private:
    unsigned int Rand()const;
  public:
    //  �V�[�h�l�������_���ō쐬
    Random();
    //  �V�[�h�l��ݒ肵�č쐬
    constexpr Random(unsigned int _Seed) : W_(_Seed) {}
    //  �͈͂��w��
    int Range(int _Max, int _Min = 0)const;
    //  �͈͂��w��
    float Range(float _Max, float _Min = 0.0f)const;
  };
}
