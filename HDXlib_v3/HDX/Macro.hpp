#pragma once

#define SAFE_RELEASE(obj)		if( obj ){ obj->Release(); obj = nullptr; }	//	ポインタリリース
#define SAFE_DELETE(obj)		if( obj ){ delete obj;  obj = nullptr; }	//	ポインタ解放
#define SAFE_DELETE_ARRAY(obj)	if( obj ){ delete[] obj;  obj = nullptr; }	//	ポインタ配列解放
#define SAFE_FREE(obj)			if( obj ){ free( obj );  obj = nullptr; }	//	メモリ解放
