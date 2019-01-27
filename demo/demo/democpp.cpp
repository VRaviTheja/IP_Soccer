#include"stdafx.h"

#include<cv.h>
#include<highgui.h>

int main()
{
	IplImage* img=cvLoadImage("F:/Images/wallpapers/Amazing Space Photos/76.jpg");
	cvNamedWindow("firstwindow");
	cvShowImage("firstwindow",img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	return 0;
}