#pragma once
#include "HDX.hpp"

namespace hdx
{
  struct DirectionalLight
  {
    hdx::float3 Direction;
    float Itensity;
    hdx::ColorF Color;
  };

  struct PointLight
  {
    hdx::float3 Position;
    float Itensity;
    hdx::ColorF Color;
    float Range;
    hdx::float3 Padding;
  };

  template<uint Size>
  struct PointLights
  {
    static constexpr uint kSize = Size;
    PointLight Light[kSize];
  };

  struct SpotLight
  {
    hdx::float3 Position;
    float Itensity;
    hdx::float3 Direction;
    hdx::Radian Angle;
    hdx::ColorF Color;
    float Range;
    hdx::float3 Padding;
  };

  template<uint Size>
  struct SpotLights
  {
    static constexpr uint kSize = Size;
    SpotLight Light[kSize];
  };
}
