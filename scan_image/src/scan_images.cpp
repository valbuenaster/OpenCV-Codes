/*
 * scan_images.cpp
 *
 *  Created on: Nov 25, 2020
 *      Author: luis
 */
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#define S_SIZE 256

using namespace std;
using namespace cv;

constexpr uchar factor(int & IntDiv, int & val)
{
	return (uchar) (IntDiv * (val/IntDiv));
}

Mat ScanningImageAndAssigning(Mat& Img,const uchar * const Table)
{
	CV_Assert(Img.depth()== CV_8U);
	Mat retImg = Img.clone();

	int channels = Img.channels();
	int n_rows = Img.rows;
	int n_columns = Img.cols * channels;

	cout << "channels = "<< channels <<", n_rows = "<< n_rows <<", n_columns = " << n_columns <<endl;

	if(Img.isContinuous())
	{
		n_columns *= n_rows;
		n_rows = 1;
	}
	cout << "new n_rows = "<< n_rows <<", n_columns = " << n_columns <<endl;

	int ii,jj;
	uchar *p;
	for(ii = 0; ii < n_rows; ii++)
	{
		p = retImg.ptr<uchar>(ii);
		for(jj=0; jj < n_columns; jj++)
		{
			p[jj] = Table[p[jj]];
		}
	}
	cout << "i = "<< ii <<", j = "<<jj<<endl;

	return retImg;
}

int main(int argc, char ** argv)
{
	string Picture = argv[1];
	stringstream s;
	int integer_divider = 0;
	uchar Table[S_SIZE];

	Mat image = imread(Picture,IMREAD_COLOR);
	s << argv[2];
	s >> integer_divider;

	cout << "Scanning Image" << endl;
	cout << "File =  " << Picture << endl;
	cout << "argc =  " << argc << endl;
	cout << "integer_divider =  " << integer_divider<< endl;

	if( (argc != 3)||(!image.data) || (integer_divider == 0))
	{
		cout << "No valid data..." << endl;
		return -1;
	}

	for(int ii=0;ii<S_SIZE;ii++)
	{
		Table[ii] = factor(integer_divider, ii);
	}

	namedWindow("Start Image",WINDOW_AUTOSIZE);
	imshow("Start Image",image);

	waitKey(0);

	cout <<"Antes de ir a function"<<endl;
	Mat clonedImage = ScanningImageAndAssigning(image,Table);
	cout <<"Despues de ir a function"<<endl;

	namedWindow("Other Image",WINDOW_AUTOSIZE);
	imshow("Other Image",clonedImage);

	waitKey(0);

	return 0;
}




