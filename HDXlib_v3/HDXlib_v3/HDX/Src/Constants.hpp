#pragma once
#include "Include/Constants.hpp"

constexpr UINT kConstantBufferMaxNum = hdx::Constants::ConstantBufferMaxNum;

constexpr UINT kSamplerStateMaxNum = hdx::Constants::SamplerStateMaxNum;

constexpr UINT kTextureMaxNum = hdx::Constants::TextureMaxNum;

constexpr UINT kSpriteBatchMaxNum = 10000;

constexpr UINT kModelBatchMaxNum = 10000;

constexpr UINT kModelAnimationSamplingRate = 24;

constexpr char* kDefault2DVertexShaderFilePath = "DATA/Shader/SpriteVS.cso";

constexpr char* kDefault3DVertexShaderFilePath = "DATA/Shader/ModelVS.cso";

constexpr char* kDefault2DPixelShaderFilePath = "DATA/Shader/SpritePS.cso";

constexpr char* kDefault3DPixelShaderFilePath = "DATA/Shader/ModelPS.cso";
