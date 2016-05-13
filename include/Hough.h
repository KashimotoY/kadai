// Hough.h

#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

using namespace std;

#ifndef GMAX
#define GMAX 255
#endif

#ifndef M_PI
#define M_PI 3.141592 
#endif

#ifndef DEG2RAD
#define DEG2RAD(x) ((x) / 180.0 * M_PI)
#endif

#ifndef ROUND_INT
#define ROUND_INT(x) ((int)((x) + 0.5))
#endif

void edge2hough(cv::Mat img_edge, cv::Mat img_vote);
int edge2hough_file(const char* file_edge, const char* file_vote);

int thresh_hough(cv::Mat img_vote, int &n_line, vector<int> &rhos, vector<int> &thetas, int thresh, int n_line_max);
int thresh_hough_file(const char* file_vote, const char* file_line, int thresh, int n_line_max);
int save_hough_line(const char* file_name, int n_line, vector<int> &rhos, vector<int> &thetas);
int load_hough_line(const char* file_name, vector<int> &rhos, vector<int> &thetas);
void draw_hough_line(cv::Mat img, int rho, int theta, cv::Scalar clr, int thickness);
int draw_hough_lines_file(const char* file_in, const char* file_line, const char* file_out, cv::Scalar clr, int thickness);
