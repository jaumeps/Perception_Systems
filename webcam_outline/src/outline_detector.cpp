
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//constants
const int GAUSSIAN_BLUR_SIZE = 7;
const double GAUSSIAN_BLUR_SIGMA = 2;
const double CANNY_EDGE_TH = 150;
const double HOUGH_ACCUM_RESOLUTION = 2;
const double MIN_CIRCLE_DIST = 40;
const double HOUGH_ACCUM_TH = 70;
const int MIN_RADIUS = 10;
const int MAX_RADIUS = 100;

using namespace std;
using namespace cv;

//Variables
VideoCapture camera;
Mat image, gray_image, imgCanny;
int cam_id;

int threshold1=188;
int threshold2=349;

int main(int argc, char *argv[])
{

	//check user args
	switch(argc)
	{
		case 1:       //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2:       //an argument is provided. Get it and set cam_id
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
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	   {
	      //Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		    {
            cout << "No image" << endl;
            waitKey();
        }

        // If input image is RGB, convert it to gray
        cvtColor(image, gray_image, CV_BGR2GRAY);

	      Canny(gray_image, imgCanny, threshold1, threshold2);

        //show image
	      imshow("Outline image", imgCanny);
        createTrackbar("Threshold1", "Outline image", &threshold1, 400);
        createTrackbar("Threshold2", "Outline image", &threshold2, 400);


        //Waits 30 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q') break;
	}
}
