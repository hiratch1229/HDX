#pragma once

//*************************
//  �V�X�e���n
//*************************

//  �V�X�e��
//  2018.07.31  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include "HDX/Include/System.hpp"


//*************************
//  ���͌n
//*************************

//  �{�^����L�[�̓���
//  2018.08.25  �쐬
//  2018.08.26  �g�ݍ��킹������
//  TODO:�g�ݍ��킹��3�ȏ�w��o����悤��
#include "HDX/Include/Button.hpp"

//  �L�[�{�[�h
//  2018.08.25  �쐬
#include "HDX/Include/Keyboard.hpp"

//  �}�E�X
//  2018.08.26  �쐬 
#include "HDX/Include/Mouse.hpp"

//  XInput�R���g���[��
//  2018.09.20  �쐬
#include "HDX/Include/XInput.hpp"

//  DirectInput�R���g���[��
//  2018.09.02  �쐬 
#include "HDX/Include/Gamepad.hpp"


//*************************
//  �O���t�B�b�N�n
//*************************

//  �F
//  2018.08.09  �쐬
#include "HDX/Include/Color.hpp"

//  2D�摜
//  2018.08.09  �쐬
//  TODO:�����ƊȒP�ɕ`��o����悤��
//  TODO:�o�b�`����
#include "HDX/Include/Texture.hpp"

////  3D��{�`�I�u�W�F�N�g
////  2018.09.26  �쐬
////  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
//#include "HDX/Include/GeometricPrimitive.hpp"

//  3D���f��
//  2018.09.26  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include "HDX/Include/Model.hpp"

////  FBX���f��
////  2018.09.28  �쐬
////  TODO:���Ɖۑ肩����P
//#include "HDX/Include/GeometricPrimitive.hpp"

//  �����_���[2D
//  2018.10.28  �쐬
#include "HDX/Include/Renderer2D.hpp"

//  �u�����h�X�e�[�g
//  2018.10.29  �쐬
#include "HDX/Include/BlendState.hpp"

//  �T���v���[�X�e�[�g
//  2018.11.06  �쐬
#include "HDX/Include/SamplerState.hpp"

//  ���X�^���C�[�U�[�X�e�[�g
//  2018.11.07  �쐬
#include "HDX/Include/RasterizerState.hpp"

//  �f�v�X�X�e���V���X�e�[�g
//  2018.11.07  �쐬
#include "HDX/Include/DepthStencilState.hpp"

//  �����_�[�^�[�Q�b�g
//  2018.11.07  �쐬
#include "HDX/Include/RenderTarget.hpp"


//*************************
//  �V�F�[�_�[�n
//*************************

//  �R���X�^���g�o�b�t�@
#include "HDX/Include/ConstantBuffer.hpp"

//  �C���v�b�g���C�A�E�g
//  2018.10.04  �쐬
#include "HDX/Include/InputElementDesc.hpp"

//  ���_�V�F�[�_�[
//  2018.09.30  �쐬
#include "HDX/Include/VertexShader.hpp"

//  �s�N�Z���V�F�[�_�[
//  2018.09.30  �쐬
#include "HDX/Include/PixelShader.hpp"


//*************************
//  �T�E���h�n
//*************************

//  �T�E���h
//  2018.09.02  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include "HDX/Include/Sound.hpp"


//*************************
//  ���w�n
//*************************

//  ���w�萔
//  2018.08.09  �쐬
#include "HDX/Include/MathConstants.hpp"

//  ���w
//  2018.08.09  �쐬
#include "HDX/Include/Math.hpp"


//*************************
//  ��{�n
//*************************

//  float,int2�̌^
//  2018.08.09  �쐬
#include "HDX/Include/Type2.hpp"

//  float,int3�̌^
//  2018.08.09  �쐬
#include "HDX/Include/Type3.hpp"

//  �p�x�������K���N���X
//  2018.08.09  �쐬
#include "HDX/Include/Angle.hpp"

//  �s��N���X
//  2018.11.19  �쐬
#include "HDX/Include/Matrix.hpp"


//*************************
//  �֗��n
//*************************

//  �����_��(Xorshift)�N���X
//  2018.09.23  �쐬
#include "HDX/Include/Random.hpp"

//  �R�s�[�֎~�N���X
//  2018.07.31  �쐬
#include "HDX/Include/NonCopy.hpp"

//  �V���O���g��(�f�U�C���p�^�[��)
//  2018.07.31  �쐬
#include "HDX/Include/Singleton.hpp"

//  �C�[�W���O
//  2018.09.02  �쐬
#include "HDX/Include/Easing.hpp"

//  �}�N��
//  2018.09.03  �쐬
#include "HDX/Include/Macro.hpp"

//  GUI
//  2018.11.18  �쐬
//  TODO:�T���v���̂܂܂Ȃ̂Ŏg���������
#include "HDX/Include/GUI.hpp"

//--------------------------------------------------

//  ���������[�N�ڍו\��
#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


//--------------------------------------------------

//  ������n�̌x���𖳌���
#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE
