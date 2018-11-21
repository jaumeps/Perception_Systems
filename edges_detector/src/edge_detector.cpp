//21/11/2018 - JPS - Canny,Scharr,copyTo,createTrackbar,cvtColor

//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace cv;

//constants
int edgeThresh = 1; //edgeThresh is lowerlimit.
int ratio = 3; //ratio between lowerlimit and upperlimit
int size_Kernel = 3;
/*Information to CANNY with C++

Filter out any noise. The Gaussian filter is used for this purpose.

Hysteresis: The final step. Canny does use two thresholds (upper and lower):
    If a pixel gradient is higher than the upper threshold, the pixel is accepted as an edge
    If a pixel gradient value is below the lower threshold, then it is rejected.
    If the pixel gradient is between the two thresholds, then it will be accepted only if it is connected to a pixel that is above the upper threshold.
    Canny recommended a upper:lower ratio between 2:1 and 3:1.
    KERNEL_SIZE: By default it is 3.
    Canny(INPUT_IMAGE, OUTPUT_IMAGE, LOWER_THRESHOLD, HIGH_THRESHOLD(LOWER_THRESHOLD*RATIO), KERNEL_SIZE);
*/
int edgeThreshScharr=1;

Mat image, gray_image, blurImage, edge1, edge2, cedge;

const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny wit custom gradient (Scharr)";

//define a tracback callback
static void onTrackbar (int, void*)
{
  blur(gray_image, blurImage, Size(3,3));

  //Run the edge detector on grayscale
  Canny(blurImage, edge1, edgeThresh, edgeThresh*3,3);
  cedge = Scalar::all (0);

  image.copyTo(cedge, edge1);
  imshow(window_name1, cedge);

  Mat dx, dy;
  Scharr(blurImage,dx,CV_16S,1,0);
  Scharr(blurImage,dy,CV_16S,0,1);
  Canny(dx,dy,edge2,edgeThreshScharr, edgeThreshScharr*ratio, size_Kernel);
  cedge=Scalar::all(0);

  image.copyTo(cedge,edge2);
  imshow(window_name2, cedge);

}

int main(int argc, char *argv[])
{
  VideoCapture camera; 	//OpenCV video capture object
	int cam_id; //camera id . Associated to device number in /dev/videoX

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

  //Process loop. Capture and point feature extraction. User can quit pressing a key
  while(1)
	{
	     //Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            cout << "No image" << endl;
            waitKey();
        }

	//NEW

  cedge.create(image.size(), image.type());
  cvtColor(image, gray_image, COLOR_BGR2GRAY);

  // Create a window
  namedWindow(window_name1, 1);
  namedWindow(window_name2, 1);

  // create a toolbar
  /*
  int cv::createTrackbar([const String &]trackbarname,[const String &]winname,[int *]value,[int]count,[TrackbarCallback]onChange = 0,[void *]userdata = 0)
    trackbarname :	Name of the created trackbar.
    winname :	Name of the window that will be used as a parent of the created trackbar.
    value :	Optional pointer to an integer variable whose value reflects the position of the slider. Upon creation, the slider position is defined by this variable.
    count	: Maximal position of the slider. The minimal position is always 0.
    onChange :	Pointer to the function to be called every time the slider changes position. This function should be prototyped as void Foo(int,void*); , where the first parameter is the trackbar position and the second parameter is the user data (see the next parameter). If the callback is the NULL pointer, no callbacks are called, but only value is updated.
    userdata :	User data that is passed as is to the callback. It can be used to handle trackbar events without using global variables.
  */
  createTrackbar("Canny threshold default", window_name1, &edgeThresh, 100, onTrackbar);
  createTrackbar("Canny threshold Scharr", window_name2, &edgeThreshScharr, 400, onTrackbar);

  // Show the image
  onTrackbar(0,0);

	//Waits 30 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }
}
