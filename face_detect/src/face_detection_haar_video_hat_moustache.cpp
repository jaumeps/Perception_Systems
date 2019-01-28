/*Information
  https://docs.opencv.org/3.0-beta/modules/imgcodecs/doc/reading_and_writing_images.html
*/


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

Mat image, gray_image, hist;
vector<Rect> faces;
Mat frame_gray;

//Variables
double scaleFactor =1.3;
int minNeighbors=2;

const char* window_name = "Video with moustache and hat";

int main(int argc, char *argv[])
{

  // Create a VideoCapture object and open the input file
  VideoCapture cap("../vid/video_deteccio_cares.mpeg");

  string Moustache("../img/moustache.png");
  string Hat("../img/hat.png");

  //**********Moustache************************
  if( argc > 1)
  {
    Moustache= argv[1];
  }

  Mat moustache_image;
  moustache_image = imread(Moustache.c_str(), IMREAD_UNCHANGED); // Read the file

  if( moustache_image.empty() )                              // Check for invalid input
  {
      cout <<  "Could not open or find the moustache image" << std::endl ;
      return -1;
  }

  //***********hat******************************
  Mat hat_image;
  hat_image = imread(Hat.c_str(), IMREAD_COLOR); // Read the file
  imshow("nnn",hat_image);
  if( hat_image.empty() )                              // Check for invalid input
  {
      cout <<  "Could not open or find the hat image" << std::endl ;
      return -1;
  }

  //***********hat_miki**************************
  int outputCols=640;
  int outputRows=480;

  Mat hat_new;
  Mat hat_mki_image;
  string Hat1("../img/miki_hat.png");
  //Mat Hat1(outputRows, outputCols, CV_8UC4);
  Hat1=Scalar(255,255,255,0);
  imwrite("hat_new",Hat1,CV_IMWRITE_PNG_COMPRESSION);



  // Check if camera opened successfully
  if(!cap.isOpened())
  {
    cout << "Error opening video stream or file!" << endl;
    return -1;
  }

  //Load haarcascade
  String face_cascade_name ="../cascade/haarcascade_frontalface_alt.xml";
  CascadeClassifier face_detect;

  //To check haarcascade
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
        //Position
        int width = faces[i].width;
        int height = faces[i].height;

        //Hat position
        int hat_x = faces[i].x;
        int hat_y = (faces[i].y - faces[i].y/2);

        //Moustache position
        int moustache_x = faces[i].x;
        int moustache_y = (faces[i].y);

        //Draw hat
        resize(hat_image, hat_image, Size(width,height),CV_INTER_LINEAR);
        hat_image.copyTo(image(Rect(hat_x,hat_y,width,height)));

        //Draw moustache
        resize(moustache_image, moustache_image, Size(width,height),CV_INTER_LINEAR);
        moustache_image.copyTo(image(Rect(moustache_x,moustache_y,width,height)));

      }
    // Display the resulting frame
    imshow(window_name, image);

    createTrackbar("minNeighbors", window_name, &minNeighbors, 10);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    if( (unsigned char)(waitKey(30) & 0xff) == 'q' ) break;
    }

    return 0;
}
