/*
 * main.cpp
 *
 *  Created on: Dec 8, 2020
 *      Author: Luis Ariel Valbuena Reyes
 */

#include <iostream>
#include <string>

#include "imageProc.h"

#define W 400

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

using std::cout;
using std::endl;
using std::cin;

int main()
{
	std::string Str1 = "Drawing 1: Atom";
	std::string Str2 = "Drawing 2: Rook";

	cout <<"Drawing basic geometric figures"<<endl;

	Mat image_Atom = Mat::zeros(W, W, CV_8UC3);
	Mat image_Rook = Mat::zeros(W, W, CV_8UC3);

	createAtom(image_Atom,Str1,W);
	createRook(image_Rook,Str2,W);

	//imshow(Str1, image_Atom);
	//moveWindow(Str1,0, 200);
	displayImage(image_Atom, Str1, Point(0,100),0);

	//imshow(Str2, image_Rook);
	//moveWindow(Str2,W, 200);
	displayImage(image_Rook, Str2, Point(W,200),0);



	cout << "Testing filters"<<endl;
	std::string StrName1 = "Test1.png";
	std::string  StrName2 = "Test2.png";
	Mat inputFilter = imread(StrName2, IMREAD_COLOR);
	Mat destination = inputFilter.clone();
	Mat dest_dilation = inputFilter.clone();
	Mat dest_erosion = inputFilter.clone();
	Mat dest_morphOp = inputFilter.clone();

	displayImage(inputFilter, StrName2, Point(2*W,200),0);

	filtering(inputFilter, destination, 3);

	cout << "Demostration Dilation and Erosion" << endl;

	demoDilation(inputFilter,dest_dilation);
	demoErosion(inputFilter,dest_erosion);
	demoMorphologyOperation(inputFilter,dest_morphOp);

	cout << "Llega aqui"<< endl;

	return 0;
}



