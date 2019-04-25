#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int m,n;
void linear_transform(Mat imgG,Mat newImg,double k)
{
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			if(k*imgG.at<uchar>(Point(i,j))<0) newImg.at<uchar>(Point(i,j))=0;
			else if(k*imgG.at<uchar>(Point(i,j))>255) newImg.at<uchar>(Point(i,j))=255;
			else newImg.at<uchar>(Point(i,j))=(int)(k*imgG.at<uchar>(Point(i,j)));
		}
}

int main()
{
	double k;
	cin>>k;
	Mat img,imgG,newImg;
	img=imread("D:\\Image\\2.jpg");
	cvtColor(img,imgG,CV_BGR2GRAY);
	m=imgG.cols;
	n=imgG.rows;
	newImg=Mat(n,m,CV_8U,Scalar::all(0));
	linear_transform(imgG,newImg,k);
	imshow("imgG",imgG);
	waitKey(50);
	imshow("Linear_transform",newImg);
	waitKey(0);
	return 0;
}