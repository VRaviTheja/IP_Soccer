#include "stdafx.h"
#include<cv.h>
#include<highgui.h>


using namespace cv;
using namespace std;

int main(int argc, const char**argv)
	
{
	VideoCapture vid(0);
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	int thresh=0;
	int c;
	 int iLowH = 0;
 int iHighH = 179;

int posX,posX1;
int posY;

int posX1;
int posY1;

  int iLowS = 0; 
 int iHighS = 255;

  int iLowV = 0;
 int iHighV = 255;

 int iLastX = -1; 
 int iLastY = -1;

  //Capture a temporary image from the camera
 Mat imgTmp;
 

  //Create a black image with the size as the camera output
 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;

  //Create trackbars in "Control" window
 cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &iHighV, 255);
	
	namedWindow("video");
	

	namedWindow("threshold");
	namedWindow("gra");
	namedWindow("hsv");
	namedWindow("binary2");
	 createTrackbar("bright", "threshold", &thresh, 255, NULL);
	Mat frame,gray,binary,imgThresholded,hsv;
	while(1)
	{
		vid.read(imgTmp); 
		vid.read(frame);
		
		cvtColor(frame,gray,CV_BGR2GRAY);
		
		threshold(gray,binary,thresh,255,CV_THRESH_BINARY);
		
		cvtColor(frame,hsv,CV_BGR2HSV);
        inRange(hsv,Scalar(iLowH, iLowS, iLowV),Scalar(iHighH, iHighS, iHighV),imgThresholded);
		
		//morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   //morphological closing (fill small holes in the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

  //Calculate the moments of the thresholded image
  Moments oMoments = moments(imgThresholded);

   double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;


   // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
  if (dArea > 10000)
  {
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea;        
        int posX1 = dM10 / dArea;
   int posY1 = dM01 / dArea; 
   
  }


  frame=frame+imgLines;
	  imshow("gra",gray);
  imshow("video",frame);
  imshow("threshold",binary);
  imshow("hsv",hsv);
		imshow("binary2",imgThresholded);

		HANDLE hSerial;

		hSerial=CreateFile(TEXT("COM8"),
			GENERIC_READ|GENERIC_WRITE,
			0,
			0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);

		DCB dcbSerial={0};

		dcbSerial.DCBlength=sizeof(dcbSerial);

		if(!GetCommState(hSerial,&dcbSerial))
		{
			//error getting state
		}

		dcbSerial.BaudRate=CBR_19200;
		dcbSerial.ByteSize=8;
		dcbSerial.StopBits=ONESTOPBIT;
		dcbSerial.Parity=NOPARITY;
		if(!SetCommState(hSerial,&dcbSerial))
		{
			//error getting serial port state
		}

		char forward='f';
		char reverse='r';
		char left='l';
		char right='r';
		char stop='s';
		DWORD bytesread=0;

		if(posX1>320)
		{
			if(!WriteFile(hSerial,&right,1,&bytesread,NULL))
			{
				//error
			}
		while(posX!=posX1)
		{
		if(!WriteFile(hSerial,&forward,1,&bytesread,NULL))
		{
			//error
		}
		}
		}
		else
		{
			if(!WriteFile(hSerial,&left,1,&bytesread,NULL))
			{
				//error
			}
		while(posX!=posX1)
		{
		if(!WriteFile(hSerial,&forward,1,&bytesread,NULL))
		{
			//error
		}
		}
		}








        CloseHandle(hSerial);
		c=waitKey(35);
		if(c==27)
		{
			break;
		}
		else
			continue;
		
	}
	destroyWindow("video");
	destroyWindow("gra");
	destroyWindow("threshold");
	return 0;
}
//void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=LINE_8, int shift=0 )