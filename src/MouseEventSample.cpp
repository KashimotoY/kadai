// MouseEventSample.cpp

#include <stdio.h>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "Epipolar.h"


#ifndef N_STR
#define N_STR 200
#endif


//-------------------------------------------
// マウスイベントサンプルを扱うための構造体
//-------------------------------------------
struct MES
{
	char		m_window_name1[N_STR];	// 画像1に対するウィンドウ名
	char		m_window_name2[N_STR];	// 画像2に対するウィンドウ名
	cv::Mat		img_in1;				// 入力画像1
	cv::Mat		img_in2;				// 入力画像2
	cv::Mat		img_out1;				// 出力画像1
	cv::Mat		img_out2;				// 出力画像2
	cv::Scalar	m_clr;					// 指定点に描画する円の色
	int			m_thickness;			// 指定点に描画する円の太さ
	int			m_radius;				// 指定点に描画する円の半径
	cv::Point	m_pt_l;					// 左ボタンクリック点
	cv::Point	m_pt_r;					// 右ボタンクリック点
};


// 今後の画像処理実習課題で，on_mouse1,2を使用する際に衝突を避けるために，
// namespace NS_MouseEventSampleを利用

//*****************************************************************************
// ウィンドウ1に対するマウスイベント
//*****************************************************************************
namespace NS_MouseEventSample{
	void on_mouse1(int event, int x, int y, int flags, void* param)
	{
		MES &mes = *(MES *)param;

		// マウスムーブイベント
		if (event == CV_EVENT_MOUSEMOVE){

			fprintf(stderr, "画像1上の点(%d, %d)をマウスが移動中です．\n", x, y);

			// 円を描画して表示
			mes.img_in1.copyTo(mes.img_out1);
			cv::circle(mes.img_out1, cv::Point(x, y), mes.m_radius, mes.m_clr, mes.m_thickness);
			cv::imshow(mes.m_window_name1, mes.img_out1);
		}

		return;
	}
};

//*****************************************************************************
// ウィンドウ2に対するマウスイベント
//*****************************************************************************
namespace NS_MouseEventSample{
	void on_mouse2(int event, int x, int y, int flags, void* param)
	{
		MES &mes = *(MES *)param;
		static int cnt = 0;

		// 左ボタンUPイベント
		if (event == CV_EVENT_LBUTTONUP){

			fprintf(stderr, "画像2上の点(%d,%d)が左クリックされました．\n", x, y);
			mes.m_pt_l = cvPoint(x, y);

			// 出力画像のクリア(入力画像で上書き)
			mes.img_in2.copyTo(mes.img_out2);

			// 円を描画して表示
			cv::circle(mes.img_out2, cv::Point(x, y), mes.m_radius, mes.m_clr, mes.m_thickness);
			cv::imshow(mes.m_window_name2, mes.img_out2);
		}

		// 右ボタンUPイベント
		else if (event == CV_EVENT_RBUTTONUP){

			fprintf(stderr, "画像2上の点(%d,%d)が右クリックされました．\n", x, y);
			mes.m_pt_r = cvPoint(x, y);

			// 直線を描画
			cv::line(mes.img_out2, mes.m_pt_l, mes.m_pt_r, id2clr(cnt));
			cv::imshow(mes.m_window_name2, mes.img_out2);

			// カウンタ更新
			cnt++;
		}

		return;
	}
};

using NS_MouseEventSample::on_mouse1;
using NS_MouseEventSample::on_mouse2;


//*****************************************************************************
// マウスイベントサンプル関数
//*****************************************************************************
int MouseEventSample(const char* file_img_in1, const char* file_img_in2, cv::Scalar clr, int thickness, int radius)
{
	int ret = 0;
	MES	mes;			// マウスイベントサンプルを扱うための構造体
	int w, h, nc;	// 画像の幅・高さ・色チャンネル数

	// 変数の初期化
	strncpy_s(mes.m_window_name1, N_STR, "Window 1", N_STR); 
	strncpy_s(mes.m_window_name2, N_STR, "Window 2", N_STR); 
	mes.m_clr = clr;
	mes.m_thickness = thickness;
	mes.m_radius = radius;


	//-------------------
	// 入力画像のロード
	//-------------------
	mes.img_in1 = cv::imread(file_img_in1);
	if (mes.img_in1.data == NULL){
		fprintf(stderr, "fail in cv::imread(%s).\n", file_img_in1);
		ret = -1;
	}
	else{

		mes.img_in2 = cv::imread(file_img_in2);
		if (mes.img_in2.data == NULL){
			fprintf(stderr, "Error: cv::imread(%s).\n", file_img_in2);
			ret = -1;
		}
		else{
			//------------
			// メモリ確保
			//------------
			nc = mes.img_in1.channels();
			mes.img_out1 = cv::Mat(mes.img_in1.size(), CV_8UC(nc));
			if (mes.img_out1.data == NULL){
				fprintf(stderr, "Error: mes.m_p_img_out1 = cv::Mat()\n");
				ret = -1;;
			}
			else{
				nc = mes.img_in2.channels();
				mes.img_out2 = cv::Mat(mes.img_in2.size(), CV_8UC(nc));
				if (mes.img_out2.data == NULL){
					fprintf(stderr, "Error: mes.m_p_img_out2 = cv::Mat()\n");
					return -1;
				}
				else{
					//-------------------
					// ウィンドウの作成
					//-------------------
					cv::namedWindow(mes.m_window_name1, CV_WINDOW_AUTOSIZE);
					cv::moveWindow(mes.m_window_name1, 0, 0);

					cv::namedWindow(mes.m_window_name2, CV_WINDOW_AUTOSIZE);
					cv::moveWindow(mes.m_window_name2, mes.img_in1.size().width + 20, 0);

					//-------------
					// 画像の表示
					//-------------
					cv::imshow(mes.m_window_name1, mes.img_in1);
					cv::imshow(mes.m_window_name2, mes.img_in2);

					//-------------------------------
					// マウスコールバック関数の設定
					//-------------------------------
					cv::setMouseCallback(mes.m_window_name1, (cv::MouseCallback)&on_mouse1, &mes);
					cv::setMouseCallback(mes.m_window_name2, (cv::MouseCallback)&on_mouse2, &mes);

					// キーが押されるまで待機(マウスイベント処理)
					cv::waitKey(-1);

					//-------------------
					// ウィンドウの解放
					//-------------------
					cv::destroyWindow(mes.m_window_name1);
					cv::destroyWindow(mes.m_window_name2);
				}
			}
		}
	}

	return ret;
}
