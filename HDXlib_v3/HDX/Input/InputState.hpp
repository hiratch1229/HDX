#pragma once

namespace detail
{
  enum class InputState
  {
    Release,  //  押されていない
    Pressed,  //  押された瞬間
    Press,    //  押されている
    Released, //  離された瞬間
  };
}
