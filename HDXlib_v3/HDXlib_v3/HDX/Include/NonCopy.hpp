#pragma once

//  ライブラリ
namespace hdx
{
  //  コピー禁止クラス
  //  継承して使用
  class NonCopy
  {
    NonCopy(const NonCopy&) = delete;
    NonCopy& operator=(const NonCopy&) = delete;
  protected:
    NonCopy() = default;
  };
}
