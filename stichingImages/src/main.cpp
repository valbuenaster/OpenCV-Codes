/*
 * main.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: Luis
 */

#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

int processArguments(int argC,char** argV,
		             bool & divImg,
					 string & Str,
					 Stitcher::Mode & mode,
					 vector<Mat> &vecImages)
{
	if(argC == 1)
	{
		cout << "Wrong input parameters" << endl;
		return EXIT_FAILURE;
	}
	for(int ii = 1; ii < argC; ++ii)
	{
		if((string(argV[ii]) == "--help")||(string(argV[ii]) == "/?"))
		{
			cout << "The arguments are the pictures you want stitched and the options after" << endl;
			return EXIT_FAILURE;
		}else if(string(argV[ii]) == "--d3")
		{
			divImg = true;
		}else if(string(argV[ii]) == "--output")
		{
			Str = argV[ii+1];
			ii++;
		}else if(string(argV[ii]) == "--mode")
		{
			if(string(argV[ii + 1]) == "panorama")
			{
				mode = Stitcher::PANORAMA;
			}else if (string(argV[ii + 1]) == "scans")
			{
				mode = Stitcher::SCANS;
			}else
			{
				cout << "Bad -- mode flag value" << endl;
				return EXIT_FAILURE;
			}
			ii++;
		}else{
			cout << argV[ii] << endl;
			Mat img = imread(samples::findFile(argV[ii]));
			if(img.empty())
			{
				cout << "Could not read your file:" << argV[ii] << endl;
				return EXIT_FAILURE;
			}

			if(divImg)
			{
				Rect rect(0, 0, img.cols/2, img.rows);
				vecImages.push_back(img(rect).clone());
				rect.x = img.cols/3;
				vecImages.push_back(img(rect).clone());
				rect.x = img.cols/2;
				vecImages.push_back(img(rect).clone());
			}else{
				vecImages.push_back(img);
			}
		}
	}
	return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
	bool divide_images = false;
	Mat pano;
	vector<Mat> Images;
	Stitcher::Mode mode = Stitcher::PANORAMA;
	string result_name = "result.jpg";

	int rValue = processArguments(argc,argv, divide_images, result_name, mode, Images);

	if(rValue) return EXIT_FAILURE;

	Ptr<Stitcher> stitcher = Stitcher::create(mode);

	int counter = 1;
	for(auto el: Images)
	{
		namedWindow("Stitching" + to_string(counter),WINDOW_NORMAL);
		imshow("Stitching" + to_string(counter), el);
		counter++;
		waitKey(0);
	}

	Stitcher::Status status = stitcher->stitch(Images, pano);

	if(status != Stitcher::OK)
	{
		cout << "Could not stitch images. Sucks, doesn't it? error code = "
		     << static_cast<int>(status) << endl;
		return EXIT_FAILURE;
	}

	imwrite(result_name,pano);
	cout << "Stitching done successfully, Ciao..." << endl;

	return EXIT_SUCCESS;
}


