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
int get_mid(Mat imgG,int x,int y,vector<int> temp)
{
	int res,cnt=0;
	for(int i=x-tem_m/2;i<=x+tem_m/2;i++)
		for(int j=y+tem_n/2;j>=y-tem_n/2;j--)
			temp[cnt++]=imgG.at<uchar>(i,j);
	QuickSort(temp,0,temp.size()-1);
	res=temp[tem_m*tem_n/2];
	temp.clear();
	return res;
}
void mid_filter(Mat imgG,Mat newImg,vector<int>temp)
{
	for(int i=tem_m/2;i<mat_m-tem_m/2;i++)
		for(int j=tem_n;j<mat_m-tem_n/2;j++)
			newImg.at<uchar>(i,j)=get_mid(imgG,i,j,temp);
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
	Mat newImg=imgG;
	cin>>tem_m;
	cin>>tem_n;
	vector<int>temp(tem_m*tem_n);
	mid_filter(imgG,newImg,temp);
	imshow("newImg",newImg);
	waitKey(0);
	return 0;
}