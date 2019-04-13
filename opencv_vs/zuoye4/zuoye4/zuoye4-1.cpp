#include <iostream>
#include <cstdio>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int mat_m,mat_n,tem_m,tem_n;

int convol(Mat imgG, int x,int y,vector<vector<int> > tem)
{
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
	mat_m=209;
	mat_n=220;
	Mat imgG=Mat(mat_m,mat_n,CV_8U,Scalar::all(0));
	int cnt=0;
	for(int i=5;i<215;i++){
		for(int j=5;j<175;j++)
			imgG.at<uchar>(j,i)=255;
		cnt++;
		if(cnt==7){
			i+=17;
			cnt=0;
		}
	}
	Mat newImg=Mat(mat_m,mat_n,CV_8U,Scalar::all(0));
	for(int i=0;i<mat_m;i++)
		for(int j=0;j<mat_n;j++)
			newImg.at<uchar>(i,j)=imgG.at<uchar>(i,j);
	cin>>tem_m;
	cin>>tem_n;
	getchar();
	vector<vector<int> >tem(tem_m,vector<int>(tem_n));
	for(int i=0;i<tem_m;i++){
		for(int j=0;j<tem_n;j++)
			cin>>tem[i][j];
		getchar();
	}
	average_filter(imgG,newImg,tem);
	//imshow("imgG",imgG);
	imshow("newImg",newImg);
	waitKey(0);
	return 0;
}