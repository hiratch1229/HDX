#pragma once

//*************************
//  �V�X�e���n
//*************************

//  �V�X�e��
//  2018.07.31  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include <HDX/System/System.hpp>


//*************************
//  ���͌n
//*************************

//  �{�^����L�[�̓���
//  2018.08.25  �쐬
//  2018.08.26  �g�ݍ��킹������
//  TODO:�g�ݍ��킹��3�ȏ�w��o����悤��
#include <HDX/Input/Button.hpp>

//  �L�[�{�[�h
//  2018.08.25  �쐬 
#include <HDX/Input/Keyboard/Keyboard.hpp>

//  �}�E�X
//  2018.08.26  �쐬 
#include <HDX/Input/Mouse/Mouse.hpp>

//  XInput�R���g���[��
//  2018.09.20  �쐬
#include <HDX/Input/XInput/XInput.hpp>

//  �R���g���[���S��
//  2018.09.02  �쐬 
#include <HDX/Input/Gamepad/Gamepad.hpp>


//*************************
//  �O���t�B�b�N�n
//*************************

//  �F
//  2018.08.09  �쐬
#include <HDX/Color.hpp>

//  2D�摜
//  2018.08.09  �쐬
//  TODO:�����ƊȒP�ɕ`��o����悤��
//  TODO:�o�b�`����
#include <HDX/Texture/Texture.hpp>

//  3D��{�`�I�u�W�F�N�g
//  2018.09.26  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include <HDX/GeometricPrimitive.hpp>

//  3D���f��
//  2018.09.26  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include <HDX/Model.hpp>

//  FBX���f��
//  2018.09.28  �쐬
//  TODO:���Ɖۑ肩����P
#include <HDX/SkinnedMesh.hpp>

//  �����_���[2D
//  2018.10.28  �쐬
#include <HDX/Renderer/Renderer2D.hpp>

//  �u�����h�X�e�[�g
//  2018.10.29  �쐬
#include <HDX/BlendState/BlendState.hpp>

//  �T���v���[�X�e�[�g
//  2018.11.06  �쐬
#include <HDX/SamplerState/SamplerState.hpp>

//  ���X�^���C�[�U�[�X�e�[�g
//  2018.11.07  �쐬
#include <HDX/RasterizerState/RasterizerState.hpp>

//  �f�v�X�X�e���V���X�e�[�g
//  2018.11.07  �쐬
#include <HDX/DepthStencilState/DepthStencilState.hpp>

//  �����_�[�^�[�Q�b�g
//  2018.11.07  �쐬
#include <HDX/RenderTarget.hpp>


//*************************
//  �V�F�[�_�[�n
//*************************

//  �R���X�^���g�o�b�t�@
#include <HDX/ConstantBuffer.hpp>

//  �C���v�b�g���C�A�E�g
//  2018.10.04  �쐬
#include <HDX/InputElementDesc.hpp>

//  ���_�V�F�[�_�[
//  2018.09.30  �쐬
#include <HDX/VertexShader/VertexShader.hpp>

//  �s�N�Z���V�F�[�_�[
//  2018.09.30  �쐬
#include <HDX/PixelShader/PixelShader.hpp>


//*************************
//  �T�E���h�n
//*************************

//  �T�E���h
//  2018.09.02  �쐬
//  TODO:�O�o�[�W��������قƂ�ǎ����Ă����̂ŁA�F�X���P
#include <HDX/Sound.hpp>


//*************************
//  ���w�n
//*************************

//  ���w�萔
//  2018.08.09  �쐬
#include <HDX/MathConstants.hpp>

//  ���w
//  2018.08.09  �쐬
#include <HDX/Math.hpp>


//*************************
//  �֗��n
//*************************

//  float,int2�̌^
//  2018.08.09  �쐬
#include <HDX/Type2.hpp>

//  float,int3�̌^
//  2018.08.09  �쐬
#include <HDX/Type3.hpp>

//  �p�x�������K���N���X
//  2018.08.09  �쐬
#include <HDX/Angle.hpp>

//  �����_��(Xorshift)�N���X
//  2018.09.23  �쐬
#include <HDX/Random/Random.hpp>

//  �R�s�[�֎~�N���X
//  2018.07.31  �쐬
#include <HDX/NonCopy.hpp>

//  �V���O���g��(�f�U�C���p�^�[��)
//  2018.07.31  �쐬
#include <HDX/Singleton.hpp>

//  �C�[�W���O
//  2018.09.02  �쐬
#include <HDX/Easing.hpp>

//  �}�N��
//  2018.09.03  �쐬
#include <HDX/Macro.hpp>


//--------------------------------------------------

//  ���������[�N�ڍו\��
#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


//--------------------------------------------------

//  ������n�̌x���𖳌���
#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE
