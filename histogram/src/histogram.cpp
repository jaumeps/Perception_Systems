
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include "stdio.h"

using namespace std;
using namespace cv;

//main
int main(int argc, char *argv[])
{
  //Load image
  CommandLineParser parser( argc, argv, "{@input | /home/jaume/Documentos/master/1Fonaments_de_la_robotica/Perception_Systems/Perception_Systems/histogram/imag/calella_palafrugell.jpg | input image}" );
  //CommandLineParser parser( argc, argv, "{@input | /home/jaume/Imágenes/calella_palafrugell.jpg | input image}" );
  Mat src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );
  if( src.empty() )
    {
        return -1;
    }

		//Separate the image in 3 places (B,G and R)
    vector<Mat> bgr_planes;
    /* split - Divides a multi-channel array into several single-channel arrays.
      void split(InputArray m, OutputArrayOfArrays mv)
      Parameters:
          m - input multi-channel array.
          mv - output array or vector of arrays.
    */
    split(src,bgr_planes);

    //Estabish the number of bins
    int histSize = 255;

    //Set the ranges (for B,G,R)
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    //Set histogram Parameters
    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    // Compute the histograms:
    /* calcHist - calculates a histogram of a set of arrays
      void calcHist(const Mat* images, int nimages, const int*channels, INputArray mask, OutputArray hist, int dims, const int*hitSize, const jloat**ranges, bool uniform=true, bool accumulate=false)
      Parameters:
        images - Source arrays.
        nimages - number of source iamges.
        channels - list of the dims channel used to compute the histogram.
        mask – Optional mask. If the matrix is not empty, it must be an 8-bit array of the same size as images[i] . The non-zero mask elements mark the array elements counted in the histogram.
        hist – Output histogram, which is a dense or sparse dims -dimensional array.
        dims – Histogram dimensionality that must be positive and not greater than CV_MAX_DIMS (equal to 32 in the current OpenCV version).
        histSize – Array of histogram sizes in each dimension.
        ranges – Array of the dims arrays of the histogram bin boundaries in each dimension. When the histogram is uniform ( uniform =true), then for each dimension i it is enough to specify the lower (inclusive) boundary L_0 of the 0-th histogram bin and the upper (exclusive) boundary U_{\texttt{histSize}[i]-1} for the last histogram bin histSize[i]-1 . That is, in case of a uniform histogram each of ranges[i] is an array of 2 elements. When the histogram is not uniform ( uniform=false ), then each of ranges[i] contains histSize[i]+1 elements: L_0, U_0=L_1, U_1=L_2, ..., U_{\texttt{histSize[i]}-2}=L_{\texttt{histSize[i]}-1}, U_{\texttt{histSize[i]}-1} . The array elements, that are not between L_0 and U_{\texttt{histSize[i]}-1} , are not counted in the histogram.
        uniform – Flag indicating whether the histogram is uniform or not (see above).
        accumulate – Accumulation flag. If it is set, the histogram is not cleared in the beginning when it is allocated. This feature enables you to compute a single histogram from several sets of arrays, or to update the histogram in time.
    */
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize );
    /*int cvRound(double value)
    Rounds floating-point number to the nearest integer.
    Parameters
      value	floatParameters:	ing-point number. If the value is outside of INT_MIN ... INT_MAX range, the result is not defined.
    */

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    // Normalize the result to [ 0, histImage.rows ]
    /* normalize - Normalizes the norm or value range of an array.
      void normalize(InputArray src, OutputArray dst, double alpha=1, double beta=0, int norm_type=NORM_L2, int dtype=-1, InputArray mask=noArray() )
        Parameters:
          src – input array.
          dst – output array of the same size as src .
          alpha – norm value to normalize to or the lower range boundary in case of the range normalization.
          beta – upper range boundary in case of the range normalization; it is not used for the norm normalization.
          normType – normalization type (see the details below).
          dtype – when negative, the output array has the same type as src; otherwise, it has the same number of channels as src and the depth =CV_MAT_DEPTH(dtype).
          mask – optional operation mask.
    */
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    // Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),Scalar( 0, 0, 255), 2, 8, 0);
    }

    imshow("Source image", src );
    imshow("calcHist Demo", histImage );
    waitKey();

    return 0;
}
