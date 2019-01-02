#include "Include/VertexShader.hpp"
#include "Include/InputElementDesc.hpp"

#include "Src/Engine.hpp"
#include "Src/VertexShader/IVertexShader.hpp"

namespace hdx
{
  VertexShader::VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], UINT _NumElements)
    : ID_(Engine::Get<IVertexShader>()->Create(_FilePath, _InputElementDescs, _NumElements))
  {

  }
}
