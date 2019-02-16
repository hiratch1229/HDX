#include "IConstantBuffer.hpp"

#include "CConstantBuffer.hpp"

IConstantBuffer* IConstantBuffer::Create()
{
  return new CConstantBuffer;
}
