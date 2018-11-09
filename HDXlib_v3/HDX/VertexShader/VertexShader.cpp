#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/InputElementDesc.hpp>

#include <HDX/Engine.hpp>

namespace hdx
{
  VertexShader::VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], UINT _NumElements)
    : ID_(GetVertexShader()->Create(_FilePath, _InputElementDescs, _NumElements))
  {

  }
}
