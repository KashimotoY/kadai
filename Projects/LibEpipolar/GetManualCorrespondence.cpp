//GetManualCorrespondence..cpp

#include <stdio.h>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "Epipolar.h"


#ifndef N_STR
#define N_STR 200
#endif

struct GMC{
	char		m_window_name1[N_STR];	//画像１に対するウィンドウ名	
	cv::Mat		m_img_in1;				//入力画像１
	cv::Mat		m_img_out1;				//出力画像１
	int			m_n_pt_max;				//最大対応点数
	point_list	m_pt1;					//画像における対応点
	int			m_n_pt1;				//画像の対応点数
	int			m_radius;				//対応点の描画円の半径
};

//*****************************************************************************
//	目的説明: 手動対応点取得関数（ファイル入力版）
//	引数:
//		file_img_in1:	1枚目の画像ファイル名
//		file_img_in2:	2枚目の画像ファイル名
//		file_pt:		
//		n_pt_max:		
//		radius:		
//		
//*****************************************************************************
int GetManualCorrespondence(const char* file_img_in1, const char* file_img_in2, const char* file_pt, int n_pt_max, int radius){

	int ret;


	return ret;

}


//*****************************************************************************
//	目的説明: 対応点を保存する関数
//	引数:
//		file_pt:
//		n_pt:
//		pt1:
//		pt2:
//		
//*****************************************************************************
int SaveCorrespondence(const char* file_pt, int n_pt, point_list &pt1, point_list &pt2){

	int ret;

	
	return ret;

}


//*****************************************************************************
//	目的説明: 対応点を読み込みする関数
//	引数:
//		file_pt:
//		n_pt:
//		pt1:
//		pt2:
//		
//*****************************************************************************
int LoadCorrespondence(const char* file_pt, int n_pt, point_list &pt1, point_list &pt2){

	int ret;


	return ret;

}

//*****************************************************************************
//	目的説明: マウスイベント関数
//	引数:
//		event:
//		x:
//		y:
//		flags:
//		param:
//		
//*****************************************************************************
void on_mouse1(int event, int x, int y, int flags, void* param){


}


//*****************************************************************************
//	目的説明: マウスイベント関数
//	引数:
//		event:
//		x:
//		y:
//		flags:
//		param:
//		
//*****************************************************************************
void on_mouse2(int event, int x, int y, int flags, void* param){


}

