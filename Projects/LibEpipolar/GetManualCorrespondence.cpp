//GetManualCorrespondence..cpp

#include <stdio.h>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "Epipolar.h"


#ifndef N_STR
#define N_STR 200
#endif

struct GMC{
	char		m_window_name1[N_STR];	//�摜�P�ɑ΂���E�B���h�E��	
	cv::Mat		m_img_in1;				//���͉摜�P
	cv::Mat		m_img_out1;				//�o�͉摜�P
	int			m_n_pt_max;				//�ő�Ή��_��
	point_list	m_pt1;					//�摜�ɂ�����Ή��_
	int			m_n_pt1;				//�摜�̑Ή��_��
	int			m_radius;				//�Ή��_�̕`��~�̔��a
};

//*****************************************************************************
//	�ړI����: �蓮�Ή��_�擾�֐��i�t�@�C�����͔Łj
//	����:
//		file_img_in1:	1���ڂ̉摜�t�@�C����
//		file_img_in2:	2���ڂ̉摜�t�@�C����
//		file_pt:		
//		n_pt_max:		
//		radius:		
//		
//*****************************************************************************
int GetManualCorrespondence(const char* file_img_in1, const char* file_img_in2, const char* file_pt, int n_pt_max, int radius){

	int ret;


	return ret;

}


//*****************************************************************************
//	�ړI����: �Ή��_��ۑ�����֐�
//	����:
//		file_pt:
//		n_pt:
//		pt1:
//		pt2:
//		
//*****************************************************************************
int SaveCorrespondence(const char* file_pt, int n_pt, point_list &pt1, point_list &pt2){

	int ret;

	
	return ret;

}


//*****************************************************************************
//	�ړI����: �Ή��_��ǂݍ��݂���֐�
//	����:
//		file_pt:
//		n_pt:
//		pt1:
//		pt2:
//		
//*****************************************************************************
int LoadCorrespondence(const char* file_pt, int n_pt, point_list &pt1, point_list &pt2){

	int ret;


	return ret;

}

//*****************************************************************************
//	�ړI����: �}�E�X�C�x���g�֐�
//	����:
//		event:
//		x:
//		y:
//		flags:
//		param:
//		
//*****************************************************************************
void on_mouse1(int event, int x, int y, int flags, void* param){


}


//*****************************************************************************
//	�ړI����: �}�E�X�C�x���g�֐�
//	����:
//		event:
//		x:
//		y:
//		flags:
//		param:
//		
//*****************************************************************************
void on_mouse2(int event, int x, int y, int flags, void* param){


}

