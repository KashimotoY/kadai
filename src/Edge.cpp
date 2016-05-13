// Edge.cpp

#include <stdio.h>
#include <algorithm>

#include <opencv2/opencv.hpp>
#include "Edge.h"


/**
 * �摜m�̃s�N�Z��(i, j)�̒l���擾����
 */
int get_image_data(cv::Mat m, int i, int j) {
	if (m.depth() == CV_8U)
		return m.at<unsigned char>(i, j);
	else
		return m.at<unsigned short>(i, j);
}


/**
 * �摜m�̃s�N�Z��(i, j)�ɒlval��������
 * Note: ���l��0�Cdepth�̍ő�l�𒴂���l�͍ő�l�ɕϊ������
 */
void set_image_data(cv::Mat m, int i, int j, double val) {
	int t = (int)round(val);
	if (m.depth() == CV_8U) {
		t = std::min(UCHAR_MAX, std::max(0, t));
		m.at<unsigned char>(i, j) = t;
	}
	else {
		t = std::min(USHORT_MAX, std::max(0, t));
		m.at<unsigned short>(i, j) = t;
	}
}


//*****************************************************************************
//	�ړI����: LoG (Laplacian of Gaussian)�t�B���^
//	���͈���:
//		img_in:		���͉摜
//		sigma:		LoG�t�B���^�̕W���΍�
//		bias:		LoG�摜�̃o�C�A�X
//	�o�͈���:
//		img_LoG:		LoG�摜
//*****************************************************************************
int LoG(cv::Mat img_in, cv::Mat img_LoG, double sigma, double bias)
{
	cv::Mat		img_op;							// �I�y���[�^�摜
	int			w, h;							// �摜�̕��ƍ���
	double		sigma2 = sigma * sigma;			// �W���΍���2��
	int			r2;								// ���a��2��
	int			range_op = (int)(3.0 * sigma);	// �I�y���[�^�͈�


	//----------------------
	// �摜�|�C���^�`�F�b�N
	//----------------------

	// ���͉摜
	if (img_in.data == NULL) {
		fprintf(stderr, "Error: img_in is NULL.\n");
		return -1;
	}

	// LoG�摜
	// (������)
	if (img_LoG.data == NULL) {
		fprintf(stderr, "Error: img_LoG is NULL.\n");
		return -1;
	}
	//
	

	//---------------------------
	// �摜�t�H�[�}�b�g�`�F�b�N
	//---------------------------

	// ���͉摜�T�C�Y�̎擾
	w = img_in.size().width;
	h = img_in.size().height;

	// LoG�摜�̃T�C�Y���`�F�b�N
	if (img_LoG.size() != img_in.size()){
		fprintf(stderr, "Error: sizes of img_in and img_LoG are incompatible.\n");
		return -1;
	}

	// ���͉摜�̐F�`�����l�����̃`�F�b�N
	if (img_in.channels() != 1) {
		fprintf(stderr, "Error: img_in.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}

	// LoG�摜�̐F�`�����l�����̃`�F�b�N
	// (������)
	if (img_LoG.channels() != 1) {
		fprintf(stderr, "Error: img_LoG.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}
	//


	// LoG�摜�̃f�v�X�̃`�F�b�N
	if (img_LoG.depth() != CV_8U && img_LoG.depth() != CV_16U) {
		fprintf(stderr, "Error: img_LoG.depth() must be CV_8U or CV_16U.\n");
		return -1;
	}

	// �W���΍��������ǂ������`�F�b�N
	// (������)
	if (!(sigma > 0)){
		fprintf(stderr, "Error: sigma must be over 0");
		return -1;
	}
	//

	//-------------------------------
	//	LoG�t�B���^�̃I�y���[�^�쐬
	//-------------------------------

	// �I�y���[�^�p�̃������m��
	cv::Size size_op = cv::Size(/*������*/range_op*2+1, /*������*/range_op*2+1);
	img_op = cv::Mat(size_op, CV_64F);
	if (img_op.data == NULL) {
		fprintf(stderr, "Error: img_op = cv::Mat().\n");
		return -1;
	}

	// �I�y���[�^�̐ݒ�
	double a = 0;
	for (int k = -range_op; k <= range_op; k++){
		for (int l = -range_op; l <= range_op; l++){
			r2 =/*������*/l*l + k*k;
			double op = /*������*/(r2/(sigma2) - 2)*exp(-r2/(2*sigma2));
			img_op.at<double>(/*������*/k + range_op, /*������*/l + range_op) = op;
			a += op;
		}
	}

	//-----------------------------------
	// ���͉摜�ƃI�y���[�^�Ƃ̏�ݍ���
	//-----------------------------------
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			double sum = /*������*/0;

			for (int k = -range_op; k <= range_op; k++){
				for (int l = -range_op; l <= range_op; l++){
					// �v�Z�Ώۂ̍��W�l���摜���Ɏ��܂邩�ǂ������`�F�b�N
					if (/*������*/i+k >= 0 && i+k < h && j+l >= 0 && j+l < w) {
						double op = img_op.at<double>(/*������*/k+range_op, /*������*/l+range_op);
						sum += op * /*������*/img_in.at<unsigned char>(i + k, j + l);
					}
				}
			}
			
			set_image_data(/*������*/img_LoG, i, j, sum+bias);
		}
	}

	return 0;
}

//*****************************************************************************
//	�ړI����: LoG (Laplacian of Gaussian)�t�B���^(�t�@�C�����o�͔�)
//	���͈���:
//		file_in:		���͉摜�t�@�C����
//		file_LoG:		LoG�摜�t�@�C����
//		sigma:			LoG�t�B���^�̕W���΍�
//		depth:			LoG�摜�̐F�[�x
//*****************************************************************************
int LoG_file(const char* file_in, const char* file_LoG, double sigma, int depth)
{
	int			ret;			// �߂�l�p�ϐ�
	cv::Mat		img_in;			// ���͉摜
	cv::Mat		img_LoG;		// LoG�摜
	double		bias;

	// depth�̃`�F�b�N�ƃo�C�A�X�̐ݒ�
	if (depth == CV_8U) bias = CHAR_MAX;
	else if (depth == CV_16U) bias = SHORT_MAX;
	else{
		fprintf(stderr, "Error: depth should be CV_8U or CV_16U.\n");
		return -1;
	}

	// �摜�̓ǂݍ���
	img_in = /*������*/cv::imread(file_in, CV_LOAD_IMAGE_GRAYSCALE);
	if (img_in.data == NULL){
		fprintf(stderr, "Error: cv::imread(%s)\n", file_in);
		ret = -1;
	}
	else{
		// LoG�摜�������̊m��
		// (���͉摜�Ɠ����T�C�Y�C�w��F�[�x�̃O���[�X�P�[���摜(�F�`���l����: 1))
		img_LoG = /*������*/cv::Mat(img_in.size(), depth);
		if (img_LoG.data == NULL){
			fprintf(stderr, "Error: img_LoG = cv::Mat()\n");
			ret = -1;
		}
		else{
			// LoG�t�B���^�̓K�p
			ret = /*������*/LoG(img_in, img_LoG, sigma, bias);
			if (ret){
				fprintf(stderr, "Error: LoG().\n");
			}
			else{
				// �摜�̕ۑ�
				ret = /*������*/cv::imwrite(file_LoG, img_LoG);
				if (ret != 1){
					fprintf(stderr, "Error: cv::imwrite(%s).\n", file_LoG);
					ret = -1;
				}
				else{
					ret = 0;
				}				
			}
		}
	}

	return ret;
}


//*****************************************************************************
//	�ړI����: �[�������@�ɂ��G�b�W���o
//	���͈���:
//		p_img_LoG:				LoG�摜
//	�o�͈���:
//		p_img_zero_cross:	�[�������摜
//*****************************************************************************
int zero_cross(cv::Mat img_LoG, cv::Mat img_zero_cross)
{
	int		w, h;		// �摜�̕��ƍ���
	double	bias;		// LoG�摜�̃o�C�A�X


	//----------------------
	// �摜�f�[�^�`�F�b�N
	//----------------------

	// LoG�摜
	/*������*/
	if (img_LoG.data == NULL) {
		fprintf(stderr, "Error: img_LoG is NULL.\n");
		return -1;
	}
	/**/
	
	// �[�������摜
	/*������*/
	if (img_zero_cross.data == NULL) {
		fprintf(stderr, "Error: img_zero_cross is NULL.\n");
		return -1;
	}
	/**/


	//---------------------------
	// �摜�t�H�[�}�b�g�`�F�b�N
	//---------------------------

	// �[�������摜�̕��E�����̃`�F�b�N
	/*������*/
	if (img_LoG.size() != img_zero_cross.size()){
		fprintf(stderr, "Error: sizes of img_zero_cross and img_LoG are incompatible.\n");
		return -1;
	}
	/**/

	w = img_LoG.size().width;
	h = img_LoG.size().height;

	// LoG�摜�E�[�������摜�̐F�`�����l�����̃`�F�b�N
	/*������*/
	if (img_LoG.channels() != 1) {
		fprintf(stderr, "Error: img_LoG.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}

	if (img_zero_cross.channels() != 1) {
		fprintf(stderr, "Error: img_zero_cross.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}
	/**/


	// depth�̃`�F�b�N�ƃo�C�A�X�̐ݒ�
	if (img_LoG.depth() == CV_8U) bias = CHAR_MAX;
	else if (img_LoG.depth() == CV_16U) bias = SHORT_MAX;
	else{
		fprintf(stderr, "Error: img_LoG.depth() should be CV_8U or CV_16U.\n");
		return -1;
	}


	//-------------------
	// �[�������_�̎Z�o
	//-------------------

	// �[�������_�摜�̏�����
	img_zero_cross.setTo(/*������*/0, img_zero_cross);
	// �e��f���X�L����
	for (/*������*/int i = 0; i < h; i++){
		for (/*������*/int j = 0; j < w; j++){
			// ���ړ_��LoG�l�̎擾
			double I = get_image_data(/*������*/img_LoG, i, j) - bias;

			// ��������(�E��)�̃`�F�b�N
			if (j + 1 < w){
				// �E�ׂ�LoG�l�̎擾
				double Ih = /*������*/get_image_data(img_LoG, i, j+1) - bias;

				// �[����������
				if (/*������*/I * Ih < 0.0){
					// �אړ_�ԂŐ�Βl���r
					if (fabs(I) < fabs(Ih)){
						img_zero_cross.at<unsigned char>(i, j) = UCHAR_MAX;
					}
					else{
						img_zero_cross.at<unsigned char>(i, j + 1) = UCHAR_MAX;
					}
				}
			}

			// ��������(����)�̃`�F�b�N
			if (i + 1 < h){
				// ���ׂ�LoG�l�̎擾
				double Iv = /*������*/get_image_data(img_LoG, i+1, j) - bias;

				// �[����������
				if (/*������*/I * Iv < 0.0){
					// �אړ_�ԂŐ�Βl���r
					if (fabs(I) < fabs(Iv)){
						/*������*/img_zero_cross.at<unsigned char>(i, j) = UCHAR_MAX;
					}
					else{
						/*������*/img_zero_cross.at<unsigned char>(i+1, j) = UCHAR_MAX;
					}
				}
			}
		}
	}

	return 0;
}



//*****************************************************************************
//	�ړI����: �[�������@�ɂ��G�b�W���o (�t�@�C�����o�͔�)
//	���͈���:
//		file_LoG:					LoG�摜�̓��̓t�@�C��
//		file_zero_cross:	�[�������摜�̏o�̓t�@�C��
//*****************************************************************************
int zero_cross_file(const char* file_LoG, const char* file_zero_cross)
{
	int			ret = 0;			// �߂�l�p�ϐ�
	cv::Mat		img_LoG;			// LoG�摜
	cv::Mat		img_zero_cross;		// �[�������摜


	// LoG�摜�̓ǂݍ���
	img_LoG = cv::imread(/*������*/file_LoG, CV_LOAD_IMAGE_ANYDEPTH);
	if (img_LoG.data == NULL){
		fprintf(stderr, "Error: cv::imread(%s)\n", file_LoG);
		ret = -1;
	}
	else{
		// �[�������摜�̃������m��
		// (LoG�摜�Ɠ����T�C�Y�C�F�[�x8�r�b�g�̃O���[�X�P�[���摜(�F�`���l����: 1))
		img_zero_cross = cv::Mat(/*������*/img_LoG.size(), CV_8U);
		if (img_zero_cross.data == NULL){
			fprintf(stderr, "Error: img_zero_cross = cv::Mat()\n");
			ret = -1;
		}
		else{
			// �[�������摜�̍쐬
			ret = /*������*/zero_cross(img_LoG, img_zero_cross);
			if (ret){
				fprintf(stderr, "Error: zero_cross.\n");
			}
			else{
				// �摜�̕ۑ�
				ret = /*������*/cv::imwrite(file_zero_cross,img_zero_cross);
				if (ret != 1){
					fprintf(stderr, "Error: cv::imwrite(%s).\n", file_zero_cross);
					ret = -1;
				}
				else{
					ret = 0;
				}
			}
		}
	}

	return ret;
}