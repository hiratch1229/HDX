#pragma once
#include "Types.hpp"

namespace hdx
{
  enum class ShaderStage
  {
    Vertex,
    Pixel
  };

  struct ConstantBufferDetail
  {
  private:
    int ID_ = -1;
  public:
    int GetID()const { return ID_; }
  public:
    ConstantBufferDetail() = default;
    ConstantBufferDetail(uint _Size);
  };

  template<class T>
  struct ConstantBuffer
  {
    static constexpr uint kSize = sizeof(T);
    static_assert(kSize % 16 == 0);
  private:
    T Data_;
    ConstantBufferDetail Detail_;
  public:
    T& Get() { return Data_; }
    const void* GetPtr()const { return static_cast<const void*>(&Data_); }
  public:
    int GetID()const { return Detail_.GetID(); }
  public:
    ConstantBuffer()
      : Detail_(kSize) {}

    ConstantBuffer(const T& _Data)
      : Data_(_Data), Detail_(kSize)
    {

    }
  };
}
