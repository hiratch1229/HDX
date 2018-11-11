#include "../../Include/PixelShader.hpp"

#include "../Engine/Engine.hpp"
#include "../PixelShader/IPixelShader.hpp"

namespace hdx
{
  PixelShader::PixelShader(const char* _FilePath)
    : ID_(GetPixelShader()->Create(_FilePath))
  {

  }
}
