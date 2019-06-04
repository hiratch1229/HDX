#pragma once

//  ライブラリ
namespace hdx
{
  //  イージング関数
  //  移動を滑らかに見せます
  //  https://easings.net/ja
  namespace Easing
  {
    float Linear(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
    inline float Linear(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
    {
      return Linear(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
    }
    inline int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
    {
      return static_cast<int>(Linear(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
    }

    struct Sine
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Quad
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Cubic
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Quart
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Quint
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Expo
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Circ
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Back
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Elastic
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };

    struct Bounce
    {
      static float In(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float Out(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      static float InOut(float _Time, float _TotalTime, float _Max = 1.0f, float _Min = 0.0f);
      inline static float In(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return In(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int In(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(In(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float Out(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int Out(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(Out(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
      inline static float InOut(int _Time, int _TotalTime, float _Max = 1.0f, float _Min = 0.0f)
      {
        return InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), _Max, _Min);
      }
      inline static int InOut(int _Time, int _TotalTime, int _Max = 1, int _Min = 0)
      {
        return static_cast<int>(InOut(static_cast<float>(_Time), static_cast<float>(_TotalTime), static_cast<float>(_Max), static_cast<float>(_Min)));
      }
    };
  };
}
