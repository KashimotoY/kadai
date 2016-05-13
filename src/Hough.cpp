// Hough.cpp

#include <cstdio>

#include <opencv2/opencv.hpp>

#include "Hough.h"

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
		t = std::min(USHRT_MAX, std::max(0, t));
		m.at<unsigned short>(i, j) = t;
	}
}

//*****************************************************************************
//	目的説明: エッジ画像からハフ変換を行い，ハフ空間の投票画像を取得する
//	入力引数:
//		img_edge:	エッジ画像
//	出力引数:
//		img_vote:	ハフ空間の投票画像(メモリ確保済み)
//*****************************************************************************
void edge2hough(cv::Mat img_edge, cv::Mat img_vote)
{
	// 変数宣言
	int		w, h;			// 画像の幅と高さ
	int		n_rho, n_theta;	// rho, thetaの投票ビン数

	// 変数の初期化
	/*穴埋め*/
	w = img_edge.size().width;
	h = img_edge.size().height;
	n_rho = img_vote.size().width;
	n_theta = img_vote.size().height;


	// 投票空間の初期化
	/*穴埋め*/
	img_vote.setTo(0, img_vote);

	// 投票空間の取得
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){

			// エッジ点に対して投票
			if (/*穴埋め*/get_image_data(img_edge,i,j) == GMAX){

				// 直線の方向(theta)を変化させて投票
				for (/*穴埋め*/int k = 0; k < 180; k++){

					// rho値の計算
					int rho = /*穴埋め*/(int)(j*cos(k * M_PI / 180) + i*sin(k* M_PI / 180));
					int theta;

					// rho値が負なら，theta値を調整して正にする
					if (rho < 0){
						rho = -rho;
						/*穴埋め*/
						if (k < 180)theta = k + 180;
						else theta = k - 180;
					}
					else {
						theta = k;
					}

					if (rho > n_rho - 1){
						fprintf(stderr, "Error: rho(%d) is over n_rho(%d).\n", rho, n_rho);
						return;
					}

					// 投票
					double vote = /*穴埋め*/get_image_data(img_vote, theta, rho);
					if (vote < GMAX) /*穴埋め*/vote++;
					set_image_data(/*穴埋め*/img_vote, theta, rho, vote);
				}
			}
		}
	}

	return;
}

//*****************************************************************************
//	目的説明: エッジ画像からハフ変換を行い，ハフ空間の投票画像を取得する(ファイル入出力版)
//	入力引数:
//		file_edge:	入力のエッジ画像ファイル名
//		file_vote:	出力の投票画像ファイル名
//*****************************************************************************
int edge2hough_file(const char* file_edge, const char* file_vote)
{
	// 変数宣言
	int			ret;		// 戻り値用変数
	cv::Mat		img_edge;	// エッジ画像
	cv::Mat		img_vote;	// 投票画像(行: theta, 列: rho)
	int			w, h;		// エッジ画像の幅と高さ
	cv::Size	size;		// 投票画像のサイズ

	// エッジ画像の読み込み
	/*穴埋め*/
	img_edge = cv::imread(file_edge, CV_LOAD_IMAGE_GRAYSCALE);
	if (img_edge.data == NULL){
		fprintf(stderr, "Error: img_zero_cross = cv::Mat()\n");
		ret = -1;
	}
	else {
		// 投票空間のサイズ取得
		h = img_edge.size().height;
		w = img_edge.size().width;
		size.width = /*穴埋め*/sqrt(h*h + w*w);
		size.height = /*穴埋め*/360;

		// 投票画像メモリの確保
		// (rho-theta空間と同じサイズ，指定色深度のグレースケール画像(色チャネル数: 1))
		/*穴埋め*/
		img_vote = cv::Mat(size, CV_8U);
		if (img_vote.data == NULL){
			fprintf(stderr, "Error: img_zero_cross = cv::Mat()\n");
			ret = -1;
		}
		else {
			// 投票画像の作成
			/*穴埋め*/
			edge2hough(img_edge,img_vote);

			// 画像の保存
			/*穴埋め*/
			ret = cv::imwrite(file_vote, img_vote);
			if (ret != 1){
				fprintf(stderr, "Error: cv::imwrite(%s).\n", file_vote);
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
//	目的説明:	ハフ投票画像から閾値以上のパラメタを取得
//	入力引数:
//		img_vote:	投票画像
//		thresh:		投票の閾値
//		n_line_max:	直線の最大数
//	出力引数:
//		n_line:		直線数
//		rhos:		rho配列
//		thetas:		theta配列
//*****************************************************************************
int thresh_hough(cv::Mat img_vote, int &n_line, vector<int> &rhos, vector<int> &thetas, int thresh, int n_line_max)
{
	bool	max_flag;			// 極大チェック用のフラグ変数
	int		n_rho, n_theta;		// theta, rhoのbin数
	int		rho_nb, theta_nb;	// theta, rhoの近傍点

	// 初期化
	n_line = 0;
	n_rho = img_vote.size().width;
	n_theta = img_vote.size().height;

	// 閾値以上かつ極大の点(隣接点と比較して投票数が多い点)の取得
	for (/*穴埋め*/int rho = 0; rho < n_rho; rho++){
		for (/*穴埋め*/int theta = 0; theta < n_theta; theta++){

			int a = get_image_data(img_vote, 0, 0);
			// 投票数が閾値未満であれば処理しない
			/*穴埋め*/if (get_image_data(img_vote, theta, rho) < thresh)continue;

			//--------------
			// 極大チェック
			//--------------
			// 極大フラグを立てる
			/*穴埋め*/max_flag = true;

			// 近傍画素に対するループ
			for (int d_theta = -1; d_theta <= 1; d_theta++){
				for (int d_rho = -1; d_rho <= 1; d_rho++){

					// 近傍点に対するrho, thetaを算出(thetaについては周期性を考慮)
					theta_nb = (theta + /*穴埋め*/d_theta + /*穴埋め*/360) % /*穴埋め*/360;
					rho_nb = rho + d_rho;

					// rhoが負なら，直線の方向(theta)を調整して対応
					if (rho_nb < 0){
						/*穴埋め*/
						rho = -rho;
						if (theta_nb < 180)theta_nb = theta_nb + 180;
						else theta_nb = theta_nb - 180;
					}

					// 近傍点と投票値を比較して，近傍点の方が大きければ，極大フラグを下ろしてbreak
					double vote_nb = /*穴埋め*/get_image_data(img_vote, theta_nb, rho_nb);
					if (vote_nb > /*穴埋め*/get_image_data(img_vote, theta, rho)){
						max_flag = /*穴埋め*/false;
						break;
					}
				}
				if (max_flag == false) break;
			}

			// 極大点であれば，パラメタに加える
			if (max_flag){
				if (/*穴埋め*/++n_line > n_line_max){
					fprintf(stderr, "Error: n_line(%d) is over n_line_max(%d)\n", n_line, n_line_max); 
					return -1;
				}
				/*穴埋め*/
				rhos.push_back(rho);
				thetas.push_back(theta);
			}
		}
	}

	return 0;
}

//*****************************************************************************
//	目的説明:	ハフ投票画像から閾値以上のパラメタを取得
//	入力引数:
//		file_vote:	投票画像
//		thresh:		投票の閾値
//		n_line_max:	直線の最大数
//		file_line:	直線パラメタを出力するファイル名
//*****************************************************************************
int thresh_hough_file(const char* file_vote, const char* file_line, int thresh, int n_line_max)
{
	int			ret = 0;		// 戻り値用変数
	cv::Mat		img_in;		// 入力画像(ハフ投票画像)
	int			n_line;		// 直線数
	vector<int>	rhos;		// rho配列
	vector<int>	thetas;		// theta配列

	// 画像の読み込み
	/*穴埋め*/img_in = cv::imread(file_vote, CV_LOAD_IMAGE_GRAYSCALE);
	if (img_in.data == NULL){
		fprintf(stderr, "Error: cv::imread(%s)\n", file_vote);
		ret = -1;
	}
	else{
		// 直線パラメタ(rho, theta)のメモリ確保

		// 閾値処理して直線パラメタを取得
		/*穴埋め*/thresh_hough(img_in, n_line, rhos, thetas, thresh, n_line_max);

		// パラメタの保存
		/*穴埋め*/
		ret = save_hough_line(file_line, n_line, rhos, thetas);
		if (ret) {
			fprintf(stderr, "Error: save_hough_line(%s)\n", file_line);
		}
	}

	return ret;
}

//*****************************************************************************
//	目的説明: rho-theta直線の保存
//	入力引数:
//		file_name:	ファイル名
//		n_line:		直線数
//		rhos:		rho配列
//		thetas:		theta配列
//*****************************************************************************
int save_hough_line(const char* file_name, int n_line, vector<int> &rhos, vector<int> &thetas)
{
	FILE*	fp;

	fopen_s(&fp, file_name, "w");
	if (!fp){
		fprintf(stderr, "Error: fopen_s(%s).\n", file_name);
		return -1;
	}

	fprintf(fp, "#Line: %d\n", n_line);
	fprintf(fp, "rho, theta\n");
	for (int i = 0; i < n_line; i++){
		fprintf(fp, "%d, %d\n", rhos[i], thetas[i]);
	}
	
	fclose(fp);
	return 0;
}


//*****************************************************************************
//	目的説明: rho-theta直線の読み込み
//	入力引数:
//		file_name:	ファイル名
//		rhos:		rho配列
//		thetas:		theta配列
//*****************************************************************************
int load_hough_line(const char* file_name, vector<int> &rhos, vector<int> &thetas)
{
	FILE*	fp;
	int		ret = 0;
	int		n_line;

	fopen_s(&fp, file_name, "r");
	if (!fp){
		fprintf(stderr, "Error: fopen_s(%s).\n", file_name);
		return -1;
	}

	fscanf_s(fp, "#Line: %d\n", &n_line);
	fscanf_s(fp, "rho, theta\n");

	rhos.resize(n_line);
	thetas.resize(n_line);
	
	for (int i = 0; i < n_line; i++){
		fscanf_s(fp, "%d, %d\n", &(rhos[i]), &(thetas[i]));
	}
		
	fclose(fp);
	return ret;
}



//*****************************************************************************
//	目的説明:	rho-theta直線の描画
//	入力引数:
//		img:		描画する画像
//		rho:		ハフ空間のrho
//		theta:		ハフ空間のtheta
//		clr:		直線の色
//		thickness:	直線の太さ
//*****************************************************************************
void draw_hough_line(cv::Mat img, int rho, int theta, cv::Scalar clr, int thickness)
{
	cv::Point	pt1, pt2;		// 線分の始点終点
	double		theta_radian;	// ラジアン単位のtheta
	double		sin_theta;		// 正弦
	double		cos_theta;		// 余弦

	// 正接・余接の取得
	/*穴埋め*/
	theta_radian = theta* M_PI / 180;
	sin_theta = sin(theta_radian);
	cos_theta = cos(theta_radian);


	//-----------------------------
	// 描画線分の始点・終点の取得
	//-----------------------------
	// 傾きが1より小さい場合
	/*穴埋め*/
	if (sin_theta / cos_theta < 1){
		pt1 = cv::Point(0, rho/sin_theta);
		pt2 = cv::Point(img.size().width - 1, (rho - (img.size().width - 1)*cos_theta) / sin_theta);
	}

	// 傾きが1より大きい場合
	/*穴埋め*/
	if (sin_theta / cos_theta >= 1){
		pt1 = cv::Point(rho / cos_theta, 0);
		pt2 = cv::Point((rho - (img.size().height - 1)*sin_theta) / cos_theta, img.size().height - 1);
	}

	// 線の描画
	/*穴埋め*/
	cv::line(img, pt1, pt2, clr, thickness);
	return;
}

//*****************************************************************************
//	目的説明:	rho-theta直線の描画(ファイル入出力版)
//	入力引数:
//		file_in:	入力画像のファイル名
//		file_line:	直線のパラメタファイル名
//		file_out:	出力画像のファイル名
//		clr:		直線の色
//		thickness:	直線の太さ
//*****************************************************************************
int draw_hough_lines_file(const char* file_in, const char* file_line, const char* file_out, cv::Scalar clr, int thickness)
{
	int			ret = 0;	// 戻り値用変数
	cv::Mat		img_in;		// 入力画像
	int			n_line;		// 直線数
	vector<int>	rhos;		// rho配列
	vector<int>	thetas;		// theta配列

	/*穴埋め*/
	ret = load_hough_line(file_line,rhos,thetas);
	n_line = rhos.size();
	img_in = cv::imread(file_in, CV_LOAD_IMAGE_COLOR);
	for (int i = 0; i < n_line; i++){
		draw_hough_line(img_in, rhos[i],thetas[i],clr,thickness);

	}
	cv::imwrite(file_out, img_in);

	return ret;
}