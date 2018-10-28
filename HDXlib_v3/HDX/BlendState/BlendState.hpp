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

  class BlendState_
  {
    union
    {
      struct
      {
        bool AlphaToCoverageEnable_ : 3;
        bool BlendEnable_ : 3;
        Blend SrcBlend_ : 5;
        Blend DestBlend_ : 5;
        BlendOp BlendOp_ : 3;
        Blend SrcBlendAlpha_ : 5;
        Blend DestBlnedAlpha_ : 5;
        BlendOp BlendOpAlpha_ : 3;
      };
      int ID_;
    };
  private:
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
    constexpr BlendState_()
      : AlphaToCoverageEnable_(false),
      BlendEnable_(false),
      SrcBlend_(Blend::One),
      DestBlend_(Blend::One),
      BlendOp_(BlendOp::Add),
      SrcBlendAlpha_(Blend::One),
      DestBlnedAlpha_(Blend::One),
      BlendOpAlpha_(BlendOp::Add)
    {

    }

    constexpr BlendState_(bool _AlphaToCoverageEnable = false,
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
      BlendOpAlpha_(_BlendOpAlpha)
    {

    }

  public:
    BlendState_(PreDefined _PreDefined)
    {
      static constexpr BlendState_ PreDefinedStatus[static_cast<int>(PreDefined::Num)] =
      {
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add },
        { false, true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::One, Blend::InvSrcAlpha, BlendOp::Add }
      };

      *this = PreDefinedStatus[static_cast<int>(_PreDefined)];
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
