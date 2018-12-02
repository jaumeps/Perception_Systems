
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace cv;

//constants
const int GAUSSIAN_BLUR_SIZE = 7;
const double GAUSSIAN_BLUR_SIGMA = 2;
const double CANNY_EDGE_TH = 150;
const double HOUGH_ACCUM_RESOLUTION = 2;
const double MIN_CIRCLE_DIST = 40;
const double HOUGH_ACCUM_TH = 70;
const int MIN_RADIUS = 20;
const int MAX_RADIUS = 30;

int main(int argc, char *argv[])
{
    VideoCapture camera;  //OpenCV video capture object
    Mat image;            //OpenCV image object
	  int cam_id;           //camera id . Associated to device number in /dev/videoX
    Mat gray_image;
    vector<Vec3f> circles;
    Point center;
    int radius;

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

    //**************** Find circles in the image ****************************

        //clear previous circles
        circles.clear();

        // If input image is RGB, convert it to gray
        cvtColor(image, gray_image, CV_BGR2GRAY);
        /*
        void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0 )

        PARAMETERS:
          src – input image: 8-bit unsigned, 16-bit unsigned ( CV_16UC... ), or single-precision floating-point.
          dst – output image of the same size and depth as src.
          code – color space conversion code (see the description below).
          dstCn – number of channels in the destination image; if the parameter is 0, the number of the channels is derived automatically from src and code .

        The conventional ranges for R, G, and B channel values are:
              0 to 255 for CV_8U images
              0 to 65535 for CV_16U images
              0 to 1 for CV_32F images
        */

        //Reduce the noise so we avoid false circle detection
        GaussianBlur( gray_image, gray_image, Size(GAUSSIAN_BLUR_SIZE, GAUSSIAN_BLUR_SIZE), GAUSSIAN_BLUR_SIGMA );
        /*
        void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )

        PARAMETERS:
          src - input image; the image can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
          dst - output image of the same size and type as src.
          ksize - Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. Or, they can be zeroÃ¢Â€Â™s and then they are computed from sigma*.
          sigmaX - Gaussian kernel standard deviation in X direction.
          sigmaY - Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height , respectively; to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.
          borderType - pixel extrapolation method.

        */

        //Apply the Hough Transform to find the circles
        HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, HOUGH_ACCUM_RESOLUTION, MIN_CIRCLE_DIST, CANNY_EDGE_TH, HOUGH_ACCUM_TH, MIN_RADIUS, MAX_RADIUS );
        /*
        void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0 )

        PARAMETERS:
          image – 8-bit, single-channel, grayscale input image.
          circles – Output vector of found circles. Each vector is encoded as a 3-element floating-point vector (x, y, radius) .
          circle_storage – In C function this is a memory storage that will contain the output sequence of found circles.
          method – Detection method to use. Currently, the only implemented method is CV_HOUGH_GRADIENT , which is basically 21HT , described in [Yuen90].
          dp – Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
          minDist – Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
          param1 – First method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller).
          param2 – Second method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
          minRadius – Minimum circle radius.
          maxRadius – Maximum circle radius.
        */


        //draw circles on the image
        for(unsigned int ii = 0; ii < circles.size(); ii++ )
        {
            if ( circles[ii][0] != -1 )
            {
                    center = Point(cvRound(circles[ii][0]), cvRound(circles[ii][1]));
                    radius = cvRound(circles[ii][2]);
                    circle(image, center, 5, Scalar(0,255,0), -1, 8, 0 );     // circle center in green
                    circle(image, center, radius, Scalar(0,0,255), 3, 8, 0 ); // circle perimeter in red
            }
        }

    //********************************************************************

        //show image
        imshow("Output Window", image);

		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if( (unsigned char)(waitKey(30) & 0xff) == 'q' ) break;
    }
}
