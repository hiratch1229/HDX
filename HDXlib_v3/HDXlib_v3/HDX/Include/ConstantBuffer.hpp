#pragma once
#include "Types.hpp"

namespace hdx
{
  enum class ShaderStage
  {
    Vertex,
    Pixel
  };

  template<class T>
  struct ConstantBuffer
  {
    static constexpr UINT Size = sizeof(T);
  private:
    T Data_;
  public:
    T& Get() { return Data_; }
    const void* GetPtr()const { return static_cast<const void*>(&Data_); }
  public:
    ConstantBuffer() = default;
    ConstantBuffer(const T _Data)
      : Data_(_Data)
    {

    }
  };
}
