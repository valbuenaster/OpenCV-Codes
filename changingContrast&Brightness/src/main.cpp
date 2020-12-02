/*
 * main.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: Luis Ariel Valbuena Reyes
 */

#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using std::cout;
using std::cin;
using std::endl;

using namespace cv;

int main()
{
	double contrast = 1.0;
	double brightness = 0.0;
	Mat input, output;

	input = imread("Landscape.png",IMREAD_COLOR);

	if(input.empty())
	{
		cout << "Image was not read correctly" << endl;
		return -1;
	}

	output = Mat::zeros(input.size(), input.type());

	cout << "Contrast and brightness" << endl;
	cout << "Enter desired contrast [1.0 to 3.0]" << endl;
	cin >> contrast;
	cout << "Now enter brightness [0.0 to 100.0]" << endl;
	cin >> brightness;

	for(int jj = 0; jj < input.rows; jj++)
	{
		for(int ii = 0; ii < input.cols; ii++)
		{
			for(int cc = 0; cc < input.channels(); cc++)
			{
				Point temp = Point(ii,jj);
				output.at<Vec3b>(temp)[cc] = saturate_cast<uchar>( contrast*( input.at<Vec3b>(temp)[cc] ) + brightness );
			}
		}
	}

	imshow("Original Image", input);
	imshow("Modified Image", output);

	waitKey(0);


	return 0;
}


