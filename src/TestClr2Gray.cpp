// TestClr2Gray.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "CvtClr.h"


// メイン関数
int main(int argc, char** argv)
{
	int		ret;			// 戻り値用変数
	char*	file_in;	// 入力ファイル名
	char*	file_out;	// 出力ファイル名

	// 引数チェックと変数の設定
	if (argc < 3){
		fprintf(stderr, "Usage: Clr2GrayTest file_in file_out\n");
		return -1;
	}
	file_in = argv[1];
	file_out = argv[2];


	// カラー画像からグレースケール画像に変換
	ret = clr2gray(file_in, file_out);
	if (ret){
		fprintf(stderr, "Error: clr2gray\n");
		return -1;
	}


	return 0;
}