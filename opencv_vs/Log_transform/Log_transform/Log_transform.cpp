#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

void change_into_range(Mat img)
{
	int m=img.rows,n=img.cols;
	int Min=img.at<uchar>(0,0),Max=Min;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(img.at<uchar>(i,j)<Min) Min=img.at<uchar>(i,j);
            if(img.at<uchar>(i,j)>Max) Max=img.at<uchar>(i,j);
        }
    }
	Max-=Min;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
			img.at<uchar>(i,j)-=Min;
			img.at<uchar>(i,j)*=(255/Max);
		}
    }
}
void Log_transform(Mat img,double c)
{
	int m=img.rows,n=img.cols;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			img.at<uchar>(i,j)=(uchar)(c*log((double)(1+img.at<uchar>(i,j))));
}

int main()
{
	double c;
	cin>>c;
	Mat img,imgG,newImg;
	img=imread("D:\\Image\\5.tif");
	cvtColor(img,imgG,CV_BGR2GRAY);
	newImg=imgG.clone();
	Log_transform(newImg,c);
	change_into_range(newImg);
	imshow("Log_transform",newImg);
	//imshow("imgG",imgG);
	waitKey(0);
	return 0;
}