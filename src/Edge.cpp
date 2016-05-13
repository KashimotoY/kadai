// Edge.cpp

#include <stdio.h>
#include <algorithm>

#include <opencv2/opencv.hpp>
#include "Edge.h"


/**
 * 画像mのピクセル(i, j)の値を取得する
 */
int get_image_data(cv::Mat m, int i, int j) {
	if (m.depth() == CV_8U)
		return m.at<unsigned char>(i, j);
	else
		return m.at<unsigned short>(i, j);
}


/**
 * 画像mのピクセル(i, j)に値valを代入する
 * Note: 負値は0，depthの最大値を超える値は最大値に変換される
 */
void set_image_data(cv::Mat m, int i, int j, double val) {
	int t = (int)round(val);
	if (m.depth() == CV_8U) {
		t = std::min(UCHAR_MAX, std::max(0, t));
		m.at<unsigned char>(i, j) = t;
	}
	else {
		t = std::min(USHORT_MAX, std::max(0, t));
		m.at<unsigned short>(i, j) = t;
	}
}


//*****************************************************************************
//	目的説明: LoG (Laplacian of Gaussian)フィルタ
//	入力引数:
//		img_in:		入力画像
//		sigma:		LoGフィルタの標準偏差
//		bias:		LoG画像のバイアス
//	出力引数:
//		img_LoG:		LoG画像
//*****************************************************************************
int LoG(cv::Mat img_in, cv::Mat img_LoG, double sigma, double bias)
{
	cv::Mat		img_op;							// オペレータ画像
	int			w, h;							// 画像の幅と高さ
	double		sigma2 = sigma * sigma;			// 標準偏差の2乗
	int			r2;								// 半径の2乗
	int			range_op = (int)(3.0 * sigma);	// オペレータ範囲


	//----------------------
	// 画像ポインタチェック
	//----------------------

	// 入力画像
	if (img_in.data == NULL) {
		fprintf(stderr, "Error: img_in is NULL.\n");
		return -1;
	}

	// LoG画像
	// (穴埋め)
	if (img_LoG.data == NULL) {
		fprintf(stderr, "Error: img_LoG is NULL.\n");
		return -1;
	}
	//
	

	//---------------------------
	// 画像フォーマットチェック
	//---------------------------

	// 入力画像サイズの取得
	w = img_in.size().width;
	h = img_in.size().height;

	// LoG画像のサイズをチェック
	if (img_LoG.size() != img_in.size()){
		fprintf(stderr, "Error: sizes of img_in and img_LoG are incompatible.\n");
		return -1;
	}

	// 入力画像の色チャンネル数のチェック
	if (img_in.channels() != 1) {
		fprintf(stderr, "Error: img_in.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}

	// LoG画像の色チャンネル数のチェック
	// (穴埋め)
	if (img_LoG.channels() != 1) {
		fprintf(stderr, "Error: img_LoG.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}
	//


	// LoG画像のデプスのチェック
	if (img_LoG.depth() != CV_8U && img_LoG.depth() != CV_16U) {
		fprintf(stderr, "Error: img_LoG.depth() must be CV_8U or CV_16U.\n");
		return -1;
	}

	// 標準偏差が正かどうかをチェック
	// (穴埋め)
	if (!(sigma > 0)){
		fprintf(stderr, "Error: sigma must be over 0");
		return -1;
	}
	//

	//-------------------------------
	//	LoGフィルタのオペレータ作成
	//-------------------------------

	// オペレータ用のメモリ確保
	cv::Size size_op = cv::Size(/*穴埋め*/range_op*2+1, /*穴埋め*/range_op*2+1);
	img_op = cv::Mat(size_op, CV_64F);
	if (img_op.data == NULL) {
		fprintf(stderr, "Error: img_op = cv::Mat().\n");
		return -1;
	}

	// オペレータの設定
	double a = 0;
	for (int k = -range_op; k <= range_op; k++){
		for (int l = -range_op; l <= range_op; l++){
			r2 =/*穴埋め*/l*l + k*k;
			double op = /*穴埋め*/(r2/(sigma2) - 2)*exp(-r2/(2*sigma2));
			img_op.at<double>(/*穴埋め*/k + range_op, /*穴埋め*/l + range_op) = op;
			a += op;
		}
	}

	//-----------------------------------
	// 入力画像とオペレータとの畳み込み
	//-----------------------------------
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			double sum = /*穴埋め*/0;

			for (int k = -range_op; k <= range_op; k++){
				for (int l = -range_op; l <= range_op; l++){
					// 計算対象の座標値が画像内に収まるかどうかをチェック
					if (/*穴埋め*/i+k >= 0 && i+k < h && j+l >= 0 && j+l < w) {
						double op = img_op.at<double>(/*穴埋め*/k+range_op, /*穴埋め*/l+range_op);
						sum += op * /*穴埋め*/img_in.at<unsigned char>(i + k, j + l);
					}
				}
			}
			
			set_image_data(/*穴埋め*/img_LoG, i, j, sum+bias);
		}
	}

	return 0;
}

//*****************************************************************************
//	目的説明: LoG (Laplacian of Gaussian)フィルタ(ファイル入出力版)
//	入力引数:
//		file_in:		入力画像ファイル名
//		file_LoG:		LoG画像ファイル名
//		sigma:			LoGフィルタの標準偏差
//		depth:			LoG画像の色深度
//*****************************************************************************
int LoG_file(const char* file_in, const char* file_LoG, double sigma, int depth)
{
	int			ret;			// 戻り値用変数
	cv::Mat		img_in;			// 入力画像
	cv::Mat		img_LoG;		// LoG画像
	double		bias;

	// depthのチェックとバイアスの設定
	if (depth == CV_8U) bias = CHAR_MAX;
	else if (depth == CV_16U) bias = SHORT_MAX;
	else{
		fprintf(stderr, "Error: depth should be CV_8U or CV_16U.\n");
		return -1;
	}

	// 画像の読み込み
	img_in = /*穴埋め*/cv::imread(file_in, CV_LOAD_IMAGE_GRAYSCALE);
	if (img_in.data == NULL){
		fprintf(stderr, "Error: cv::imread(%s)\n", file_in);
		ret = -1;
	}
	else{
		// LoG画像メモリの確保
		// (入力画像と同じサイズ，指定色深度のグレースケール画像(色チャネル数: 1))
		img_LoG = /*穴埋め*/cv::Mat(img_in.size(), depth);
		if (img_LoG.data == NULL){
			fprintf(stderr, "Error: img_LoG = cv::Mat()\n");
			ret = -1;
		}
		else{
			// LoGフィルタの適用
			ret = /*穴埋め*/LoG(img_in, img_LoG, sigma, bias);
			if (ret){
				fprintf(stderr, "Error: LoG().\n");
			}
			else{
				// 画像の保存
				ret = /*穴埋め*/cv::imwrite(file_LoG, img_LoG);
				if (ret != 1){
					fprintf(stderr, "Error: cv::imwrite(%s).\n", file_LoG);
					ret = -1;
				}
				else{
					ret = 0;
				}				
			}
		}
	}

	return ret;
}


//*****************************************************************************
//	目的説明: ゼロ交差法によるエッジ抽出
//	入力引数:
//		p_img_LoG:				LoG画像
//	出力引数:
//		p_img_zero_cross:	ゼロ交差画像
//*****************************************************************************
int zero_cross(cv::Mat img_LoG, cv::Mat img_zero_cross)
{
	int		w, h;		// 画像の幅と高さ
	double	bias;		// LoG画像のバイアス


	//----------------------
	// 画像データチェック
	//----------------------

	// LoG画像
	/*穴埋め*/
	if (img_LoG.data == NULL) {
		fprintf(stderr, "Error: img_LoG is NULL.\n");
		return -1;
	}
	/**/
	
	// ゼロ交差画像
	/*穴埋め*/
	if (img_zero_cross.data == NULL) {
		fprintf(stderr, "Error: img_zero_cross is NULL.\n");
		return -1;
	}
	/**/


	//---------------------------
	// 画像フォーマットチェック
	//---------------------------

	// ゼロ交差画像の幅・高さのチェック
	/*穴埋め*/
	if (img_LoG.size() != img_zero_cross.size()){
		fprintf(stderr, "Error: sizes of img_zero_cross and img_LoG are incompatible.\n");
		return -1;
	}
	/**/

	w = img_LoG.size().width;
	h = img_LoG.size().height;

	// LoG画像・ゼロ交差画像の色チャンネル数のチェック
	/*穴埋め*/
	if (img_LoG.channels() != 1) {
		fprintf(stderr, "Error: img_LoG.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}

	if (img_zero_cross.channels() != 1) {
		fprintf(stderr, "Error: img_zero_cross.channels() is not 1 (not gray-scale image).\n");
		return -1;
	}
	/**/


	// depthのチェックとバイアスの設定
	if (img_LoG.depth() == CV_8U) bias = CHAR_MAX;
	else if (img_LoG.depth() == CV_16U) bias = SHORT_MAX;
	else{
		fprintf(stderr, "Error: img_LoG.depth() should be CV_8U or CV_16U.\n");
		return -1;
	}


	//-------------------
	// ゼロ交差点の算出
	//-------------------

	// ゼロ交差点画像の初期化
	img_zero_cross.setTo(/*穴埋め*/0, img_zero_cross);
	// 各画素をスキャン
	for (/*穴埋め*/int i = 0; i < h; i++){
		for (/*穴埋め*/int j = 0; j < w; j++){
			// 注目点のLoG値の取得
			double I = get_image_data(/*穴埋め*/img_LoG, i, j) - bias;

			// 水平方向(右隣)のチェック
			if (j + 1 < w){
				// 右隣のLoG値の取得
				double Ih = /*穴埋め*/get_image_data(img_LoG, i, j+1) - bias;

				// ゼロ交差判定
				if (/*穴埋め*/I * Ih < 0.0){
					// 隣接点間で絶対値を比較
					if (fabs(I) < fabs(Ih)){
						img_zero_cross.at<unsigned char>(i, j) = UCHAR_MAX;
					}
					else{
						img_zero_cross.at<unsigned char>(i, j + 1) = UCHAR_MAX;
					}
				}
			}

			// 垂直方向(下隣)のチェック
			if (i + 1 < h){
				// 下隣のLoG値の取得
				double Iv = /*穴埋め*/get_image_data(img_LoG, i+1, j) - bias;

				// ゼロ交差判定
				if (/*穴埋め*/I * Iv < 0.0){
					// 隣接点間で絶対値を比較
					if (fabs(I) < fabs(Iv)){
						/*穴埋め*/img_zero_cross.at<unsigned char>(i, j) = UCHAR_MAX;
					}
					else{
						/*穴埋め*/img_zero_cross.at<unsigned char>(i+1, j) = UCHAR_MAX;
					}
				}
			}
		}
	}

	return 0;
}



//*****************************************************************************
//	目的説明: ゼロ交差法によるエッジ抽出 (ファイル入出力版)
//	入力引数:
//		file_LoG:					LoG画像の入力ファイル
//		file_zero_cross:	ゼロ交差画像の出力ファイル
//*****************************************************************************
int zero_cross_file(const char* file_LoG, const char* file_zero_cross)
{
	int			ret = 0;			// 戻り値用変数
	cv::Mat		img_LoG;			// LoG画像
	cv::Mat		img_zero_cross;		// ゼロ交差画像


	// LoG画像の読み込み
	img_LoG = cv::imread(/*穴埋め*/file_LoG, CV_LOAD_IMAGE_ANYDEPTH);
	if (img_LoG.data == NULL){
		fprintf(stderr, "Error: cv::imread(%s)\n", file_LoG);
		ret = -1;
	}
	else{
		// ゼロ交差画像のメモリ確保
		// (LoG画像と同じサイズ，色深度8ビットのグレースケール画像(色チャネル数: 1))
		img_zero_cross = cv::Mat(/*穴埋め*/img_LoG.size(), CV_8U);
		if (img_zero_cross.data == NULL){
			fprintf(stderr, "Error: img_zero_cross = cv::Mat()\n");
			ret = -1;
		}
		else{
			// ゼロ交差画像の作成
			ret = /*穴埋め*/zero_cross(img_LoG, img_zero_cross);
			if (ret){
				fprintf(stderr, "Error: zero_cross.\n");
			}
			else{
				// 画像の保存
				ret = /*穴埋め*/cv::imwrite(file_zero_cross,img_zero_cross);
				if (ret != 1){
					fprintf(stderr, "Error: cv::imwrite(%s).\n", file_zero_cross);
					ret = -1;
				}
				else{
					ret = 0;
				}
			}
		}
	}

	return ret;
}