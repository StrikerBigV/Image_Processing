#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;


int differential(Mat imgG, int x,int y,vector<vector<int> > tem)
{
	int tem_m=tem.size(),tem_n=tem[0].size();
    int res=0;
	int i,j,k,l;
	for(i=0,k=x-tem_m/2;i<tem_m;i++,k++)
		for(j=0,l=y+tem_n/2;j<tem_n;j++,l--)
			res+=imgG.at<uchar>(k,l)*tem[i][j];
	return res;
}

void secondary_differential_filter(Mat imgG,vector<vector<int> >&matrix, vector<vector<int> >tem)
{
	int mat_m=imgG.rows,mat_n=imgG.cols;
	int tem_m=tem.size(),tem_n=tem[0].size();
    for(int i=tem_m/2;i<mat_m-tem_m/2;i++)
    {
        for(int j=tem_n/2;j<mat_n-tem_n/2;j++)
        {
            matrix[i][j]=(int)imgG.at<uchar>(i,j)-differential(imgG,i,j,tem);
        }
    }
}
void Matrix2Mat(vector<vector<int> >matrix,Mat &img)
{
	int m=matrix.size(),n=matrix[0].size();
	img=Mat(m,n,CV_8U,Scalar(0));
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			img.at<uchar>(i,j)=matrix[i][j];
}
void Mat2Matrix(Mat img,vector<vector<int> >&matrix)
{
	int m=img.rows,n=img.cols;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			matrix[i][j]=img.at<uchar>(i,j);
}
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
			matrix[i][j]=(uchar)(matrix[i][j]*(255*1.0/Max));
		}
    }
}
int main()
{
	int tem_m,tem_n;
	cin>>tem_m;
	cin>>tem_n;
	getchar();
	vector<vector<int> >tem(tem_m,vector<int>(tem_n));
	for(int i=0;i<tem_m;i++)
	{	for(int j=0;j<tem_n;j++)
			cin>>tem[i][j];
		getchar();
	}
	Mat img,imgG,newImg;
	img=imread("D:\\Image\\2.jpg");
	cvtColor(img,imgG,CV_BGR2GRAY);
	vector<vector<int> >matrix(img.rows,vector<int>(img.cols));
	Mat2Matrix(imgG,matrix);
	secondary_differential_filter(imgG,matrix,tem);
	change_into_range(matrix);
	Matrix2Mat(matrix,newImg);
	imshow("secodary_differential_filter",newImg);
	//for(int i=0;i<img.rows;i++)
	//{	for(int j=0;j<img.cols;j++)
		//	cout<<matrix[i][j]<<" ";
	//}
	waitKey(0);
}