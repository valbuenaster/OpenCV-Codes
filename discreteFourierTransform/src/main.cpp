/*
 * main.cpp
 *
 *  Created on: Dec 2, 2020
 *      Author: Luis Ariel Valbuena Reyes
 */

#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	string NameFile = (argc >=2)? (argv[1]): "GitHubPic.jpg";

	Mat I = imread(NameFile, IMREAD_GRAYSCALE);

	if(I.empty())
	{
		cout << "Failed to read file... sucks to be you." << endl;
		return -1;
	}

	Mat padded;
	int m = getOptimalDFTSize(I.rows);
	int n = getOptimalDFTSize(I.cols);
	copyMakeBorder(I,padded,0,m - I.rows,0,n - I.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F)};
	Mat ComplexI;
	merge(planes,2,ComplexI);//Add to the expanded another plane with zeros

	dft(ComplexI,ComplexI);//Don't know what this does yet

	split(ComplexI,planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];

	magI += Scalar::all(1);
	log(magI, magI);//switch logarithmic scale

	magI = magI( Rect(0,0,magI.cols & -2, magI.rows & -2));//crop the spectru if it has an odd number of rows or colums

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols/2;
	int cy = magI.rows/2;

	Mat q0(magI,Rect(0,0,cx,cy));	//top-left, Region of Interest
	Mat q1(magI,Rect(cx,0,cx,cy));	//top-right
	Mat q2(magI,Rect(0,cy,cx,cy));	//bottom-left
	Mat q3(magI,Rect(cx,cy,cx,cy));	//bottom-right

	Mat tmp;
	q0.copyTo(tmp);	//Swap quadrants top-left with bottom-right
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);	//Swap quadrants top-right with bottom-left
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI,magI,0,1, NORM_MINMAX); //Transforming the matrix with float values into a
											//viewable image form (float between 0 and 1)

	imshow("Input Image", I);
	imshow("Spectrum magnitude", magI);
	waitKey(0);

	return 0;
}


