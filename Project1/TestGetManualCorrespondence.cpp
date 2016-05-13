//TestGetManualCorrespondence.cpp

#include <stdio.h>
#include "Epipolar.h"


//*****************************************************************************
// ƒƒCƒ“ŠÖ”
//*****************************************************************************
int main(int argc, char** argv){

	int ret;
	char* file_img_in1;
	char* file_img_in2;
	char* file_point_out;

	if (argc < 4){
		fprintf(stderr, "usage: GetManualCorrespondence file_img_in1 file_img_in2 file_point_out.\n");
		return -1;
	}


	file_img_in1 = argv[1];
	file_img_in2 = argv[2];
	file_point_out = argv[3];



}