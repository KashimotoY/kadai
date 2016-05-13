// ID2Clr.cpp

#include <opencv2/opencv.hpp>

// ID‚©‚çF‚ğæ“¾
cv::Scalar id2clr(int id)
{
	cv::Scalar clr;
	int p = 3;
	double	s = (double)UCHAR_MAX / (p - 1);
	int max = p * p * p;
	int	S0, S1;
	int	d, r, k1, k2, k3;

	// round”‚ÌZo
	id = id % max;
	S0 = S1 = 0;
	for (r = 1; r <= p; r++){
		S1 = S0 + 3 * (p - r + 1) * (p - r) + 1;
		if (id < S1){
			break;
		}
		else{
			S0 = S1;
		}
	}

	// F‚ÌŒˆ’è
	d = id - S0 - 1;
	if (d == -1){
		for (int k = 0; k < 3; k++) clr.val[k] = (int)(s * (r - 1));
	}
	else{
		k1 = d % 3;
		k2 = (d / 3) % (p - r) + r;
		k3 = (d / (3 * (p - r))) % 3 + (r - 1);
		clr.val[k1] = (int)(s * k2);
		clr.val[(k1 + 1) % 3] = (int)(s * k3);
		clr.val[(k1 + 2) % 3] = (int)(s * (r - 1));
	}
	return clr;
}
