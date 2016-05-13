// ZeroCrossTest.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Edge.h"


// ���C���֐�
int main(int argc, char** argv)
{
	int		ret = 0;				// �߂�l�p�ϐ�
	char*	file_LoG;			// LoG�摜�̓��̓t�@�C����
	char*	file_zero_cross;		// ZeroCross�摜�̏o�̓t�@�C����

	// �����`�F�b�N�ƕϐ��̐ݒ�
	if (argc < 3){
		fprintf(stderr, "Usage: ZeroCrossTest file_LoG file_zero_cross\n");
		return -1;
	}
	file_LoG = argv[1];
	file_zero_cross = argv[2];

	// �[������
	ret = zero_cross_file(file_LoG, file_zero_cross);
	if (ret){
		fprintf(stderr, "Error: zero_cross\n");
		return -1;
	}

	return ret;
}