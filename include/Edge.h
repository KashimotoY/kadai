// Edge.h

#pragma once


#ifndef M_PI
#define M_PI 3.141592 
#endif

#ifndef UCHAR_MAX
#define UCHAR_MAX 255
#endif

#ifndef CHAR_MAX
#define CHAR_MAX 127
#endif

#ifndef USHORT_MAX
#define USHORT_MAX 65535
#endif

#ifndef SHORT_MAX
#define SHORT_MAX 32767
#endif

int LoG(cv::Mat img_in, cv::Mat , double sigma, double bias = 0);

int LoG_file(const char* file_in, const char* file_out, double sigma, int depth);

int zero_cross(cv::Mat img_in, cv::Mat img_out);

int zero_cross_file(const char* file_in, const char* file_out);
