#include "ISound.hpp"

#include "CSound.hpp"

ISound* ISound::Create()
{
  return new CSound;
}
