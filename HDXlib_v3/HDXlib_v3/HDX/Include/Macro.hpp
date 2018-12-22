#pragma once

//	ポインタ解放
#define SAFE_DELETE(Obj)  if( Obj ){ delete Obj; Obj = nullptr; }	
//	ポインタ配列解放
#define SAFE_DELETE_ARRAY(Obj)  if( Obj ){ delete[] Obj; Obj = nullptr; }	
//	メモリ解放
#define SAFE_FREE(Obj)  if( Obj ){ free( Obj ); Obj = nullptr; }	
//  配列の要素数を求める
#define ARRAY_SIZE(Array) sizeof(Array) / sizeof(Array[0])
