#pragma once

#if defined(DEBUG) | defined(_DEBUG)
#define NOT_FOUND(hr,wFilePath)  \
if (FAILED(hr))\
{\
  wchar_t wstr[256];\
  wsprintf(wstr, L"%s not found.", wFilePath);\
  _ASSERT_EXPR(SUCCEEDED(hr), wstr);\
}
#else
#define NOT_FOUND(hr,wFilePath)
#endif
