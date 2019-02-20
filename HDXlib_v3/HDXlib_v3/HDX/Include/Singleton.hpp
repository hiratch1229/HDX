#pragma once

namespace hdx
{
  //  �f�U�C���p�^�[��Singleton
  //  �p�����Ďg�p
  template <class T>
  class Singleton
  {
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton &&) = delete;
    Singleton& operator=(Singleton &&) = delete;
  protected:
    Singleton() = default;
  public:
    static T* Get()
    {
      static T Instance;
      return &Instance;
    }
  };
}
