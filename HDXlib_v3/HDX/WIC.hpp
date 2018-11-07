#pragma once
#include <HDX/Type2.hpp>

namespace detail
{
  class WIC
  {
    struct Impl;
  private:
    Impl* pImpl_;
  public:
    WIC();
    ~WIC();
    int Load(const char* _FilePath);
    int Add(const hdx::int2& _Size);
  };
}
