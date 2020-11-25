/*
 * DisplayImage.cpp
 *
 *  Created on: Nov 24, 2020
 *      Author: Luis Ariel Valbuena Reyes
 */
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
	Mat image;
	string argName = argv[1];
	image = imread( argName, 1 );

	if( argc != 2 || !image.data )
    {
		cout <<"argName = " << argName << endl;
		cout << "argc = "<< argc << ", No image data ... " << endl;
		return -1;
    }

	namedWindow( "Display Image", WINDOW_AUTOSIZE );
	imshow( "Display Image", image );

	waitKey(0);

	return 0;
}


