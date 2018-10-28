#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>

#include <HDX/Engine.hpp>

namespace hdx
{
  PixelShader::PixelShader(const char* _FilePath)
    : ID_(detail::Engine::GetPixelShader()->Create(_FilePath))
  {

  }
}
