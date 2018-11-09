#pragma once
#include <HDX/Type2.hpp>

namespace detail
{
  class IWIC
  {
    struct Impl;
  private:
    Impl* pImpl_;
  public:
    IWIC();
    ~IWIC();
    int Load(const char* _FilePath);
    int Add(const hdx::int2& _Size);
  };
}
