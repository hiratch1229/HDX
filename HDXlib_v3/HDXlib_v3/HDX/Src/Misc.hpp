#pragma once
#include <Windows.h>

//--------------------------------------------------
//  エラー
//--------------------------------------------------
#if defined( DEBUG ) || defined( _DEBUG )
#define _ASSERT_EXPR_A(expr, msg) \
	(void)((!!(expr)) || \
	(1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, "%s", msg)) || \
	(_CrtDbgBreak(), 0))

inline LPWSTR hResultTrace(HRESULT hr)
{
  LPWSTR msg;
  FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&msg), 0, NULL);
  return msg;
}
#else
#define  _ASSERT_EXPR_A(expr, expr_str) ((void)0)
#endif

//--------------------------------------------------
//  デバッグ用
//--------------------------------------------------
#if defined( DEBUG ) || defined( _DEBUG )
#define TIMER_START(str) Engine::Start(str)
#define TIMER_END(str) Engine::End(str)
#else
#define TIMER_START(str)
#define TIMER_END(str)
#endif
