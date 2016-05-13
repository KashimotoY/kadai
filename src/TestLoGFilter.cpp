// TestLoGFilter.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Edge.h"

// �f�t�H���g�����p�̒萔
#define DEF_SIGMA 2.0
#define DEF_DEPTH CV_8U


// ���C���֐�
int main(int argc, char** argv)
{
	int			ret;			// �߂�l�p�ϐ�
	char*		file_in;		// ���̓t�@�C����
	char*		file_LoG;	// �o�̓t�@�C����
	double		sigma;		// LoG�t�B���^�̕W���΍�
	int			depth;		// �o�͉摜�̐F�[�x

	// �����`�F�b�N�ƕϐ��̐ݒ�
	if (argc < 3){
		fprintf(stderr, "Usage: LoGFilterTest file_in file_LoG [sigma] [depth]\n");
		return -1;
	}
	file_in = argv[1];
	file_LoG = argv[2];
	sigma = (argc >= 4) ? atof(argv[3]) : DEF_SIGMA;
	depth = (argc >= 5) ? atoi(argv[4]) : DEF_DEPTH;

	// LoG �t�B���^
	ret = LoG_file(file_in, file_LoG, sigma, depth);
	if (ret){
		fprintf(stderr, "Error: LoG\n");
		return -1;
	}

	return 0;
}