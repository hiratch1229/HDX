#pragma once

namespace hdx
{
  struct int2;
}

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
