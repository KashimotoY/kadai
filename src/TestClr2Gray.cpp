// TestClr2Gray.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "CvtClr.h"


// ���C���֐�
int main(int argc, char** argv)
{
	int		ret;			// �߂�l�p�ϐ�
	char*	file_in;	// ���̓t�@�C����
	char*	file_out;	// �o�̓t�@�C����

	// �����`�F�b�N�ƕϐ��̐ݒ�
	if (argc < 3){
		fprintf(stderr, "Usage: Clr2GrayTest file_in file_out\n");
		return -1;
	}
	file_in = argv[1];
	file_out = argv[2];


	// �J���[�摜����O���[�X�P�[���摜�ɕϊ�
	ret = clr2gray(file_in, file_out);
	if (ret){
		fprintf(stderr, "Error: clr2gray\n");
		return -1;
	}


	return 0;
}