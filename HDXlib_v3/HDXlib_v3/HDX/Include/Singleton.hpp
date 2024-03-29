#pragma once

//  ライブラリ
namespace hdx
{
  //  デザインパターンSingleton
  //  継承して使用
  template <class T>
  class Singleton
  {
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
  protected:
    Singleton() = default;
    virtual ~Singleton() = default;
  public:
    static T* Get()
    {
      static T Instance;
      return &Instance;
    }
  };
}
