
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

const char* window_name = "Output windows";

int main(int argc, char *argv[])
{

  VideoCapture camera;

  Mat image;
  int cam_id;

  //check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << endl;
			cout << "EXIT program." << endl;
			break;
	}

	//advertising to the user
	cout << "Opening video device " << cam_id << endl;

  //open the video stream and make sure it's opened
  if( !camera.open(cam_id) )
	{
        cout << "Error opening the camera. May be invalid device id. EXIT program." << endl;
        return -1;
  }

  String face_detect_name="../src/haarcascade_frontalface_alt.xml";

  CascadeClassifier face_detect;

  if( !face_detect.load( face_detect_name ) )
  {
    cout << "--(!)Error loading face detect\n" << endl;
    return -1;
  }

  //Process loop. Capture and point feature extraction. User can quit pressing a key

  while(1)
	{

    //Read image and check it. Blocking call up to a new image arrives from camera.
    if(!camera.read(image))
    {
      cout << "No frame" << endl;
            waitKey();
    }


    cvtColor(image, gray_image, CV_BGR2GRAY);
    equalizeHist(gray_image, gray_image);

    face_detect.detectMultiScale( gray_image, faces, scaleFactor, minNeighbors, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
      {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
      }

    // Display the resulting frame
    imshow(window_name, image);

    createTrackbar("minNeighbors", window_name, &minNeighbors, 10);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }

    return 0;
}
