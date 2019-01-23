#include "ITexture.hpp"

#include "CTexture.hpp"

ITexture* ITexture::Create()
{
  return new CTexture;
}
