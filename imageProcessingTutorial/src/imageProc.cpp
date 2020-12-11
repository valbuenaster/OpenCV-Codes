/*
 * imageProc.cpp
 *
 *  Created on: Dec 8, 2020
 *      Author: luis
 */
#include <iostream>

#include "imageProc.h"

using namespace cv;

void createEllipse(Mat img, Point pos, int SmajorAxis, int SminorAxis, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,pos, Size(SmajorAxis,SminorAxis),
			angle, 0, 360,
			Scalar(255,0,0),thickness,lineType);
}

void createFilledCircle(Mat img, Point center, int radius)
{
	circle(img,center,radius, Scalar(0, 0, 255),FILLED,LINE_8);
}

void createLine(Mat img, Point Start, Point End)
{
	int thickness = 2;
	int lineType = 8;

	line(img,Start,End,Scalar(0,0,0),thickness,lineType);
}

void createPolygon(Mat img,int w)
{
	  int lineType = LINE_8;
	  Point rook_points[1][20];
	  rook_points[0][0]  = Point(    w/4,   7*(w/8) );
	  rook_points[0][1]  = Point(  3*(w/4),   7*(w/8) );
	  rook_points[0][2]  = Point(  3*(w/4),  13*(w/16) );
	  rook_points[0][3]  = Point( 11*(w/16), 13*(w/16) );
	  rook_points[0][4]  = Point( 19*(w/32),  3*(w/8) );
	  rook_points[0][5]  = Point(  3*(w/4),   3*(w/8) );
	  rook_points[0][6]  = Point(  3*(w/4),     w/8 );
	  rook_points[0][7]  = Point( 26*(w/40),    w/8 );
	  rook_points[0][8]  = Point( 26*(w/40),    w/4 );
	  rook_points[0][9]  = Point( 22*(w/40),    w/4 );
	  rook_points[0][10] = Point( 22*(w/40),    w/8 );
	  rook_points[0][11] = Point( 18*(w/40),    w/8 );
	  rook_points[0][12] = Point( 18*(w/40),    w/4 );
	  rook_points[0][13] = Point( 14*(w/40),    w/4 );
	  rook_points[0][14] = Point( 14*(w/40),    w/8 );
	  rook_points[0][15] = Point(    w/4,     w/8 );
	  rook_points[0][16] = Point(    w/4,   3*(w/8) );
	  rook_points[0][17] = Point( 13*(w/32),  3*(w/8) );
	  rook_points[0][18] = Point(  5*(w/16), 13*(w/16) );
	  rook_points[0][19] = Point(    w/4,  13*(w/16) );

	  const Point* ppt[1] = { rook_points[0] };
	  int npt[] = { 20 };
	  fillPoly( img, ppt, npt, 1, Scalar( 255, 255, 255 ), lineType );
}

void createAtom(Mat img,const std::string & Str, int w)
{
	createEllipse(img, Point(w/2, w/2), w/4, w/16,   0.0);
	createEllipse(img, Point(w/2, w/2), w/4, w/16,  90.0);
	createEllipse(img, Point(w/2, w/2), w/4, w/16,  45.0);
	createEllipse(img, Point(w/2, w/2), w/4, w/16, -45.0);

	createFilledCircle(img, Point( w/2, w/2), w/32);
}

void createRook(Mat img,const std::string & Str, int w)
{
	createPolygon(img,w);

	rectangle(img,Point(0, 7*(w/8)), Point(w,w),
			  Scalar(0,255,255),FILLED,LINE_8);

	createLine(img, Point(0,15*(w/16)), Point(w,15*(w/16)));
	createLine(img, Point(w/4,7*(w/8)), Point(w/4,w));
	createLine(img, Point(w/2,7*(w/8)), Point(w/2,w));
	createLine(img, Point(3*(w/4),7*(w/8)), Point(3*(w/4),w));
}

void displayImage(Mat img, const std::string & Str, Point Pos, int delay)
{
	int lineType = 7;
	int thickness = 1;

	putText(img,Str,Point(4,24),1,1.0,Scalar(0, 0, 255),thickness,lineType,false);
	namedWindow(Str, WINDOW_AUTOSIZE);
	imshow(Str, img);
	moveWindow(Str,Pos.x,Pos.y);

	waitKey(delay);
}

void filtering(Mat src, Mat img, int Kind)
{
	std::string Str;
	switch(Kind)
	{
	case 1:
		Str = "blur";
		break;
	case 2:
		Str = "Gaussian blur";
		break;
	case 3:
		Str = "Median blur";
		break;
	case 4:
		Str = "bilateral filter";
		break;
	}

	for(int ii = 1; ii < MAX_KERNEL_LENGTH; ii+=2)
	{
		switch(Kind)
		{
		case 1://blur
			blur(src,img,Size(ii,ii), Point(-1,-1));
			break;
		case 2://Gaussian blur
			GaussianBlur(src,img,Size(ii,ii), 0, 0);
			break;
		case 3://Median blur
			medianBlur(src,img,ii);
			break;
		case 4://bilateral filter
			bilateralFilter(src,img,ii,ii*2,ii/2);
			break;
		}
		displayImage(img,Str, Point(40,40), DELAY_BLUR);
	}
	std::cout<<"Done filtering"<<std::endl;
}

void demoDilation(Mat input, Mat output)
{
	//int dilationElement = 0;
	//int dilationSize = 0;
	int const max_elem = 2;
	int const max_kernel_size = 21;
	std::string windowName = "Dilation Demo";
	IoO temp;
	temp.Str = windowName;
	temp.input = input;
	temp.output = output;
	temp.Element = 0;
	temp.Size = 0;

	namedWindow(windowName,WINDOW_AUTOSIZE);

	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", windowName,
			&temp.Element, max_elem,
			Dilation,&temp);

	createTrackbar("Kernel size:\n 2n +1", windowName,
			&temp.Size, max_kernel_size,
			Dilation,&temp);


	//Dilation(0,0);
	Dilation(0,&temp);

	std::cout <<"End of Dilation demo"<<std::endl;
	waitKey(0);
}

void Dilation(int , void * object)
{
	//IoO * recTemp = reinterpret_cast<IoO *> (object);
	IoO * recTemp = static_cast<struct IoO *> (object);
	int dilationElement = recTemp->Element;
	int dilationSize = recTemp->Size;

	int dilation_type = 0;
	if(dilationElement == 0 ){dilation_type = MORPH_RECT;}
	else if(dilationElement == 1 ){dilation_type = MORPH_CROSS;}
	else if(dilationElement == 2 ){dilation_type = MORPH_ELLIPSE;}

	Mat element = getStructuringElement(dilation_type,
			                            Size((2*dilationSize) + 1,(2*dilationSize) + 1),
			                            Point(dilationSize,dilationSize));
	dilate(recTemp->input,recTemp->output,element);
	imshow(recTemp->Str,recTemp->output);
	object = static_cast<void*> (&recTemp);
}

void demoErosion(Mat input, Mat output)
{
	//int dilationElement = 0;
	//int dilationSize = 0;
	int const max_elem = 2;
	int const max_kernel_size = 21;
	std::string windowName = "Erosion Demo";
	IoO temp;
	temp.Str = windowName;
	temp.input = input;
	temp.output = output;
	temp.Element = 0;
	temp.Size = 0;

	namedWindow(windowName,WINDOW_AUTOSIZE);

	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", windowName,
			&temp.Element, max_elem,
			Erosion,&temp);

	createTrackbar("Kernel size:\n 2n +1", windowName,
			&temp.Size, max_kernel_size,
			Erosion,&temp);


	//Dilation(0,0);
	Dilation(0,&temp);

	std::cout <<"End of Erosion demo"<<std::endl;
	waitKey(0);
}

void Erosion(int , void * object)
{
	//IoO * recTemp = reinterpret_cast<IoO *> (object);
	IoO * recTemp = static_cast<struct IoO *> (object);
	int dilationElement = recTemp->Element;
	int dilationSize = recTemp->Size;

	int dilation_type = 0;
	if(dilationElement == 0 ){dilation_type = MORPH_RECT;}
	else if(dilationElement == 1 ){dilation_type = MORPH_CROSS;}
	else if(dilationElement == 2 ){dilation_type = MORPH_ELLIPSE;}

	Mat element = getStructuringElement(dilation_type,
			                            Size((2*dilationSize) + 1,(2*dilationSize) + 1),
			                            Point(dilationSize,dilationSize));
	erode(recTemp->input,recTemp->output,element);
	imshow(recTemp->Str,recTemp->output);
	object = static_cast<void*> (&recTemp);
}

void demoMorphologyOperation(Mat input, Mat output)
{
	//int dilationElement = 0;
	//int dilationSize = 0;
	int const max_elem = 2;
	int const max_kernel_size = 21;
	std::string windowName = "Morphology Operations Demo";
	IoO temp;
	temp.Str = windowName;
	temp.input = input;
	temp.output = output;
	temp.Element = 0;
	temp.Size = 0;
	temp.Operation = 0;


	namedWindow(windowName,WINDOW_AUTOSIZE);

	createTrackbar("Operator:\n 0: Erode - 1: Dilate  \n 2: Opening - 3: Closing  \n 4: Gradient - 5: Top Hat \n 6: Black Hat", windowName,
			&temp.Operation, max_elem + max_elem + max_elem,
			MorphologyOperation,&temp);

	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", windowName,
			&temp.Element, max_elem,
			MorphologyOperation,&temp);

	createTrackbar("Kernel size:\n 2n +1", windowName,
			&temp.Size, max_kernel_size,
			MorphologyOperation,&temp);


	//Dilation(0,0);
	Dilation(0,&temp);

	std::cout <<"End of Morphology Operation demo"<<std::endl;
	waitKey(0);
}

void MorphologyOperation(int , void* object)
{
	//IoO * recTemp = reinterpret_cast<IoO *> (object);
	IoO * recTemp = static_cast<struct IoO *> (object);
	int dilationElement = recTemp->Element;
	int dilationSize = recTemp->Size;
	int operation = recTemp->Operation;

	int dilation_type = 0;
	if(dilationElement == 0 ){dilation_type = MORPH_RECT;}
	else if(dilationElement == 1 ){dilation_type = MORPH_CROSS;}
	else if(dilationElement == 2 ){dilation_type = MORPH_ELLIPSE;}

	Mat element = getStructuringElement(dilation_type,
			                            Size((2*dilationSize) + 1,(2*dilationSize) + 1),
			                            Point(dilationSize,dilationSize));
	morphologyEx(recTemp->input,recTemp->output,operation,element);
	imshow(recTemp->Str,recTemp->output);
	object = static_cast<void*> (&recTemp);
}
