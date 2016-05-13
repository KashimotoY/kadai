// TestEdge2Hough.cpp

// ヘッダファイルのインクルード
/*穴埋め*/#include <opencv2/opencv.hpp>
#include <cstdio>
#include "Hough.h"

// メイン関数
int main(int argc, char** argv)
{
	// 変数宣言
	/*穴埋め*/
	int ret;
	char* file_edge;
	char* file_vote;

	// 引数チェックと変数の設定
	if (argc < 3){
		fprintf(stderr, "Usage: Edge2HoughTest file_edge file_vote\n");
		return -1;
	}

	/*穴埋め*/
	file_edge = argv[1];
	file_vote = argv[2];

	// ハフ変換
	ret = edge2hough_file(file_edge, file_vote);
	if (ret){
		fprintf(stderr, "Error: edge2hough_file");
		return -1;
	}

	return 0;
}