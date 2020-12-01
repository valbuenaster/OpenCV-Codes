/*
 * applying_kernels.cpp
 *
 *  Created on: Nov 26, 2020
 *      Author: Luis Ariel Valbuena Reyes
 */

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat kernel1 = (Mat_<char>(3,3) <<  0,-1, 0,
		                          -1, 5,-1,
								   0,-1, 0);

void sharpenFctn(Mat & Input, Mat & Output)
{
	CV_Assert(Input.depth() == CV_8U);

	const int Channels = Input.channels();
	Output.create(Input.size(),Input.type());

	for(int jj = 1; jj < Input.rows-1; ++jj)
	{
		const uchar * previous = Input.ptr<uchar>(jj-1);
		const uchar * current = Input.ptr<uchar>(jj);
		const uchar * next = Input.ptr<uchar>(jj+1);

		uchar * output = Output.ptr<uchar>(jj);

		for(int ii = Channels;ii<Channels*(Input.cols - 1);++ii)
		{
			*output++ = saturate_cast<uchar> (5*current[ii] - current[ii-Channels] - current[ii+Channels] - previous[ii] - next[ii]);
		}
	}

	Output.row(0).setTo(Scalar(0));
	Output.row(Output.rows-1).setTo(Scalar(0));
	Output.col(0).setTo(Scalar(0));
	Output.col(Output.cols-1).setTo(Scalar(0));
}

int main(int argc, char** argv)
{
	string Name = argv[1];
	Mat Original_Image = imread(Name,IMREAD_COLOR);
	Mat grayScale_Image= imread(Name,IMREAD_GRAYSCALE);
	Mat dest1;
	Mat dest2;
	Mat dest3;
	Mat dest4;

	if( (argc != 2)||(!Original_Image.data) )
	{
		cout << "No valid data..." << endl;
		return -1;
	}

	namedWindow("Color Image",WINDOW_AUTOSIZE);
	imshow("Color Image", Original_Image);
	waitKey(0);

	namedWindow("Gray Image",WINDOW_AUTOSIZE);
	imshow("Gray Image", grayScale_Image);
	waitKey(0);

	double t = (double)getTickCount();
	sharpenFctn(Original_Image, dest1);
	t = ((double)getTickCount() - t)/getTickFrequency();

	namedWindow("Filtered Color Image Manual",WINDOW_AUTOSIZE);
	imshow("Filtered Color Image Manual", dest1);
	cout<<"The handwritten code took t = "<< t <<" seconds."<<endl;
	waitKey(0);

	t = (double)getTickCount();
	filter2D(Original_Image, dest2,Original_Image.depth(),kernel1);
	t = ((double)getTickCount() - t)/getTickFrequency();

	namedWindow("Filtered Color Image OpenCV",WINDOW_AUTOSIZE);
	imshow("Filtered Color Image OpenCV", dest2);
	cout<<"The opencv code took t = "<< t <<" seconds."<<endl;
	waitKey(0);

	t = (double)getTickCount();
	sharpenFctn(grayScale_Image, dest3);
	t = ((double)getTickCount() - t)/getTickFrequency();

	namedWindow("Filtered Gray Image Manual",WINDOW_AUTOSIZE);
	imshow("Filtered Gray Image Manual", dest3);
	cout<<"The handwritten code took t = "<< t <<" seconds."<<endl;
	waitKey(0);

	t = (double)getTickCount();
	filter2D(grayScale_Image, dest4,grayScale_Image.depth(),kernel1);
	t = ((double)getTickCount() - t)/getTickFrequency();

	namedWindow("Filtered Gray Image OpenCV",WINDOW_AUTOSIZE);
	imshow("Filtered Gray Image OpenCV", dest4);
	cout<<"The opencv code took t = "<< t <<" seconds."<<endl;
	waitKey(0);


	return 0;
}


