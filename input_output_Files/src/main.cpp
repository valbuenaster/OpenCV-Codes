/*
 * main.cpp
 *
 *  Created on: Dec 27, 2020
 *      Author: luis
 */


#include <iostream>
#include <ostream>
#include <string>

#include <opencv2/core.hpp>

using namespace cv;
using std::cin;
using std::cout;
using std::endl;


class MyData
{
public:
	MyData() : A(0), X(0), id()
	{}
	explicit MyData(int) : A(97), X(CV_PI), id("mydata1234")
	{}
	void write(FileStorage & fs) const
	{
		fs << "{" << "A" << A << "X" << X << "id" << id <<"}";
	}
	void read(const FileNode& node)
	{
		A = static_cast<int> (node["A"]);
		X = static_cast<double> (node["X"]);
		id = static_cast<std::string> (node["id"]);
	}

public:
	int A;
	double X;
	std::string id;
};

//These functions is define for the serialization on FileStorage to work
static void write(FileStorage &fs, const std::string &, const MyData &x)
{
	x.write(fs);
}
static void read(const FileNode &node, MyData &x, const MyData default_value = MyData())
{
	if(node.empty())
	{
		x = default_value;
	}else{
		x.read(node);
	}
}
//These functions is define for the serialization on FileStorage to work

//This function will print to the  console the class previously defined
static std::ostream& operator<<(std::ostream& out, const MyData& m)
{
	out << "{\t id = " << m.id << ", ";
	out << "\t X = " << m.X << ", ";
	out << "\t A = " << m.A <<"}";
	return out;
}

int main(int argc, char** argv)
{
	Mat R;
	Mat T;
	int itNr;

	if(argc !=2)
	{
		return -1;
	}else
	{
		cout << "Writing" << endl;
		std::string filename = argv[1];
		R = Mat_<uchar>::eye(3,3);
		T = Mat_<double>::zeros(3,1);
		MyData m(1);

		FileStorage fs(filename,FileStorage::WRITE);

		fs << "iterationNr" << 100;

		fs << "strings" << "[";
		fs << "image1.jpg" << "Awesomeness" << "../data/baboon.jpg"; //Writing text sequences
		fs << "]";

		fs << "Mapping";
		fs << "{" << "One" << 1 << "Two" << 2 << "}"; //Writing mapping

		fs << "R" << R; //Writing matrices
		fs << "T" << T;

		fs << "MyData" << m; //Writing the class defined above

		fs.release();
		cout << "Done writing"<< endl << endl;

		cout << "Reading" << endl;
		FileStorage fs2;
		fs2.open(filename,FileStorage::READ);

		if(!fs2.isOpened())
		{
			cout << "Failed to open "<< filename <<". Sucks to be you..."<<endl;
			return -1;
		}

		itNr = static_cast<int> (fs2["iterationNr"]);
		cout << "itNr = " << itNr << endl;

		FileNode n = fs2["strings"];
		if(n.type() != FileNode::SEQ)
		{
			cout << "strings is not a sequence! FAIL" << endl;
			return -1;
		}
		for(auto el: n)
		{
			cout << static_cast<std::string> (el) <<endl;
		}

		n = fs2["Mapping"];                               // Read mappings from a sequence
        cout << "Two  " << static_cast<int>(n["Two"]) << "; ";
        cout << "One  " << static_cast<int>(n["One"]) << endl << endl;

        MyData mr;
        Mat Rr,Tr;

        fs2["R"] >> Rr;
        fs2["T"] >> Tr;
        fs2["MyData"] >> mr;

        cout << endl << "R = " << R << endl;
        cout << "T = " << T << endl << endl;
        cout << "MyData = " << endl << mr << endl << endl;

        //Show default behavior for non existing nodes
        cout << "Attempt to read NonExisting (should initialize the data structure with its default).";
        fs["NonExisting"] >> mr;
        cout << endl << "NonExisting = " << endl << mr << endl;

		return 0;
	}
}

