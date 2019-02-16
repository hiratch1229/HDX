#include "Include/PixelShader.hpp"

#include "Src/Engine.hpp"
#include "Src/Shaders/PixelShader/IPixelShader.hpp"

namespace hdx
{
  PixelShader::PixelShader(const char* _FilePath)
    : ID_(Engine::Get<IPixelShader>()->Create(_FilePath))
  {

  }
}
