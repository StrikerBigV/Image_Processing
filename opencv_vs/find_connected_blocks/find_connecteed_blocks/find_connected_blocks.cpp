#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

const int maxn=10010;//设定的最大长或宽
int m,n;//输入矩阵的长宽，小于maxn

//每个点的结构定义
struct Node
{
    int x,y;
};

int matrix[maxn][maxn];//输入矩阵
int mark[maxn][maxn]={0};//标记矩阵
bool inQ[maxn][maxn]={false};//判断矩阵，判断是否入过队列

//增量数组
int X[8]={-1,0,1,1,1,0,-1,-1};
int Y[8]={1,1,1,0,-1,-1,-1,0};

//寻找下一个点
Node Next(Node now,int order)
{//输入当前点以及下一个点的序号
    Node next;
    next.x=now.x+X[order];
    next.y=now.y+Y[order];
    return next;
}

//判断是否访问
bool judge(Node s)
{
    int x=s.x,y=s.y;
    if(x>=m || y>=n || x<0 || y<0) return false;
    if(matrix[x][y]==255 || inQ[x][y]==true) return false;
    return true;
}

//广度优先搜索，处理标记矩阵和判断矩阵
void BFS(Node s,int blocks)
{
    queue<Node> Q;
    Q.push(s);
    inQ[s.x][s.y]=true;
    mark[s.x][s.y]=blocks;
    while(!Q.empty())
    {
        Node top=Q.front();
        Q.pop();
        for(int i=0;i<8;i++)
        {
            Node p=Next(top,i);
            if(judge(p))
            {
                s=p;
                Q.push(s);
                inQ[s.x][s.y]=true;
                mark[s.x][s.y]=blocks;
            }
        }
    }
}

int main()
{
    Mat img=imread("D:\\Image\\2.jpg");
	Mat imgGray,imgBi;
	cvtColor(img,imgGray,CV_BGR2GRAY);
	threshold(imgGray,imgBi,110,255,CV_THRESH_BINARY);
	m=imgBi.cols;
	n=imgBi.rows;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			matrix[i][j]=imgBi.at<uchar>(Point(i,j));
    int blocks=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(matrix[i][j]==0 && inQ[i][j]==false)
            {
                blocks++;
                Node s;
                s.x=i;
                s.y=j;
                BFS(s,blocks);
            }
        }
    }
    printf("The number of connected_blocks is %d\n",blocks);
	printf("The marked matrix is\n");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d ",mark[i][j]);
		}
		printf("\n");
	}
    printf("The seats of blocks are\n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(inQ[i][j]) printf("(%d,%d) ",i+1,j+1);
        }
    }
	imshow("imgB",imgBi);
	waitKey(0);
    return 0;
}
