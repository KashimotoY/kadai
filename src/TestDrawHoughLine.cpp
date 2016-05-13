// TestDrawHoughLine.cpp

// ヘッダファイルのインクルード
/*穴埋め*/#include <opencv2/opencv.hpp>
#include <cstdio>
#include "Hough.h"

#define CLR_R			0
#define CLR_G			255
#define CLR_B			0
#define THICKNESS	1

// メイン関数
int main(int argc, char** argv)
{
	// 変数宣言
	/*穴埋め*/
	int ret;
	char* file_in;
	char* file_line;
	char* file_out;
	cv::Scalar clr = cv::Scalar(CLR_B, CLR_G, CLR_R);
	int thickness = THICKNESS;


	// 引数チェックと変数の設定
	if (argc < 4){
		fprintf(stderr, "Usage: DrawHoughLineTest file_in file_line file_out [clr_R] [clr_G] [clr_B] [thickness]\n");
		return -1;
	}

	/*穴埋め*/
	file_in = argv[1];
	file_line = argv[2];
	file_out = argv[3];

	// rho-theta直線の描画
	ret = draw_hough_lines_file(file_in, file_line, file_out, clr, thickness);
	if (ret){
		fprintf(stderr, "Error: draw_hough_lines_file.\n");
		return -1;
	}

	return 0;
}