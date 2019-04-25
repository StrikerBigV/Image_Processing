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
	int m=imgG.cols,n=imgG.rows;
	Mat temp=imgG.clone();
	for(int i=0;i<8;i++)
	{
		cut[i]=Mat(imgG.rows,imgG.cols,CV_8U,Scalar(0));
		for(int j=0;j<m;j++)
		{
			for(int k=0;k<n;k++)
			{
				cut[i].at<uchar>(Point(j,k))=(temp.at<uchar>(Point(j,k))%2)*255;
				temp.at<uchar>(Point(j,k))/=2;
			}
		}
	}
}

//********************************显示多张图片的函数************************//

//**************************************************************************//
int main()
{
	Mat img=imread("D:\\Image\\10.jpg"),imgG;
	cvtColor(img,imgG,CV_BGR2GRAY);
	Bitmap_cut(imgG);
	imshow("imgG",imgG);
	waitKey(50);
	for(int i=7;i>=0;i--){
		imshow("cut",cut[i]);
		waitKey(1000);
	}
	waitKey(0);
	destroyAllWindows();
	return 0;
}