#include "IConstantBuffer.hpp"

#include "CConstatBuffer.hpp"

IConstantBuffer* IConstantBuffer::Create()
{
  return new CConstatBuffer;
}
