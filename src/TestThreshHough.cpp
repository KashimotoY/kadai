// TestThreshHough.cpp

// ヘッダファイルのインクルード
/*穴埋め*/#include <opencv2/opencv.hpp>
#include <cstdio>
#include "Hough.h"

#define N_LINE_MAX 100

// メイン関数
int main(int argc, char** argv)
{
	// 変数宣言
	/*穴埋め*/
	int ret;
	char* file_vote;
	char* file_line;
	int thresh;
	int n_line_max = N_LINE_MAX;

	// 引数チェックと変数の設定
	if (argc < 4){
		fprintf(stderr, "Usage: HoughThreshTest file_vote file_line thresh [n_line_max]\n");
		return -1;
	}

	/*穴埋め*/
	file_vote = argv[1];
	file_line = argv[2];
	thresh = atoi(argv[3]);

	// ハフ投票画像から閾値以上のパラメタを取得
	ret = thresh_hough_file(file_vote, file_line, thresh, n_line_max);
	if (ret){
		fprintf(stderr, "Error: thresh_hough_file.\n");
		return -1;
	}

	return 0;
}