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
	Erosion(0,&temp);

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
	MorphologyOperation(0,&temp);

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

void extractVerticalHorizontalLines(const std::string imagePath)
{
	Mat source = imread(imagePath, IMREAD_COLOR);
	Mat grayVersion;
	Mat bw;
	Mat Horizontal;
	Mat Vertical;
	Mat hE;
	Mat vE;
	Mat Edges;
	Mat Smooth;

	int Factor = 30;
	int horizontal_size;
	int vertical_size;

	imshow(imagePath, source);
	if(source.channels() == 3)
	{
		cvtColor(source, grayVersion, COLOR_BGR2GRAY);
	}else{
		grayVersion = source;
	}
	displayImage(grayVersion, imagePath, Point(80,250), 0);

	//Turns the image black & white
	adaptiveThreshold(~grayVersion,bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	displayImage(bw,"Binary",Point(80,250),0);

	Horizontal = bw.clone();
	Vertical = bw.clone();

	horizontal_size = Horizontal.cols/Factor;
	vertical_size = Vertical.rows/Factor;

	hE = getStructuringElement(MORPH_RECT,Size(horizontal_size,1));
	vE = getStructuringElement(MORPH_RECT,Size(1,vertical_size));

	erodeFirst_dilateLater(Horizontal, hE, Point(-1,-1));
	erodeFirst_dilateLater(Vertical, vE, Point(-1,-1));

	displayImage(Horizontal,"Horizontal",Point(80,250),0);
	displayImage(Vertical,"Vertical",Point(80,250),0);

	bitwise_not(Vertical,Vertical);
	adaptiveThreshold(Vertical,Edges,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY, 3,-2);
	displayImage(Edges,"Edges",Point(80,250),0);

	dilate(Edges,Edges,Mat::ones(2,2,CV_8UC1));
	displayImage(Edges,"Edges",Point(80,250),0);
	Vertical.copyTo(Smooth);
	blur(Smooth,Smooth,Size(2,2));
	Smooth.copyTo(Vertical,Edges);

	displayImage(Smooth,"Smooth",Point(0,0),0);
}

void erodeFirst_dilateLater(Mat & mat, Mat & Element, Point pos)
{
	erode(mat,mat,Element,pos);
	dilate(mat,mat,Element,pos);
}

void demoThreshold(Mat & input,const std::string imagePath, Mat & output)
{
	Mat gray;
	IoO Temp;
	int max_operation = 4;
	int max_value = 255;

	cvtColor(input,gray, COLOR_BGR2GRAY);

	Temp.Str = imagePath;
	Temp.input = gray;
	Temp.output = output;
	Temp.Element = 0;
	Temp.Size = 0;
	Temp.Operation = 0;

	namedWindow(imagePath, WINDOW_AUTOSIZE);

	createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted",imagePath,
			&Temp.Operation,max_operation,thresholdFunction, &Temp);

	createTrackbar("Value",imagePath,&Temp.Element,max_value,thresholdFunction, &Temp);

	thresholdFunction(0,&Temp);
	waitKey(0);
}

void thresholdFunction(int , void* object)
{
	IoO * recTemp = static_cast<struct IoO *> (object);
	int max_binary_value = 255;

	threshold(recTemp->input,recTemp->output,recTemp->Element,max_binary_value,recTemp->Operation);
	imshow(recTemp->Str,recTemp->output);
	object = static_cast<void*> (&recTemp);
}

void demoVideo_ThresholdinRange()
{
	char key = ' ';
	const int max_value_H = 360/2;
	const int max_value = 255;
	int low_H = 0;
	int low_S = 0;
	int low_V = 0;
	int high_H = max_value_H;
	int high_S = max_value;
	int high_V = max_value;
	const std::string window_capture_name = "Video Capture";
	const std::string window_detection_name = "Object Detection";

	Mat frame, frame_HSV, frameThreshold;
 	VideoCapture cap(0);

 	namedWindow(window_capture_name);
 	namedWindow(window_detection_name);

 	infoThreshold temp;
 	temp.windowName = window_detection_name;
	temp.low_H = low_H;
	temp.high_H = high_H;
	temp.low_S = low_S;
	temp.high_S = high_S;
	temp.low_V = low_V;
	temp.high_V = high_V;

 	createTrackbar("Low H", window_detection_name, &temp.low_H,
 			       max_value_H,on_low_H_thresh_trackbar,&temp);
 	createTrackbar("High H", window_detection_name, &temp.high_H,
 			       max_value_H,on_high_H_thresh_trackbar,&temp);

 	createTrackbar("Low S", window_detection_name, &temp.low_S,
 			       max_value,on_low_S_thresh_trackbar,&temp);
 	createTrackbar("High S", window_detection_name, &temp.high_S,
 			       max_value,on_high_S_thresh_trackbar,&temp);

 	createTrackbar("Low V", window_detection_name, &temp.low_V,
 			       max_value,on_low_V_thresh_trackbar,&temp);
 	createTrackbar("High V", window_detection_name, &temp.high_V,
 			       max_value,on_high_V_thresh_trackbar,&temp);


 	while(true)
 	{
 	 	on_low_H_thresh_trackbar(0,&temp);
 	 	on_high_H_thresh_trackbar(0,&temp);
 	 	on_low_V_thresh_trackbar(0,&temp);
 	 	on_high_V_thresh_trackbar(0,&temp);
 	 	on_low_S_thresh_trackbar(0,&temp);
 	 	on_high_S_thresh_trackbar(0,&temp);

 		cap >> frame;

 		if(frame.empty()) break;

 		cvtColor(frame,frame_HSV,COLOR_BGR2HSV);

 		inRange(frame_HSV,Scalar(temp.low_H, temp.low_S, temp.low_V), Scalar(temp.high_H, temp.high_S, temp.high_V), frameThreshold);

 		imshow(window_capture_name,frame);
 		imshow(window_detection_name,frameThreshold);

 		key = (char) waitKey(30);

 		if((key=='q')||(key=='Q')||(key==27)) break;
 	}
}

static void on_low_H_thresh_trackbar(int, void* object)
{
	infoThreshold * Temp = static_cast<infoThreshold *> (object);
	int low_H = fmin(Temp->high_H - 1, Temp->low_H);
	setTrackbarPos("Low H", Temp->windowName,low_H);

	Temp->low_H = low_H;

	object = static_cast<void*> (&Temp);
}

static void on_high_H_thresh_trackbar(int, void* object)
{
	infoThreshold * Temp = static_cast<infoThreshold *> (object);
	int high_H = fmax(Temp->high_H, Temp->low_H + 1);
	setTrackbarPos("High H", Temp->windowName,high_H);

	Temp->high_H = high_H;

	object = static_cast<void*> (&Temp);
}

static void on_low_S_thresh_trackbar(int, void* object)
{
	infoThreshold * Temp = static_cast<infoThreshold *> (object);
	int low_S = fmin(Temp->high_S - 1, Temp->low_S);
	setTrackbarPos("Low S", Temp->windowName,low_S);

	Temp->low_S = low_S;

	object = static_cast<void*> (&Temp);
}

static void on_high_S_thresh_trackbar(int, void* object)
{
	infoThreshold * Temp = static_cast<infoThreshold *> (object);
	int high_S = fmax(Temp->high_S, Temp->low_S + 1);
	setTrackbarPos("High S", Temp->windowName,high_S);

	Temp->high_S = high_S;

	object = static_cast<void*> (&Temp);
}

static void on_low_V_thresh_trackbar(int, void* object)
{
	infoThreshold * Temp = static_cast<infoThreshold *> (object);
	int low_V = fmin(Temp->high_V - 1, Temp->low_V);
	setTrackbarPos("Low V", Temp->windowName,low_V);

	Temp->low_V = low_V;

	object = static_cast<void*> (&Temp);
}

static void on_high_V_thresh_trackbar(int, void* object)
{
	infoThreshold * Temp = static_cast<infoThreshold *> (object);
	int high_V = fmax(Temp->high_V, Temp->low_V + 1);
	setTrackbarPos("High V", Temp->windowName,high_V);

	Temp->high_V = high_V;

	object = static_cast<void*> (&Temp);
}

void demoCannyEdgeDetector(const std::string & path)
{
	const int max_lowThreshold = 100;
	std::string window_name = "Canny Edge Detector";
	Mat src = imread(path,IMREAD_COLOR);
	Mat dst;
	Mat src_gray;
	IoO Temp;

	if(src.empty())
	{
		std::cout<<"No go. Could not open the image"<<std::endl;
	}else
	{
		dst.create(src.size(),src.type());
		cvtColor(src,src_gray,COLOR_BGR2GRAY);

		Temp.Str = window_name;
		Temp.input = src_gray;
		Temp.Element = max_lowThreshold / 2;

		namedWindow(window_name, WINDOW_AUTOSIZE);
		createTrackbar("Min Threshold:", window_name,&Temp.Element,max_lowThreshold,CannyThreshold,&Temp);

		CannyThreshold(0,&Temp);
		waitKey(0);
	}
}

void CannyThreshold(int , void* object)
{
	IoO * recTemp = static_cast<struct IoO *> (object);
	Mat detectedEdges;
	const int ratio = 3;
	const int kernel_size = 3;

	//blur(recTemp->input,detectedEdges,Size(3,3));
	medianBlur(recTemp->input,detectedEdges,3);
	Canny(detectedEdges,detectedEdges,recTemp->Element,ratio*(recTemp->Element),kernel_size);
	recTemp->output = Scalar::all(0);

	//Originally, it does it with the src matrix, I am going to do it with src_gray
	recTemp->input.copyTo(recTemp->output, detectedEdges);

	imshow(recTemp->Str, recTemp->output);
	object = static_cast<void*> (&recTemp);
}

void demoHoughStraighLinesDetector(const std::string & path)
{
	std::string window_name1 = "Standard Hough Transform Straigh Lines";
	std::string window_name2 = "Probabilistic Hough Transform Straigh Lines";
	Mat src = imread(path,IMREAD_GRAYSCALE);
	Mat dst;
	Mat cdst;
	Mat cdstP;
	std::vector<Vec2f> lines;
	std::vector<Vec4i> linesP;

	if(src.empty())
	{
		std::cout<<"No go. Could not open the image"<<std::endl;
	}else
	{
		Canny(src,dst,50,200,3);

		cvtColor(dst,cdst,COLOR_GRAY2BGR);
		cdstP = cdst.clone();

		HoughLines(dst,lines, 1, CV_PI/180, 150,0,0);

		for(auto elem: lines)
		{
			float rho = elem[0];
			float theta = elem[1];
			Point p1,p2;
			double a = cos(theta);
			double b = sin(theta);
			double x0 = a*rho;
			double y0 = b*rho;

			p1.x = cvRound(x0 + 1000*(-b));
			p1.y = cvRound(y0 + 1000*(a));
			p2.x = cvRound(x0 - 1000*(-b));
			p2.y = cvRound(y0 - 1000*(a));

			createLine(cdst, p1, p2);
		}

		HoughLinesP(dst,linesP, 1, CV_PI/180, 50, 50, 10);

		for(auto elem: linesP) createLine(cdstP, Point(elem[0],elem[1]), Point(elem[2],elem[3]));

		imshow(path, src);
		imshow(window_name1,cdst);
		imshow(window_name2,cdstP);

		waitKey(0);
	}
}
