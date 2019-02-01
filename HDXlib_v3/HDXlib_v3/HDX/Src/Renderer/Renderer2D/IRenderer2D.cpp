#include "IRenderer2D.hpp"

#include "CRenderer2D.hpp"

IRenderer2D* IRenderer2D::Create()
{
  return new CRenderer2D;
}
