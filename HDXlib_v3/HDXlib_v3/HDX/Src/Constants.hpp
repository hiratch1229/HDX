#pragma once
#include "Include/Constants.hpp"

constexpr UINT kCharMaxNum = hdx::Constants::kCharMaxNum;

constexpr UINT kConstantBufferMaxNum = hdx::Constants::kConstantBufferMaxNum;

constexpr UINT kSamplerStateMaxNum = hdx::Constants::kSamplerStateMaxNum;

constexpr UINT kTextureMaxNum = hdx::Constants::kTextureMaxNum;

constexpr UINT kControllerMaxNum = hdx::Constants::kControllerMaxNum;

constexpr UINT kSpriteBatchMaxNum = 10000;

constexpr UINT kModelBatchMaxNum = 10000;

constexpr UINT kModelAnimationSamplingRate = 24;

constexpr float kModelAnimationSamplingTime = 1.0f / kModelAnimationSamplingRate;

constexpr UINT kModelBoneMaxNum = hdx::Constants::kModelBoneMaxNum;

constexpr UINT kModelBoneInfluencesMaxNum = 4;

constexpr char* kDefault2DVertexShaderFilePath = "DATA/Shader/SpriteVS.cso";

constexpr char* kDefault3DVertexShaderFilePath = "DATA/Shader/ModelVS.cso";

constexpr char* kDefault2DPixelShaderFilePath = "DATA/Shader/SpritePS.cso";

constexpr char* kDefault3DPixelShaderFilePath = "DATA/Shader/ModelPS.cso";

constexpr char* kGUIVertexShaderFilePath = "DATA/Shader/GUIVS.cso";

constexpr char* kGUIPixelShaderFilePath = "DATA/Shader/GUIPS.cso";
