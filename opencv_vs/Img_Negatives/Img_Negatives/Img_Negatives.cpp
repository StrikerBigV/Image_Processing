#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int m,n;
void Img_Negetives(Mat imgG,Mat newImg)
{
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			newImg.at<uchar>(i,j)=255-1-imgG.at<uchar>(i,j);
}

int main()
{
	Mat img,imgG,newImg;
	img=imread("D:\\Image\\3.tif");
	cvtColor(img,imgG,CV_BGR2GRAY);
	m=imgG.rows;
	n=imgG.cols;
	newImg=Mat(m,n,CV_8U,Scalar::all(0));
	Img_Negetives(imgG,newImg);
	imshow("Linear_transform",newImg);
	waitKey(0);
	return 0;
}