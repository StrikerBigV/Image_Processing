#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;


int convol(Mat imgG, int x,int y,vector<vector<int> > tem)
{
	int tem_m=tem.size(),tem_n=tem[0].size();
    int res=0,sum=0;
	int i,j,k,l;
	for(i=0,k=x-tem_m/2;i<tem_m;i++,k++)
		for(j=0,l=y+tem_n/2;j<tem_n;j++,l--)
		{
			res+=imgG.at<uchar>(k,l)*tem[i][j];
			sum+=tem[i][j];
		}
	return res/sum;
}

void average_filter(Mat imgG,Mat newImg, vector<vector<int> >tem)
{
	int mat_m=imgG.rows,mat_n=imgG.cols;
	int tem_m=tem.size(),tem_n=tem[0].size();
    for(int i=tem_m/2;i<mat_m-tem_m/2;i++)
    {
        for(int j=tem_n/2;j<mat_n-tem_n/2;j++)
        {
            newImg.at<uchar>(i,j)=convol(imgG,i,j,tem);
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
	img=imread("D:\\Image\\4.tif");
	cvtColor(img,imgG,CV_BGR2GRAY);
	newImg=imgG.clone();
	average_filter(imgG,newImg,tem);
	imshow("average_filter",newImg);
	waitKey(0);
}