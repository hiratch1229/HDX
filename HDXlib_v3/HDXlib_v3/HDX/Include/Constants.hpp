#pragma once
#include "Types.hpp"

//  ライブラリ
namespace hdx
{
  //  定数
  namespace Constants
  {
    //  最大文字数
    constexpr UINT CharMaxNum = 256;

    constexpr UINT AppendAlignedElement = 0xffffffff;

    constexpr UINT SamplerStateMaxNum = 16;

    constexpr UINT TextureMaxNum = 128;

    constexpr UINT ConstantBufferMaxNum = 14;

    constexpr UINT ControllerMaxNum = 4;

    constexpr UINT MaxBoneInfluences = 4;

    constexpr UINT MaxBoneNum = 32;
  }
}
