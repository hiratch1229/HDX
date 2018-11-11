#pragma once

//  ���C�u����
namespace hdx
{
  //  �R�s�[�֎~�N���X
  //  �p�����Ďg�p
  class NonCopy
  {
    NonCopy(const NonCopy&) = delete;
    NonCopy& operator=(const NonCopy&) = delete;
  protected:
    NonCopy() = default;
  };
}
