// TestLoGFilter.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Edge.h"

// デフォルト引数用の定数
#define DEF_SIGMA 2.0
#define DEF_DEPTH CV_8U


// メイン関数
int main(int argc, char** argv)
{
	int			ret;			// 戻り値用変数
	char*		file_in;		// 入力ファイル名
	char*		file_LoG;	// 出力ファイル名
	double		sigma;		// LoGフィルタの標準偏差
	int			depth;		// 出力画像の色深度

	// 引数チェックと変数の設定
	if (argc < 3){
		fprintf(stderr, "Usage: LoGFilterTest file_in file_LoG [sigma] [depth]\n");
		return -1;
	}
	file_in = argv[1];
	file_LoG = argv[2];
	sigma = (argc >= 4) ? atof(argv[3]) : DEF_SIGMA;
	depth = (argc >= 5) ? atoi(argv[4]) : DEF_DEPTH;

	// LoG フィルタ
	ret = LoG_file(file_in, file_LoG, sigma, depth);
	if (ret){
		fprintf(stderr, "Error: LoG\n");
		return -1;
	}

	return 0;
}