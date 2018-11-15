#include "../../Include/PixelShader.hpp"

#include "../Engine.hpp"
#include "../PixelShader/IPixelShader.hpp"

namespace hdx
{
  PixelShader::PixelShader(const char* _FilePath)
    : ID_(Engine::GetPixelShader()->Create(_FilePath))
  {

  }
}
