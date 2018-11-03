
//OpenCV 
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"

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
const int MIN_RADIUS = 20;
const int MAX_RADIUS = 100;

int main(int argc, char *argv[]) 
{
    cv::VideoCapture camera; 	//OpenCV video capture object
    cv::Mat image; 		//OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Mat gray_image;
    cv::Mat imageHSV;
    cv::Mat imageThreshHigh;
    cv::Mat imageThreshLow;
    cv::Mat imageThresh;
    //cv::Mat structuringElement;

    std::vector<cv::Vec3f> circles;
    cv::Point center;
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
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl; 
			std::cout << "EXIT program." << std::endl; 
			break; 
	}
	
	//advertising to the user 
	std::cout << "Opening video device " << cam_id << std::endl;

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
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }
        
        //clear previous circles
        circles.clear();

	//NEW
	cv::cvtColor(image, imageHSV, CV_BGR2HSV);
	
	cv::inRange(imageHSV, cv::Scalar(0,155,155), cv::Scalar(18,255,255), imageThreshLow);
	cv::inRange(imageHSV, cv::Scalar(165,155,155), cv::Scalar(179,255,255), imageThreshHigh);

	cv::add(imageThreshLow, imageThreshHigh, imageThresh);

	cv::GaussianBlur(imageThresh, imageThresh, cv::Size(3,3), 0);

	cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));

	cv::dilate(imageThresh, imageThresh, structuringElement);
	cv::erode(imageThresh, imageThresh, structuringElement);

	cv::HoughCircles(imageThresh, circles, CV_HOUGH_GRADIENT, HOUGH_ACCUM_RESOLUTION, MIN_CIRCLE_DIST, CANNY_EDGE_TH, HOUGH_ACCUM_TH, MIN_RADIUS, MAX_RADIUS);

	for (int i = 0; i < circles.size(); i++) {
			
		 std::cout << "ball position x = " << circles[i][0] << ", y = " << circles[i][1] << ", radius = " << circles[i][2] << "\n";				cv::circle(image, cv::Point((int)circles[i][0], circles[i][1]), 3, cv::Scalar(0, 255, 0), CV_FILLED);
		 cv::circle(image, cv::Point((int)circles[i][0], (int)circles[i][1]), (int)circles[i][2], cv::Scalar(0, 0, 255),3);			
	} 
	
	/*
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("imageThresh", CV_WINDOW_AUTOSIZE);
	*/

        //show image
	cv::imshow("imageThresh", imageThresh);
        cv::imshow("Output Window", image);

	/*	
	cv::imshow("imageHSV", imageHSV);
	cv::imshow("gray_image", gray_image);
	cv::imshow("imagethreshlow", imageThreshLow);
	cv::imshow("imagethreshhigh", imageThreshHigh);
	*/


	//Waits 30 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }   
}
