#include "stdafx.h"

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

 int main( int argc, char** argv )
 {
    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    namedWindow("Control",CV_WINDOW_AUTOSIZE); //create a window called "Control"
	// Can use trackbars to pick calibrate color of interest.
	int minHue = 0;
	int maxHue = 179;

	int minSatur = 0; 
	int maxSatur = 255;

	int minValue = 0;
	int maxValue = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &minHue, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &maxHue, 179);

	cvCreateTrackbar("LowS", "Control", &minSatur, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &maxSatur, 255);

	cvCreateTrackbar("LowV", "Control", &minValue, 255);//Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &maxValue, 255);

    while (true)
    {
        Mat imgOriginal;
		Mat imgHSV;
		Mat imgThresholded;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

		 
		// Convert the captured frame from BGR to HSV
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 
	
		

		inRange(imgHSV, Scalar(minHue, minSatur, minValue), Scalar(maxHue, maxSatur, maxValue), imgThresholded); //Threshold the image
      
		//morphological opening (removes noise from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 

		//morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;
}