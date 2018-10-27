#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/InputElementDesc.hpp>
#include <HDX/System.hpp>

namespace hdx
{
  VertexShader::VertexShader(const char* _FilePath, const InputElementDesc _InputElementDescs[], unsigned int _NumElements)
    : ID_(detail::System::Get()->GetVertexShader()->Create(_FilePath, _InputElementDescs, _NumElements))
  {

  }
}
