#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

vector<Mat>cut(8);
void Bitmap_cut(Mat imgG){
	int m=imgG.rows,n=imgG.cols;
	Mat temp=imgG.clone();
	for(int i=0;i<8;i++)
	{
		cut[i]=Mat(m,n,CV_8U,Scalar(0));
		for(int j=0;j<m;j++)
		{
			for(int k=0;k<n;k++)
			{
				cut[i].at<uchar>(j,k)=(temp.at<uchar>(j,k)%2)*255;
				temp.at<uchar>(j,k)/=2;
			}
		}
	}
}

int main()
{
	Mat img=imread("D:\\Image\\4.tif"),imgG;
	cvtColor(img,imgG,CV_BGR2GRAY);
	Bitmap_cut(imgG);
	for(int i=0;i<8;i++)
	{
		imshow("Bitmap_cut",cut[i]);
		waitKey(1000);
	}
	return 0;
}