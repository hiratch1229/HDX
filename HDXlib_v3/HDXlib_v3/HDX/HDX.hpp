#pragma once

//*************************
//  �V�X�e���n
//*************************

//  �V�X�e��
//  2018.07.31  �쐬
//  2018.10.29  �G���W���ƕ������ĊǗ��ɕύX
#include "Include/System.hpp"


//*************************
//  ���͌n
//*************************

//  �{�^����L�[�̓���
//  2018.08.25  �쐬
//  2018.08.26  �g�ݍ��킹������
//  TODO:�g�ݍ��킹��3�ȏ�w��o����悤��
#include "Include/Button.hpp"

//  �L�[�{�[�h
//  2018.08.25  �쐬
#include "Include/Keyboard.hpp"

//  �}�E�X
//  2018.08.26  �쐬 
#include "Include/Mouse.hpp"

//  XInput�R���g���[��
//  2018.09.20  �쐬
#include "Include/XInput.hpp"

//  DirectInput�R���g���[��
//  2018.09.02  �쐬 
#include "Include/Gamepad.hpp"


//*************************
//  �O���t�B�b�N�n
//*************************

//  �F
//  2018.08.09  �쐬
#include "Include/Color.hpp"

//  2D�摜
//  2018.08.09  �쐬
//  TODO:�����ƊȒP�ɕ`��o����悤��
//  2018.11.14  �o�b�`�����ɕύX
#include "Include/Texture.hpp"

//  3D���f��
//  2018.09.26  �쐬
//  2018.11.22  GeometricPrimitive��SkinnedMesh�𓝍�
#include "Include/Model.hpp"

//  �J����
//  2018.11.21  �쐬
#include "Include/Camera.hpp"

//  �����_���[2D
//  2018.10.28  �쐬
#include "Include/Renderer2D.hpp"

//  �����_���[3D
//  2018.11.21  �쐬
#include "Include/Renderer3D.hpp"

//  �u�����h�X�e�[�g
//  2018.10.29  �쐬
#include "Include/BlendState.hpp"

//  �T���v���[�X�e�[�g
//  2018.11.06  �쐬
#include "Include/SamplerState.hpp"

//  ���X�^���C�[�U�[�X�e�[�g
//  2018.11.07  �쐬
#include "Include/RasterizerState.hpp"

//  �f�v�X�X�e���V���X�e�[�g
//  2018.11.07  �쐬
#include "Include/DepthStencilState.hpp"

//  �R���X�^���g�o�b�t�@
//  2018.11.21  �쐬
#include "Include/ConstantBuffer.hpp"

//  �����_�[�^�[�Q�b�g
//  2018.11.07  �쐬
#include "Include/RenderTarget.hpp"


//*************************
//  �V�F�[�_�[�n
//*************************

//  �R���X�^���g�o�b�t�@
#include "Include/ConstantBuffer.hpp"

//  ���_�V�F�[�_�[
//  2018.09.30  �쐬
#include "Include/VertexShader.hpp"

//  �s�N�Z���V�F�[�_�[
//  2018.09.30  �쐬
#include "Include/PixelShader.hpp"


//*************************
//  �T�E���h�n
//*************************

//  �T�E���h
//  2018.09.02  �쐬
//  2018.11.24  �Ǘ��N���X(ISound)�쐬
#include "Include/Sound.hpp"


//*************************
//  ���w�n
//*************************

//  ���w�萔
//  2018.08.09  �쐬
#include "Include/MathConstants.hpp"

//  ���w
//  2018.08.09  �쐬
#include "Include/Math.hpp"


//*************************
//  ��{�n
//*************************

//  float,int2�̌^
//  2018.08.09  �쐬
//  2019.02.07  template�N���X��
#include "Include/Type2.hpp"

//  float,int3�̌^
//  2018.08.09  �쐬
//  2019.02.07  template�N���X��
#include "Include/Type3.hpp"

//  float,int4�̌^
//  2019.02.07  �쐬
#include "Include/Type4.hpp"

//  �p�x�������K���N���X
//  2018.08.09  �쐬
#include "Include/Angle.hpp"

//  �s��N���X
//  2018.11.19  �쐬
#include "Include/Matrix.hpp"


//*************************
//  �֗��n
//*************************

//  �����_��(Xorshift)�N���X
//  2018.09.23  �쐬
#include "Include/Random.hpp"

//  �R�s�[�֎~�N���X
//  2018.07.31  �쐬
#include "Include/NonCopy.hpp"

//  �V���O���g��(�f�U�C���p�^�[��)
//  2018.07.31  �쐬
#include "Include/Singleton.hpp"

//  �C�[�W���O
//  2018.09.02  �쐬
#include "Include/Easing.hpp"

//  �}�N��
//  2018.09.03  �쐬
#include "Include/Macro.hpp"

//  GUI
//  2018.11.18  �쐬
//  TODO:�g���������
#include "Include/GUI.hpp"


//*************************
//  �֗��n
//*************************

//  �萔
//  2019.02.02
#include "Include/Constants.hpp"


//--------------------------------------------------

//  ���������[�N�ڍו\��
#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
