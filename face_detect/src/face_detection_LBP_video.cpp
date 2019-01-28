
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat image, gray_image;
vector<Rect> faces;
Mat frame_gray;

//Variables
double scaleFactor =1.3;
int minNeighbors=5;

const char* window_name = "Output windows";

int main(int argc, char *argv[])
{

  // Create a VideoCapture object and open the input file
  VideoCapture cap("../vid/video_deteccio_cares.mpeg");

  // Check if camera opened successfully
  if(!cap.isOpened())
  {
    cout << "Error opening video stream or file!" << endl;
    return -1;
  }

  //Load LBP (Local Binary Pattern)
  String face_cascade_name ="../LBP/lbpcascade_frontalface.xml";

  CascadeClassifier face_detect;

  //To check LBP
  if( !face_detect.load( face_cascade_name ) )
  {
    cout << "--(!)Error loading face detect" << endl;
    return -1;
  }

  //Process loop. Capture and point feature extraction. User can quit pressing a key
  while(1)
	{
    // Capture frame-by-frame
    cap >> image;

    cvtColor(image, gray_image, CV_BGR2GRAY);
    equalizeHist(gray_image, gray_image);

    /*
    C++: void CascadeClassifier::detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size()
    Parameters:
        cascade – Haar classifier cascade (OpenCV 1.x API only). It can be loaded from XML or YAML file using Load(). When the cascade is not needed anymore, release it using cvReleaseHaarClassifierCascade(&cascade).
        image – Matrix of the type CV_8U containing an image where objects are detected.
        objects – Vector of rectangles where each rectangle contains the detected object.
        scaleFactor – Parameter specifying how much the image size is reduced at each image scale.
        minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
        flags – Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
        minSize – Minimum possible object size. Objects smaller than that are ignored.
        maxSize – Maximum possible object size. Objects larger than that are ignored.
    */

    face_detect.detectMultiScale( gray_image, faces, scaleFactor, minNeighbors, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
      {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        //circle( image, center, 50, Scalar( 255, 0, 0 ), 4, 8, 0 );

      }

    // Display the resulting frame
    imshow(window_name, image);

    createTrackbar("minNeighbors", window_name, &minNeighbors, 10);


		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(waitKey(30) & 0xff) == 'q' ) break;
    }

    return 0;
}
