#include "IRenderer3D.hpp"

#include "CRenderer3D.hpp"

IRenderer3D* IRenderer3D::Create()
{
  return new CRenderer3D;
}
