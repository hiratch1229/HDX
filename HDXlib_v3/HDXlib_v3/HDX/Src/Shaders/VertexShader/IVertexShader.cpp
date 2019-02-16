#include "IVertexShader.hpp"

#include "CVertexShader.hpp"

IVertexShader* IVertexShader::Create()
{
  return new CVertexShader;
}
