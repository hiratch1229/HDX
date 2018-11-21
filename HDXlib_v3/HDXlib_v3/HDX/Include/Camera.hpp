#pragma once
#include "Type3.hpp"
#include "Angle.hpp"

namespace hdx
{
  struct Camera
  {
    //  Êu
    float3 Pos;
    //  _
    float3 Target;
    //  ãûü
    float3 Up;
    //  ÅßÊ
    float Near = 0.0f;
    //  ÅÊ
    float Far = 1000.0f;
    //  ìp
    Degree Fov = 30.0f;
    //  trueÅ§e
    bool isPerspective = true;
  };
}
