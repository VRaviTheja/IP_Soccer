#include "stdafx.h"
#include <C:\OpenCV\opencv\build\include\opencv2\highgui\highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main( int argc, const char**argv )
{
	VideoCapture vid(0);
	namedWindow("video");
	Mat frame;
	while(1)
	{
		vid.read(frame);
		imshow("video",frame);
		waitKey(33);
		
	}
	destroyWindow("video");
	return 0;
}