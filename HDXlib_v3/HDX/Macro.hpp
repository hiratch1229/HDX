#pragma once

#define SAFE_RELEASE(obj)		if( obj ){ obj->Release(); obj = nullptr; }	//	�|�C���^�����[�X
#define SAFE_DELETE(obj)		if( obj ){ delete obj;  obj = nullptr; }	//	�|�C���^���
#define SAFE_DELETE_ARRAY(obj)	if( obj ){ delete[] obj;  obj = nullptr; }	//	�|�C���^�z����
#define SAFE_FREE(obj)			if( obj ){ free( obj );  obj = nullptr; }	//	���������
