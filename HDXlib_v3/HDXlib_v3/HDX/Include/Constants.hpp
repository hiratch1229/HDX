#pragma once
#include "Types.hpp"

//  ライブラリ
namespace hdx
{
  //  定数
  namespace Constants
  {
    //  最大文字数
    constexpr UINT kCharMaxNum = 256;

    constexpr UINT kControllerMaxNum = 4;

    constexpr UINT kModelBoneMaxNum = 32;

    //  D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT
    constexpr UINT kSamplerStateMaxNum = 16;

    //  D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
    constexpr UINT kTextureMaxNum = 128;

    //  D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
    constexpr UINT kConstantBufferMaxNum = 14;
  }
}
