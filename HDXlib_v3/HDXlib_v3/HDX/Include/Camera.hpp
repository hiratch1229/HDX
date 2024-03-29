#pragma once
#include "Type3.hpp"
#include "Angle.hpp"

namespace hdx
{
  struct Camera
  {
    //  Êu
    float3 Pos = { 0.0f, 0.0f, -10.0f };
    //  _
    float3 Target = { 0.0f, 0.0f, 0.0f };
    //  ãûü
    float3 Up = { 0.0f, 1.0f, 0.0f };
    //  ÅßÊ
    float Near = 0.1f;
    //  ÅÊ
    float Far = 1000.0f;
    //  ìp
    Degree Fov = 30.0f;
    //  trueÅ§e
    bool isPerspective = true;
  };
}
