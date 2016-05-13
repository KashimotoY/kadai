// MouseEventSample.cpp

#include <stdio.h>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "Epipolar.h"


#ifndef N_STR
#define N_STR 200
#endif


//-------------------------------------------
// �}�E�X�C�x���g�T���v�����������߂̍\����
//-------------------------------------------
struct MES
{
	char		m_window_name1[N_STR];	// �摜1�ɑ΂���E�B���h�E��
	char		m_window_name2[N_STR];	// �摜2�ɑ΂���E�B���h�E��
	cv::Mat		img_in1;				// ���͉摜1
	cv::Mat		img_in2;				// ���͉摜2
	cv::Mat		img_out1;				// �o�͉摜1
	cv::Mat		img_out2;				// �o�͉摜2
	cv::Scalar	m_clr;					// �w��_�ɕ`�悷��~�̐F
	int			m_thickness;			// �w��_�ɕ`�悷��~�̑���
	int			m_radius;				// �w��_�ɕ`�悷��~�̔��a
	cv::Point	m_pt_l;					// ���{�^���N���b�N�_
	cv::Point	m_pt_r;					// �E�{�^���N���b�N�_
};


// ����̉摜�������K�ۑ�ŁCon_mouse1,2���g�p����ۂɏՓ˂�����邽�߂ɁC
// namespace NS_MouseEventSample�𗘗p

//*****************************************************************************
// �E�B���h�E1�ɑ΂���}�E�X�C�x���g
//*****************************************************************************
namespace NS_MouseEventSample{
	void on_mouse1(int event, int x, int y, int flags, void* param)
	{
		MES &mes = *(MES *)param;

		// �}�E�X���[�u�C�x���g
		if (event == CV_EVENT_MOUSEMOVE){

			fprintf(stderr, "�摜1��̓_(%d, %d)���}�E�X���ړ����ł��D\n", x, y);

			// �~��`�悵�ĕ\��
			mes.img_in1.copyTo(mes.img_out1);
			cv::circle(mes.img_out1, cv::Point(x, y), mes.m_radius, mes.m_clr, mes.m_thickness);
			cv::imshow(mes.m_window_name1, mes.img_out1);
		}

		return;
	}
};

//*****************************************************************************
// �E�B���h�E2�ɑ΂���}�E�X�C�x���g
//*****************************************************************************
namespace NS_MouseEventSample{
	void on_mouse2(int event, int x, int y, int flags, void* param)
	{
		MES &mes = *(MES *)param;
		static int cnt = 0;

		// ���{�^��UP�C�x���g
		if (event == CV_EVENT_LBUTTONUP){

			fprintf(stderr, "�摜2��̓_(%d,%d)�����N���b�N����܂����D\n", x, y);
			mes.m_pt_l = cvPoint(x, y);

			// �o�͉摜�̃N���A(���͉摜�ŏ㏑��)
			mes.img_in2.copyTo(mes.img_out2);

			// �~��`�悵�ĕ\��
			cv::circle(mes.img_out2, cv::Point(x, y), mes.m_radius, mes.m_clr, mes.m_thickness);
			cv::imshow(mes.m_window_name2, mes.img_out2);
		}

		// �E�{�^��UP�C�x���g
		else if (event == CV_EVENT_RBUTTONUP){

			fprintf(stderr, "�摜2��̓_(%d,%d)���E�N���b�N����܂����D\n", x, y);
			mes.m_pt_r = cvPoint(x, y);

			// ������`��
			cv::line(mes.img_out2, mes.m_pt_l, mes.m_pt_r, id2clr(cnt));
			cv::imshow(mes.m_window_name2, mes.img_out2);

			// �J�E���^�X�V
			cnt++;
		}

		return;
	}
};

using NS_MouseEventSample::on_mouse1;
using NS_MouseEventSample::on_mouse2;


//*****************************************************************************
// �}�E�X�C�x���g�T���v���֐�
//*****************************************************************************
int MouseEventSample(const char* file_img_in1, const char* file_img_in2, cv::Scalar clr, int thickness, int radius)
{
	int ret = 0;
	MES	mes;			// �}�E�X�C�x���g�T���v�����������߂̍\����
	int w, h, nc;	// �摜�̕��E�����E�F�`�����l����

	// �ϐ��̏�����
	strncpy_s(mes.m_window_name1, N_STR, "Window 1", N_STR); 
	strncpy_s(mes.m_window_name2, N_STR, "Window 2", N_STR); 
	mes.m_clr = clr;
	mes.m_thickness = thickness;
	mes.m_radius = radius;


	//-------------------
	// ���͉摜�̃��[�h
	//-------------------
	mes.img_in1 = cv::imread(file_img_in1);
	if (mes.img_in1.data == NULL){
		fprintf(stderr, "fail in cv::imread(%s).\n", file_img_in1);
		ret = -1;
	}
	else{

		mes.img_in2 = cv::imread(file_img_in2);
		if (mes.img_in2.data == NULL){
			fprintf(stderr, "Error: cv::imread(%s).\n", file_img_in2);
			ret = -1;
		}
		else{
			//------------
			// �������m��
			//------------
			nc = mes.img_in1.channels();
			mes.img_out1 = cv::Mat(mes.img_in1.size(), CV_8UC(nc));
			if (mes.img_out1.data == NULL){
				fprintf(stderr, "Error: mes.m_p_img_out1 = cv::Mat()\n");
				ret = -1;;
			}
			else{
				nc = mes.img_in2.channels();
				mes.img_out2 = cv::Mat(mes.img_in2.size(), CV_8UC(nc));
				if (mes.img_out2.data == NULL){
					fprintf(stderr, "Error: mes.m_p_img_out2 = cv::Mat()\n");
					return -1;
				}
				else{
					//-------------------
					// �E�B���h�E�̍쐬
					//-------------------
					cv::namedWindow(mes.m_window_name1, CV_WINDOW_AUTOSIZE);
					cv::moveWindow(mes.m_window_name1, 0, 0);

					cv::namedWindow(mes.m_window_name2, CV_WINDOW_AUTOSIZE);
					cv::moveWindow(mes.m_window_name2, mes.img_in1.size().width + 20, 0);

					//-------------
					// �摜�̕\��
					//-------------
					cv::imshow(mes.m_window_name1, mes.img_in1);
					cv::imshow(mes.m_window_name2, mes.img_in2);

					//-------------------------------
					// �}�E�X�R�[���o�b�N�֐��̐ݒ�
					//-------------------------------
					cv::setMouseCallback(mes.m_window_name1, (cv::MouseCallback)&on_mouse1, &mes);
					cv::setMouseCallback(mes.m_window_name2, (cv::MouseCallback)&on_mouse2, &mes);

					// �L�[���������܂őҋ@(�}�E�X�C�x���g����)
					cv::waitKey(-1);

					//-------------------
					// �E�B���h�E�̉��
					//-------------------
					cv::destroyWindow(mes.m_window_name1);
					cv::destroyWindow(mes.m_window_name2);
				}
			}
		}
	}

	return ret;
}
