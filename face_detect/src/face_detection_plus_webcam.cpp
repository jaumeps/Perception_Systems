
//https://stackoverflow.com/questions/36451089/opencv-png-image-with-alpha-channel?rq=1

//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace cv;
using namespace std;

Mat image, gray_image, hist;
vector<Rect> faces;
Mat frame_gray;

int main(int argc, char *argv[])
{
    	VideoCapture camera; //OpenCV video capture object
    	Mat image; //OpenCV image object
	    int cam_id; //camera id . Associated to device number in /dev/videoX

      //Moustache and hat
      string Moustache("../img/moustache.png");
      string Hat("../img/hat.png");

      if( argc > 1)
      {
        Moustache= argv[1];
      }

      //Read moustache image
      Mat moustache_image;
      moustache_image = imread(Moustache.c_str(), IMREAD_COLOR); // Read the file
      if( moustache_image.empty() )                              // Check for invalid input
      {
          cout <<  "Could not open or find the moustache image" << endl ;
          return -1;
      }

      //Read hat image
      Mat hat_image;
      hat_image = imread(Hat.c_str(), IMREAD_COLOR); // Read the file
      if( hat_image.empty() )                        // Check for invalid input
      {
          cout <<  "Could not open or find the hat image" << endl ;
          return -1;
      }

	     // Programa per detectar cara
        CascadeClassifier face_cascade;
	      face_cascade.load("../cascade/haarcascade_frontalface_default.xml");
	      // Programa per detectar ulls
        CascadeClassifier eyes_cascade;
	      eyes_cascade.load("haarcascade_eye_tree_eyeglasses.xml");
	      // Programa per detectar el nas
        CascadeClassifier nose_cascade;
	      nose_cascade.load("haarcascade_mcs_nose.xml");

	      // Per saber si carrega be el arxiu xml o no
 		    if (!face_cascade.load("../cascade/haarcascade_frontalface_default.xml"))
        {
         		printf("--(!)Error loading the haarcascade_frontalface_default.xml\n"); return -1;
    		}

        if (!eyes_cascade.load("../cascade/haarcascade_eye_tree_eyeglasses.xml"))
        {
         		printf("--(!)Error loading the haarcascade_eye_tree_eyeglasses.xml\n"); return -1;
    		}

		    if (!nose_cascade.load("../cascade/haarcascade_mcs_nose.xml"))
        {
         		printf("--(!)Error loading the haarcascade_mcs_nose.xml\n"); return -1;
    		}

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

            // If input image is RGB, convert it to gray
            cvtColor(image, gray_image, CV_BGR2GRAY);

          	//Processem la imatge
          	equalizeHist(gray_image, gray_image);

          	vector<Rect> faces;
          	face_cascade.detectMultiScale(gray_image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(100,100));

              for (int i = 0; i < faces.size(); i++)
              {
                  // visualize the faces
                 	Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
                  ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

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

        //show image
        imshow("Output Window", image);

    		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if((unsigned char)(waitKey(1)) == 'q') break;
        }

        return 0;
}
