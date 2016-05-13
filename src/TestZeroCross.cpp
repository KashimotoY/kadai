// ZeroCrossTest.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Edge.h"


// メイン関数
int main(int argc, char** argv)
{
	int		ret = 0;				// 戻り値用変数
	char*	file_LoG;			// LoG画像の入力ファイル名
	char*	file_zero_cross;		// ZeroCross画像の出力ファイル名

	// 引数チェックと変数の設定
	if (argc < 3){
		fprintf(stderr, "Usage: ZeroCrossTest file_LoG file_zero_cross\n");
		return -1;
	}
	file_LoG = argv[1];
	file_zero_cross = argv[2];

	// ゼロ交差
	ret = zero_cross_file(file_LoG, file_zero_cross);
	if (ret){
		fprintf(stderr, "Error: zero_cross\n");
		return -1;
	}

	return ret;
}