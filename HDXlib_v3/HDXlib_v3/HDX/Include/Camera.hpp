#pragma once
#include "Type3.hpp"
#include "Angle.hpp"

namespace hdx
{
  struct Camera
  {
    //  �ʒu
    float3 Pos;
    //  �����_
    float3 Target;
    //  �����
    float3 Up;
    //  �ŋߖ�
    float Near = 0.0f;
    //  �ŉ���
    float Far = 1000.0f;
    //  ����p
    Degree Fov = 30.0f;
    //  true�œ������e
    bool isPerspective = true;
  };
}
