/*
 * main.cpp
 *
 *  Created on: Dec 1, 2020
 *      Author: luis
 */

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

using std::cout;
using std::cin;
using std::endl;

int main()
{
	double alpha = 0.5;
	double beta;
	double input;

	Mat Img1, Img2, Result;

	cout<<"Blending images together"<<endl;
	cout<<"Enter alpha for I_{mixed} = alpha*Img1 + (1 - alpha)*Img2"<<endl;
	cin >> input;

	Img1 = imread("Batman.png",IMREAD_COLOR);
	Img2 = imread("Catwoman.png",IMREAD_COLOR);

	if((input <= 1.0)&&(input >= 0.0)) alpha = input;

	beta = 1 - alpha;

	if(Img1.empty())
	{
		cout<<"Could not read file..."<<endl;
	}else{
		namedWindow("Image 1",WINDOW_AUTOSIZE);
		imshow("Image 1", Img1);
	}
	if(Img2.empty())
	{
		cout<<"Could not read file..."<<endl;
	}else{
		namedWindow("Image 2",WINDOW_AUTOSIZE);
		imshow("Image 2", Img2);
	}

	waitKey(0);

	addWeighted(Img1,alpha,Img2,beta,0.0,Result);

	imwrite("Merging.png",Result);
	namedWindow("Result",WINDOW_AUTOSIZE);
	imshow("Result", Result);

	waitKey(0);

	return 0;
}


