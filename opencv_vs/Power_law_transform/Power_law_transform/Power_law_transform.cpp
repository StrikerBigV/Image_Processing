#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

void change_into_range(vector<vector<int> >&matrix)
{
	int m=matrix.size(),n=matrix[0].size();
	int Min=matrix[0][0],Max=Min;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(matrix[i][j]<Min) Min=matrix[i][j];
            if(matrix[i][j]>Max) Max=matrix[i][j];
        }
    }
    Max-=Min;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
			matrix[i][j]-=Min;
			matrix[i][j]=(int)(matrix[i][j]*(255*1.0/Max));
		}
    }
}

void Power_law_transform(Mat imgG,vector<vector<int> >&matrix,double c,double n)
{
	int mat_m=imgG.rows,mat_n=imgG.cols;
	for(int i=0;i<mat_m;i++)
		for(int j=0;j<mat_n;j++)
			matrix[i][j]=(int)(c*pow((double)(imgG.at<uchar>(i,j)),n));
}

void Matrix2Mat(vector<vector<int> >matrix,Mat &img)
{
	int m=matrix.size(),n=matrix[0].size();
	img=Mat(m,n,CV_8U,Scalar(0));
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			img.at<uchar>(i,j)=matrix[i][j];
}
int main()
{
	double c,n;
	cin>>c;
	cin>>n;
	Mat img,imgG,newImg;
	img=imread("D:\\Image\\6.tif");
	cvtColor(img,imgG,CV_BGR2GRAY);
	vector<vector<int> >matrix(imgG.rows,vector<int>(imgG.cols));
	Power_law_transform(imgG,matrix,c,n);
	change_into_range(matrix);
	Matrix2Mat(matrix,newImg);
	imshow("Power_law_transform",newImg);
	waitKey(0);
	return 0;
}