#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

void QuickSort(vector<int> &vec, int low, int high)
{
    if (low < high)
    {
        int l = low;
        int r = high;
        int key = vec[l];

        while (l < r)
        {
            while (l < r&&key <= vec[r])
                --r;
            vec[l] = vec[r];
            while (l < r&&key >= vec[l])
                ++l;
            vec[r] = vec[l];
        }
        vec[l] = key;

        QuickSort(vec, low, l-1);
        QuickSort(vec, r + 1, high);
    }
}

int mat_m,mat_n,tem_m,tem_n;
int get_midP(Mat imgG,int x,int y,vector<int> temp)
{
	int res,cnt=0;
	for(int i=x-tem_m/2;i<=x+tem_m/2;i++)
		for(int j=y+tem_n/2;j>=y-tem_n/2;j--)
			temp[cnt++]=imgG.at<uchar>(i,j);
	QuickSort(temp,0,temp.size()-1);
	res=(temp[0]+temp[tem_m*tem_n-1])/2;
	temp.clear();
	return res;
}
void MidPoint_filter(Mat imgG,Mat newImg,vector<int>temp)
{
	for(int i=tem_m/2;i<mat_m-tem_m/2;i++)
		for(int j=tem_n;j<mat_m-tem_n/2;j++)
			newImg.at<uchar>(i,j)=get_midP(imgG,i,j,temp);
}

int main()
{
	cin>>tem_m;
	cin>>tem_n;
	vector<int>temp(tem_m*tem_n);
	Mat img,imgG,newImg;
	img=imread("D:\\Image\\4.tif");
	cvtColor(img,imgG,CV_BGR2GRAY);
	mat_m=imgG.rows;
	mat_n=imgG.cols;
	newImg=imgG.clone();
	MidPoint_filter(imgG,newImg,temp);
	imshow("mid_filter",newImg);
	waitKey(0);
	return 0;
}