#include"stdafx.h"
#include "C:\OpenCV\opencv\build\include\opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, const char**argv )
{ 
	Mat img =imread("F:/Images/wallpapers/Amazing Space Photos/11.jpg", CV_LOAD_IMAGE_UNCHANGED);

	if(img.empty()) //check if imgage is loaded
	{
		cout << "Error img cant be loaded"  << endl;
		//system("pause");  //wait for a key press
		return -1;
	}

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow",img);

	waitKey(0);

	destroyWindow("MyWindow");

	return 0;
}