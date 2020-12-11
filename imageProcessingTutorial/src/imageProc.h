/*
 * imageProc.h
 *
 *  Created on: Dec 8, 2020
 *      Author: luis
 */

#ifndef SRC_IMAGEPROC_H_
#define SRC_IMAGEPROC_H_

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define DELAY_BLUR 100
#define MAX_KERNEL_LENGTH 31

using namespace cv;

void createEllipse(Mat img, Point pos, int SmajorAxis, int SminorAxis, double angle);
void createFilledCircle(Mat img, Point center, int radius);
void createPolygon(Mat img, int w);
void createLine(Mat img, Point Start, Point End);

void createAtom(Mat img,const std::string & Str, int w);
void createRook(Mat img,const std::string & Str, int w);

void displayImage(Mat img, const std::string & Str, Point Pos, int delay);

void filtering(Mat src, Mat img, int Kind);

void demoDilation(Mat input, Mat output);
void Dilation(int , void* object);

void demoErosion(Mat input, Mat output);
void Erosion(int , void* object);

void demoMorphologyOperation(Mat inputFilter,Mat dest_morphOp);
void MorphologyOperation(int , void* object);

struct IoO
{
	Mat input;
	Mat output;
	std::string Str;
	int Element;
	int Size;
	int Operation;
};

#endif /* SRC_IMAGEPROC_H_ */
