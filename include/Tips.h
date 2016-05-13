// Tips.h

#pragma once

// 定数
#define N_STR 200
#define GMAX	255
#define GMIN	0

// 画像関連
#define CV_ID(pimg, y, x) ((pimg)->widthStep * (y) + (pimg)->depth / 8 * (pimg)->nChannels * (x))
#define CV_ID1C(pimg, y, x) ((pimg)->widthStep * (y) + (pimg)->depth / 8 * (x))
#define CV_ID1C8U(pimg, y, x) ((pimg)->widthStep * (y) + (x))
#define CV_2D(pimg, y, x) (&(pimg)->imageData[CV_ID(pimg, y, x)])
#define CV_2D1C(pimg, y, x) ((pimg)->imageData[CV_ID1C(pimg, y, x)])
#define CV_2D1C8U(pimg, y, x) ((pimg)->imageData[CV_ID1C8U(pimg, y, x)])


// 数学関係
#define COTAN(x) ((cos(x) / sin(x)))
#define SQR(x) ((x) * (x))
#define SQRT(x) sqrt(fabs(x))
#define CUB(x) ((x) * (x) * (x))
#define SIGN_SQR(x) (((x) > 0) ? SQR(x) : -SQR(x))
#define SIGN_SQRT(x) (((x) > 0) ? sqrt(x) : -sqrt(-x))
#define SQR_ADD(x, y) (SQR(x) + SQR(y))
#define HYPOTENEUSE(x, y) sqrt((double)SQR_ADD(x, y))
#define RINT(x) ((int)((x) + 0.5))
#define AVR(x, y) (((x) + (y)) / 2.0)
#define RINT_AVR(x, y) RINT(AVR(x, y))
#define RADIANS(x) ((x) / 180.0 * M_PI)
#define DEGREES(x) ((x) / M_PI * 180.0)

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef M_PI
#define M_PI 3.141592
#endif

#define CLIP(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define CLIP_MIN(x, min) (((x) < (min)) ? (min) : (x))
#define CLIP_MAX(x, max) (((x) > (max)) ? (max) : (x))
#define UPDATE_MAX(max, new_x) {if ((new_x) > (max)) (max) = (new_x);}
#define UPDATE_MIN(min, new_x) {if ((new_x) < (min)) (min) = (new_x);}
#define SIGN(x) (((x) > 0) ? 1 : -1)
#define SIGN2(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define NORMAL_RAND() ((double)rand() / (double)(RAND_MAX + 1))
#define SPEC_RAND(x) ((double)(x) * (double)rand() / (double)(RAND_MAX + 1))

#define NORM_RGB_SELF(c) sqrt(SQR((c).R) + SQR((c).G) + SQR((c).B))
#define NORM_RGB(c1, c2) (SQR((double)(c1).R-(double)(c2).R) + SQR((double)(c1).G - (double)(c2).G) + SQR((double)(c1).B - (double)(c2).B))
#define NORM_RGB_SQRT(c1, c2) sqrt((double)NORM_SQR(c1, c2))

#ifndef SWAP
#define SWAP(x, y, swap) {(swap) = (x); (x) = (y); (y) = (swap);}
#endif

// 固定サイズベクトル・行列演算マクロ
#define COPY_VEC3(v_in, v_out) {(v_out)[0] = (v_in)[0]; (v_out)[1] = (v_in)[1]; (v_out)[2] = (v_in)[2];}
#define INC_VEC3(v, v_add) {(v)[0] += (v_add)[0]; (v)[1] += (v_add)[1]; (v)[2] += (v_add)[2];}
#define SUB_VEC3(v1, v2, vout) {(vout)[0] = (v1)[0] - (v2)[0]; (vout)[1] = (v1)[1] - (v2)[1]; (vout)[2] = (v1)[2] - (v2)[2];}
#define INNER_PROD3(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1] + (v1)[2] * (v2)[2])
#define NORM_SQR3(v) (SQR((v)[0]) + SQR((v)[1]) + SQR((v)[2]))
#define NORM3(v) sqrt(NORM_SQR3(v))
#define PROD_MAT_AND_VEC3(M, v, vout) {(vout)[0] = INNER_PROD3(M[0], v); (vout)[1] = INNER_PROD3(M[1], v); (vout)[2] = INNER_PROD3(M[2], v);}
#define INC_MAT_BY_DIR_PROD3(M, v) {(M)[0][0] += (v)[0] * (v)[0]; (M)[0][1] += (v)[0] * (v)[1]; (M)[0][2] += (v)[0] * (v)[2]; (M)[1][0] += (v)[1] * (v)[0]; (M)[1][1] += (v)[1] * (v)[1]; (M)[1][2] += (v)[1] * (v)[2]; (M)[2][0] += (v)[2] * (v)[0]; (M)[2][1] += (v)[2] * (v)[1]; (M)[2][2] += (v)[2] * (v)[2];}
