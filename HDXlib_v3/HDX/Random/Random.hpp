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
    //  シード値をランダムで作成
    Random();
    //  シード値を設定して作成
    constexpr Random(unsigned int _Seed) : W_(_Seed) {}
    //  範囲を指定
    int Range(int _Max, int _Min = 0)const;
    //  範囲を指定
    float Range(float _Max, float _Min = 0.0f)const;
  };
}
