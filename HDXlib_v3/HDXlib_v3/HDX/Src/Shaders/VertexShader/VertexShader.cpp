#include "Include/VertexShader.hpp"

#include "Src/Engine.hpp"
#include "Src/Shaders/VertexShader/IVertexShader.hpp"

namespace hdx
{
  VertexShader::VertexShader(const char* _FilePath)
    : ID_(Engine::Get<IVertexShader>()->Create(_FilePath))
  {

  }
}
