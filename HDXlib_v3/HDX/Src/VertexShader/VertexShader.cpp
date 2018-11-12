#include "../../Include/VertexShader.hpp"
#include "../../Include/InputElementDesc.hpp"

#include "../Engine.hpp"
#include "../VertexShader/IVertexShader.hpp"

namespace hdx
{
  VertexShader::VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], UINT _NumElements)
    : ID_(Engine::GetVertexShader()->Create(_FilePath, _InputElementDescs, _NumElements))
  {

  }
}
