#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
#include <HDX/System.hpp>

namespace hdx
{
  PixelShader::PixelShader(const char* _FilePath)
    : ID_(detail::System::Get()->GetPixelShader()->Create(_FilePath))
  {

  }
}
