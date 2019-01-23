#include "IPixelShader.hpp"

#include "CPixelShader.hpp"

IPixelShader* IPixelShader::Create()
{
  return new CPixelShader;
}
