// Epipolar.h

#pragma once

#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;

#define dump(x) cerr << #x << ": " << (x) << endl;

typedef vector<cv::Point> point_list;


cv::Scalar id2clr(int id);

int MouseEventSample(const char* file_img_in1, const char* file_img_in2, cv::Scalar clr, int thickness, int radius);

int GetManualCorrespondence(const char *file_img_in1, const char *file_img_in2, const char *file_pt, int n_pt_max, int radius);

int SaveCorrespondence﻿(const char *file_pt, int n_pt, vector<cv::Point> &pt1, vector<cv::Point> &pt2);
int LoadCorrespondence﻿(const char *file_pt, int &n_pt, vector<cv::Point> &pt1, vector<cv::Point> &pt2);

int GetFMat(int n_pt, vector<cv::Point> &pt1, vector<cv::Point> &pt2, cv::Mat &F);
int GetFMat_file(const char *file_pt, const char *file_FMat);

int SaveFMat(const char *file_FMat, cv::Mat F);
int LoadFMat(const char *file_FMat, cv::Mat &F);

void draw_line_with_prm(cv::Mat img, double *p, cv::Scalar clr, int thickness);
void DrawPtAndEpipolarLine(cv::Mat img_pt, cv::Mat img_epipolar, int id_img_pt, cv::Point pt, cv::Mat F, cv::Scalar clr, int thickness, int pt_radius);

int OnlineDrawEpipolar(const char *file_img_in1, const char *file_img_in2, const char * file_Fmat, cv::Scalar clr, int thickness, int radius);
