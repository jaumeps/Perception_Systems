
//opencv
#include "opencv2/opencv.hpp"

//std
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace cv;

//main
int main(int argc, char *argv[])
{
    VideoCapture camera;               //OpenCV video capture object
    Mat image;                         //OpenCV image object
	  int cam_id;                        //camera id . Associated to device number in /dev/videoX
	  Scalar_<unsigned char> px_value;   //pixel value (4-element vector)
	  int user_key;                      //user pressed key to quit

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
			cout << "EXIT program." << std::endl;
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

    //capture loop. Out of user press a key
    while(1)
	  {
		//Read image and check it. Blocking call up to a new image arrives from camera.
      if(!camera.read(image))
		  {
            cout << "No frame" << endl;
            waitKey();
      }

        //show image in a window
        imshow("Output Window", image);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(waitKey(30) & 0xff) == 'q' ) break;
    }
}
