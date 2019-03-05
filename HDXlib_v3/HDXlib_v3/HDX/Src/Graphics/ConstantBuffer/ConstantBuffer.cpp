#include "Include/ConstantBuffer.hpp"

#include "Src/Engine.hpp"
#include "Src/Graphics/ConstantBuffer/IConstantBuffer.hpp"

namespace hdx
{
  ConstantBufferDetail::ConstantBufferDetail(uint _Size)
    : ID_(Engine::Get<IConstantBuffer>()->Add(_Size))
  {

  }
}
