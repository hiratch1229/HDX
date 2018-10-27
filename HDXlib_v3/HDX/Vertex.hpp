#pragma once
#include <HDX/Type2.hpp>
#include <HDX/Type3.hpp>
#include <HDX/Color.hpp>

namespace detail
{
  struct Vertex2D
  {
    hdx::float3 Position;
    hdx::ColorF Color;
    hdx::float2 Texcoord;
  };
}
