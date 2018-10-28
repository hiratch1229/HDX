#pragma once

namespace hdx
{
  enum class Blend
  {
    Zero = 1,
    One = 2,
    SrcColor = 3,
    InvSrcColor = 4,
    SrcAlpha = 5,
    InvSrcAlpha = 6,
    DestAlpha = 7,
    InvDestAlpha = 8,
    DestColor = 9,
    InvDestColor = 10,
    SrcAlphaSat = 11,
    BlendFactor = 14,
    InvBlendFactor = 15,
    Src1Color = 16,
    InvSrc1Color = 17,
    Src1Alpha = 18,
    InvSrc1Alpha = 19
  };

  enum class BlendOp
  {
    Add = 1,
    Subtract = 2,
    RevSubtract = 3,
    Min = 4,
    Max = 5
  };

  class BlendState
  {
    enum class PreDefined
    {
      Default,
      Add,
      Subtract,
      Replace,
      Multiply,
      Lighten,
      Draken,
      Screen,

      Num
    };
  public:
    union
    {
      struct
      {
        bool AlphaToCoverageEnable_ : 3;
        bool BlendEnable_ : 3;
        hdx::Blend SrcBlend_ : 5;
        hdx::Blend DestBlend_ : 5;
        hdx::BlendOp BlendOp_ : 3;
        hdx::Blend SrcBlendAlpha_ : 5;
        hdx::Blend DestBlnedAlpha_ : 5;
        hdx::BlendOp BlendOpAlpha_ : 3;
      };
      int DataType_;
    };
  public:
    constexpr BlendState(bool _AlphaToCoverageEnable = false,
      bool _BlendEnable = false,
      Blend _SrcBlend = Blend::One,
      Blend _DestBlend = Blend::Zero,
      BlendOp _BlendOp = BlendOp::Add,
      Blend _SrcBlendAlpha = Blend::One,
      Blend _DestBlnedAlpha = Blend::Zero,
      BlendOp _BlendOpAlpha = BlendOp::Add)
      : AlphaToCoverageEnable_(_AlphaToCoverageEnable),
      BlendEnable_(_BlendEnable),
      SrcBlend_(_SrcBlend),
      DestBlend_(_DestBlend),
      BlendOp_(_BlendOp),
      SrcBlendAlpha_(_SrcBlendAlpha),
      DestBlnedAlpha_(_DestBlnedAlpha),
      BlendOpAlpha_(_BlendOpAlpha) { }
  public:
    BlendState(PreDefined _PreDefined)
    {
      static constexpr BlendState PreDefineds[static_cast<int>(PreDefined::Num)] =
      {
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::One, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::One, BlendOp::Subtract, Blend::Zero, Blend::One, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::Zero, BlendOp::Add, Blend::One, Blend::Zero, BlendOp::Add },
        { false, true, Blend::Zero, Blend::SrcColor, BlendOp::Add, Blend::DestAlpha, Blend::Zero, BlendOp::Add },
        { false, true, Blend::One, Blend::One, BlendOp::Max, Blend::One, Blend::One, BlendOp::Max },
        { false, true, Blend::One, Blend::One, BlendOp::Min, Blend::One, Blend::One, BlendOp::Min },
        { false, true, Blend::SrcAlpha, Blend::InvSrcColor, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add }
      };

      *this = PreDefineds[static_cast<int>(_PreDefined)];
    }
  public:
    bool operator==(const BlendState& _BlendState)const
    {
      return DataType_ == _BlendState.DataType_;
    }
    bool operator!=(const BlendState& _BlendState)const
    {
      return !((*this) == _BlendState);
    }
  public:
    static constexpr PreDefined Default = PreDefined::Default;
    static constexpr PreDefined Add = PreDefined::Add;
    static constexpr PreDefined Subtract = PreDefined::Subtract;
    static constexpr PreDefined Replace = PreDefined::Replace;
    static constexpr PreDefined Multiply = PreDefined::Multiply;
    static constexpr PreDefined Lighten = PreDefined::Lighten;
    static constexpr PreDefined Draken = PreDefined::Draken;
    static constexpr PreDefined Screen = PreDefined::Screen;
  };
}
