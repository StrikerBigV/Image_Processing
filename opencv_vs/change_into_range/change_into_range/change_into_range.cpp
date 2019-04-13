#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
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
int main()
{
	Mat img1,img2,img,img1G,img2G;
	img1=imread("D:\\Image\\1.tif");
	img2=imread("D:\\Image\\2.tif");
	cvtColor(img1,img1G,CV_BGR2GRAY);
	cvtColor(img2,img2G,CV_BGR2GRAY);
	int mat_m=img1G.rows;
	int mat_n=img1G.cols;
	vector<vector<int> >matrix1(mat_m,vector<int>(mat_n));
	vector<vector<int> >matrix2(mat_m,vector<int>(mat_n));
	vector<vector<int> >matrix(mat_m,vector<int>(mat_n));
	img=Mat(mat_m,mat_n,CV_8U,Scalar::all(0));
	for(int i=0;i<mat_m;i++)
		for(int j=0;j<mat_n;j++)
			matrix1[i][j]=img1G.at<uchar>(i,j);
	for(int i=0;i<mat_m;i++)
		for(int j=0;j<mat_n;j++)
			matrix2[i][j]=img2G.at<uchar>(i,j);
	for(int i=0;i<mat_m;i++)
		for(int j=0;j<mat_n;j++)
			matrix[i][j]=matrix1[i][j]-matrix2[i][j];
	change_into_range(matrix);
	for(int i=0;i<mat_m;i++)
		for(int j=0;j<mat_n;j++)
			img.at<uchar>(i,j)=matrix[i][j];
	imshow("img",img);
	waitKey(0);
	return 0;
}