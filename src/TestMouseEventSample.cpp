// TestMouseSampleEvent.cpp

#include <stdio.h>
#include "Epipolar.h"

#define DEF_CLR_R		0
#define DEF_CLR_G		255
#define DEF_CLR_B		0
#define DEF_THICKNESS	1
#define DEF_RADIUS		3

#pragma comment (lib, "LibEpipolar.lib")

//*****************************************************************************
// メイン関数
//*****************************************************************************
int main(int argc, char** argv)
{
	int				ret;
	char*			file_img_in1;		// 入力画像1のファイル名
	char*			file_img_in2;		// 入力画像2のファイル名
	cv::Scalar		clr;				// 描画色
	int				thickness;			// 描画太さ
	int				radius;				// 円描画の半径

	// 引数チェックと変数の初期化
	if (argc < 3){
		fprintf(stderr, "usage: MouseEventSample file_img_in1 file_img_in2.\n");
		return -1;
	}
	file_img_in1 = argv[1];
	file_img_in2 = argv[2];
	clr = (argc >= 6) ? CV_RGB(atoi(argv[3]), atoi(argv[4]), atoi(argv[5])) : CV_RGB(DEF_CLR_R, DEF_CLR_G, DEF_CLR_B);
	thickness = (argc >= 7) ? atoi(argv[6]) : DEF_THICKNESS;
	radius = (argc >= 8) ? atoi(argv[7]) : DEF_RADIUS;

	// マウスイベントサンプル
	ret = MouseEventSample(file_img_in1, file_img_in2, clr, thickness, radius);
	if (ret){
		fprintf(stderr, "Error: MouseEventSample.\n");
		return -1;
	}

	return 0;
}