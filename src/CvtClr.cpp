// ClrConv.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

//*****************************************************************************
//	目的説明: カラー画像からグレースケール画像への変換 (ファイル入出力版)
//	入力引数:
//		file_in:	カラー画像の入力ファイル名
//		fiel_out:	グレースケール画像の出力ファイル名
//*****************************************************************************
int clr2gray(const char* file_in, const char* file_out) {
	int	ret = 0;	  // 戻り値用変数
	cv::Mat	img_in; // 入力画像
	cv::Mat img_out;	 // 出力画像

	// 画像の読み込み
	img_in = cv::imread(file_in, CV_LOAD_IMAGE_COLOR);
	if (img_in.data == NULL) {
		fprintf(stderr, "Error: cv::imread(%s)\n", file_in);
		ret = -1;
	}
	else {
		// 出力画像メモリの確保
		// (入力画像と同じサイズ，色深度8ビットのグレースケール画像(色チャネル数: 1))
		img_out = cv::Mat(img_in.size(), CV_8U);
		if (img_out.data == NULL){
			fprintf(stderr, "Error: img_out = cv::Mat()\n");
			ret = -1;
		}
		else{
			// カラー画像からグレースケール画像への変換
			cv::cvtColor(img_in, img_out, CV_BGR2GRAY);

			// 画像の保存
			ret = cv::imwrite(file_out, img_out);
			if (ret != 1){
				fprintf(stderr, "Error: cv::imwrite(%s).\n", file_out);
				ret = -1;
			}
			else{
				ret = 0;
			}
		}
	}

	return ret;
}


//*****************************************************************************
//	目的説明: カラー画像からグレースケール画像への変換 (ファイル入出力版)
//	入力引数:
//		file_in:	カラー画像の入力ファイル名
//		fiel_out:	グレースケール画像の出力ファイル名
//*****************************************************************************
int clr2gray_old(const char* file_in, const char* file_out)
{
	int				ret = 0;					// 戻り値用変数
	IplImage*	p_img_in = NULL;	// 入力画像
	IplImage*	p_img_out = NULL;	// 出力画像
	CvSize		size;							// 画像サイズ


	// 画像の読み込み
	p_img_in = cvLoadImage(file_in, CV_LOAD_IMAGE_COLOR);
	if (!p_img_in){
		fprintf(stderr, "Error: cvLoadImage(%s)\n", file_in);
		ret = -1;
	}
	else{
	

		// 出力画像メモリの確保
		// (入力画像と同じサイズ，色深度8ビットのグレースケール画像(色チャネル数: 1))
		size = cvSize(p_img_in->width, p_img_in->height);
		p_img_out = cvCreateImage(size, IPL_DEPTH_8U, 1);
		if (!p_img_out){
			fprintf(stderr, "Error: p_img_out = cvCreateImage\n");
			ret = -1;
		}
		else{


			// カラー画像からグレースケール画像への変換
			cvCvtColor(p_img_in, p_img_out, CV_BGR2GRAY);


			// 画像の保存
			ret = cvSaveImage(file_out, p_img_out);
			if (ret != 1){
				fprintf(stderr, "Error: cvSaveImage(%s).\n", file_out);
				ret = -1;
			}
			else{
				ret = 0;
			}
		}
	}


	// 画像メモリの解放
	cvReleaseImage(&p_img_in);
	cvReleaseImage(&p_img_out);

	return ret;
}
