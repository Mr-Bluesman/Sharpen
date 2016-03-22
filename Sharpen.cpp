/*
** Sharpen.cpp
** sharpens an image
** Usage: ./Sharpen image_path
*/

/***** Preprocessor Directives *****/

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include "processingLibs.hpp"

using namespace std;
using namespace cv;

/***** Globals *****/
struct variableBuffer buffer;
Mat sharpenIm;

void* dummy;

/***** Program Functions *****/
void function_errors(Err flag)
{
	switch (flag) {
		case 1: 
			cout << "Incorrect input args\n"<<"Usage: ./Sharpen image_path"
			<< endl; exit(1);
		case 2:
			cout << "Cannot open image at indicated directory" << endl;
			exit(2);
		default:
			cout << "Unknown Error" << endl;
			exit(99);
	}
}

/* checks to ensure correct input arguments have been utilized */
void args_check(int args, char *argsBuffer[], Mat& getIm)
{
	Err argsFlag;
	switch(args) {
		case 2:
			//obtain image
			getIm = imread(argsBuffer[1], CV_LOAD_IMAGE_COLOR);
			if (getIm.empty()) {
				argsFlag = 2;
				function_errors(argsFlag);
			}
			break;
		default:
			argsFlag = 1;
			function_errors(argsFlag);
	}
}

// Perform in-place unsharp masking operation
void unsharp_mask(Mat& im) 
{
    Mat tmp;
    //performs 'blurring' on a copy of the image
    GaussianBlur(im, tmp, cv::Size(buffer.size,buffer.size), (double)buffer.sigmaX/100);
    //computes weighted sum of blurred image and original image
    cv::addWeighted(im, (double)buffer.alpha/100, tmp, (double)buffer.beta/100, (double)buffer.gamma/100, im);
}

void callback_sigmax(int barVal, void*)
{
	buffer.sigmaX = barVal;
	unsharp_mask(sharpenIm);
}

int main(int argc, char *argv[])
{
	args_check(argc, argv, sharpenIm);

	//display input image
	namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	imshow("Input Image", sharpenIm);

	/** establish gui window and trackbars **/
	namedWindow("Processed Image", CV_WINDOW_NORMAL);
	//GaussianBlur variable trackbars
	createTrackbar("Gaussian kernel size", "Processed Image", &buffer.size, 100);
	createTrackbar("Sigma X", "Processed Image", &buffer.sigmaX, 1000, callback_sigmax);
	//weighted sum variable trackbars
	createTrackbar("alpha", "Processed Image", &buffer.alpha, 1000);
	createTrackbar("beta", "Processed Image", &buffer.beta, 1000);
	createTrackbar("gamma", "Processed Image", &buffer.gamma, 1000);

	unsharp_mask(sharpenIm);

	imshow("Processed Image", sharpenIm);
	// resizeWindow("Processed Image", 1280, 800); //1280*800 approx. fullscreen (mac)

	waitKey(0);
	return 0;	
}