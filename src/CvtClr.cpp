// ClrConv.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

//*****************************************************************************
//	�ړI����: �J���[�摜����O���[�X�P�[���摜�ւ̕ϊ� (�t�@�C�����o�͔�)
//	���͈���:
//		file_in:	�J���[�摜�̓��̓t�@�C����
//		fiel_out:	�O���[�X�P�[���摜�̏o�̓t�@�C����
//*****************************************************************************
int clr2gray(const char* file_in, const char* file_out) {
	int	ret = 0;	  // �߂�l�p�ϐ�
	cv::Mat	img_in; // ���͉摜
	cv::Mat img_out;	 // �o�͉摜

	// �摜�̓ǂݍ���
	img_in = cv::imread(file_in, CV_LOAD_IMAGE_COLOR);
	if (img_in.data == NULL) {
		fprintf(stderr, "Error: cv::imread(%s)\n", file_in);
		ret = -1;
	}
	else {
		// �o�͉摜�������̊m��
		// (���͉摜�Ɠ����T�C�Y�C�F�[�x8�r�b�g�̃O���[�X�P�[���摜(�F�`���l����: 1))
		img_out = cv::Mat(img_in.size(), CV_8U);
		if (img_out.data == NULL){
			fprintf(stderr, "Error: img_out = cv::Mat()\n");
			ret = -1;
		}
		else{
			// �J���[�摜����O���[�X�P�[���摜�ւ̕ϊ�
			cv::cvtColor(img_in, img_out, CV_BGR2GRAY);

			// �摜�̕ۑ�
			ret = cv::imwrite(file_out, img_out);
			if (ret != 1){
				fprintf(stderr, "Error: cv::imwrite(%s).\n", file_out);
				ret = -1;
			}
			else{
				ret = 0;
			}
		}
	}

	return ret;
}


//*****************************************************************************
//	�ړI����: �J���[�摜����O���[�X�P�[���摜�ւ̕ϊ� (�t�@�C�����o�͔�)
//	���͈���:
//		file_in:	�J���[�摜�̓��̓t�@�C����
//		fiel_out:	�O���[�X�P�[���摜�̏o�̓t�@�C����
//*****************************************************************************
int clr2gray_old(const char* file_in, const char* file_out)
{
	int				ret = 0;					// �߂�l�p�ϐ�
	IplImage*	p_img_in = NULL;	// ���͉摜
	IplImage*	p_img_out = NULL;	// �o�͉摜
	CvSize		size;							// �摜�T�C�Y


	// �摜�̓ǂݍ���
	p_img_in = cvLoadImage(file_in, CV_LOAD_IMAGE_COLOR);
	if (!p_img_in){
		fprintf(stderr, "Error: cvLoadImage(%s)\n", file_in);
		ret = -1;
	}
	else{
	

		// �o�͉摜�������̊m��
		// (���͉摜�Ɠ����T�C�Y�C�F�[�x8�r�b�g�̃O���[�X�P�[���摜(�F�`���l����: 1))
		size = cvSize(p_img_in->width, p_img_in->height);
		p_img_out = cvCreateImage(size, IPL_DEPTH_8U, 1);
		if (!p_img_out){
			fprintf(stderr, "Error: p_img_out = cvCreateImage\n");
			ret = -1;
		}
		else{


			// �J���[�摜����O���[�X�P�[���摜�ւ̕ϊ�
			cvCvtColor(p_img_in, p_img_out, CV_BGR2GRAY);


			// �摜�̕ۑ�
			ret = cvSaveImage(file_out, p_img_out);
			if (ret != 1){
				fprintf(stderr, "Error: cvSaveImage(%s).\n", file_out);
				ret = -1;
			}
			else{
				ret = 0;
			}
		}
	}


	// �摜�������̉��
	cvReleaseImage(&p_img_in);
	cvReleaseImage(&p_img_out);

	return ret;
}
