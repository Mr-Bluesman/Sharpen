/*
** processingLibs.hpp
** includes the necessary typedefs, structs, and other data necessary for
** Sharpen and other image processing programs to work
*/

/* type used as error flag */
typedef int Err;

/* stores the variables that are used to change parameters to the functions */
struct variableBuffer
{
	//sharpen params
	int alpha = 150; 	//weighting of first image
	int beta = -50;	//weighting of second image
	int gamma = 0;	//scalar added to output of sum
	int size = 1;	//stores the Gaussian kernel size (width and height are equal)
	int sigmaX = 300;	//sigmaX value for GaussianBlur

};
