#pragma once
#include <HDX/Types.hpp>
#include <HDX/Color.hpp>

namespace hdx
{
  enum class Filter : uint
  {
    MinMagMipPoint = 0,
    MinMagPointMipLinear = 0x1,
    MinPointMagLinearMipPoint = 0x4,
    MinPointMagMipLinear = 0x5,
    MinLinearMagMipPoint = 0x10,
    MinLinearMagPointMipLinear = 0x11,
    MinMagLinearMipPoint = 0x14,
    MinMagMipLinear = 0x15,
    Anisotropic = 0x55,
    ComparisonMinMagMipPoint = 0x80,
    ComparisonMinMagPointMipLinear = 0x81,
    ComparisonMinPointMagLinearMipPoint = 0x84,
    ComparisonMinPointMagMipLinear = 0x85,
    ComparisonMinLinearMagMipPoint = 0x90,
    ComparisonMinLinearMagPointMipLinear = 0x91,
    ComparisonMinMagLinearMipPoint = 0x94,
    ComparisonMinMagMipLinear = 0x95,
    ComparisonAnisotropic = 0xd5,
  };

  enum class AddressMode : uint
  {
    Wrap = 1,
    Mirror = 2,
    Clamp = 3,
    Border = 4,
    MirrorOnce = 5
  };

  class SamplerState
  {
    enum class PreDefined
    {
      WrapLinear,
      WrapAnisotropic,

      Num
    };
  public:
    union
    {
      struct
      {
        AddressMode AddressMode_ : 3;
        Filter Filter_ : 8;
        uint MaxAnisotropy_ : 5;
        Color BorderColor_;
      };
      uint DataType_;
    };
  public:
    constexpr SamplerState(AddressMode _AddressMode = AddressMode::Clamp,
      Filter _Filter = Filter::MinMagMipLinear,
      uint _MaxAnisotropy = 16,
      const Color& _BorderColor = Palette::Black)
      : Filter_(_Filter),
      AddressMode_(_AddressMode),
      MaxAnisotropy_(_MaxAnisotropy),
      BorderColor_(_BorderColor)
    {

    }
  public:
    SamplerState(PreDefined _PreDefined)
    {
      static constexpr SamplerState PreDefineds[static_cast<int>(PreDefined::Num)] =
      {
        { AddressMode::Wrap, Filter::MinMagMipLinear },
        { AddressMode::Wrap, Filter::Anisotropic }
      };

      *this = PreDefineds[static_cast<int>(_PreDefined)];
    }
  public:
    bool operator==(const SamplerState& _SamplerState)const
    {
      return DataType_ == _SamplerState.DataType_;
    }
    bool operator!=(const SamplerState& _SamplerState)const
    {
      return !((*this) == _SamplerState);
    }
  public:
    static constexpr PreDefined Default2D = PreDefined::WrapLinear;
    static constexpr PreDefined Default3D = PreDefined::WrapAnisotropic;
  };
}
