#pragma once

//	�|�C���^���
#define SAFE_DELETE(Obj)  if( Obj ){ delete Obj; Obj = nullptr; }	
//	�|�C���^�z����
#define SAFE_DELETE_ARRAY(Obj)  if( Obj ){ delete[] Obj; Obj = nullptr; }	
//	���������
#define SAFE_FREE(Obj)  if( Obj ){ free( Obj ); Obj = nullptr; }	
//  �z��̗v�f�������߂�
#define ARRAY_SIZE(Array) sizeof(Array) / sizeof(Array[0])
