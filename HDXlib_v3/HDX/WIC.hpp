#pragma once

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
  };
}
