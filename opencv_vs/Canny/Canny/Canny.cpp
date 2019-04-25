#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


const int maxn=1010;
//结点定义
struct Node
{
    int x,y;
};
//高斯滤波器
int Gauss[3][3]={{1,2,1},{2,4,2},{1,2,1}};

int convol(Mat imgG, int x,int y,int tem[][3])
{
    int res=0,sum=0;
	int i,j,k,l;
	for(i=0,k=x-1;i<3;i++,k++)
		for(j=0,l=y-1;j<3;j++,l++)
		{
			res+=imgG.at<uchar>(Point(k,l))*tem[i][j];
			sum+=tem[i][j];
		}
	return res/sum;
}

void Gauss_filter(Mat imgG,Mat newImg)
{
	int mat_m=imgG.cols,mat_n=imgG.rows;
    for(int i=1;i<mat_m-1;i++)
    {
        for(int j=1;j<mat_n-1;j++)
        {
            newImg.at<uchar>(Point(i,j))=convol(imgG,i,j,Gauss);
        }
    }
}

//sobel算子
int SobelX[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
int SobelY[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};


int differential(Mat imgG, int x,int y,int tem[][3])
{
    int res=0;
	int i,j,k,l;
	for(i=0,k=x-1;i<3;i++,k++)
		for(j=0,l=y-1;j<3;j++,l++)
			res+=imgG.at<uchar>(Point(k,l))*tem[i][j];
	return res;
}

void Sobel_filter(Mat imgG,vector<vector<double> >&matrix,vector<vector<int> >&matrixX,vector<vector<int> >&matrixY)
{
	int mat_m=imgG.cols,mat_n=imgG.rows;
    for(int i=1;i<mat_m-1;i++)
    {
        for(int j=1;j<mat_n-1;j++)
        {
            matrixX[i][j]=abs(differential(imgG,i,j,SobelX));// 改
			matrixY[i][j]=abs(differential(imgG,i,j,SobelY));
			matrix[i][j]=(int)sqrt(matrixX[i][j]*matrixX[i][j]+matrixY[i][j]*matrixY[i][j]+0.5);
        }
    }
}
void Matrix2Mat(vector<vector<int> >matrix,Mat &img)
{
	int m=matrix.size(),n=matrix[0].size();
	img=Mat(n,m,CV_8U,Scalar(0));
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			img.at<uchar>(Point(i,j))=matrix[i][j];
}
void Mat2Matrix(Mat img,vector<vector<int> >&matrix)
{
	int m=img.cols,n=img.rows;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			matrix[i][j]=img.at<uchar>(Point(i,j));
}

//广度优先搜索
bool inQ[maxn][maxn]={false};//判断矩阵，判断是否入过队列
bool isVis[1000][1000]={false};//标记数组
//增量数组
int X[8]={-1,0,1,1,1,0,-1,-1};
int Y[8]={1,1,1,0,-1,-1,-1,0};

//是否保留
bool PointReserved=false,LineReserved=false;
//寻找下一个点
Node Next(Node now,int order)
{//输入当前点以及下一个点的序号
    Node next;
    next.x=now.x+X[order];
    next.y=now.y+Y[order];
    return next;
}

//判断是否访问
bool judge(Node s,Mat &N,vector<vector<double> > &M,int nThrLow,int nThrHigh)
{
	int m=N.cols,n=N.rows;
    int x=s.x,y=s.y;
    if(x>=m-1 || y>=n-1 || x<1 || y<1) return false;
    if(N.at<uchar>(Point(x,y))!=225 || M[x][y]<nThrLow ||M[x][y]>=nThrHigh || inQ[x][y]==true) return false;
    return true;
}

//广度优先搜索
void BFS(Node s,Mat &N,vector<vector<double> >&M,int nThrLow,int nThrHigh)
{
    queue<Node> Q;
    Q.push(s);
    inQ[s.x][s.y]=true;
	N.at<uchar>(Point(s.x,s.y))=255;
    while(!Q.empty())
    {
        Node top=Q.front();
        Q.pop();
        for(int i=0;i<8;i++)
        {
            Node p=Next(top,i);
            if(judge(p,N,M,nThrLow,nThrHigh))
            {
                s=p;
                Q.push(s);
                inQ[s.x][s.y]=true;
				N.at<uchar>(Point(s.x,s.y))=255;
            }
        }
    }
}

int main(){
	Mat img=imread("D:\\Image\\11.png");
//第一步，灰度化
	Mat imgG;
	cvtColor(img,imgG,CV_BGR2GRAY);
	int mat_m=imgG.cols,mat_n=imgG.rows;

//第二步，高斯滤波器平滑图像
	Mat imgGauss=imgG.clone();
	Gauss_filter(imgG,imgGauss);

//第三步，Sobel算子计算梯度幅值和方向
	vector<vector<int> > P(mat_m,vector<int>(mat_n)),Q(mat_m,vector<int>(mat_n));
	vector<vector<double> > M(mat_m,vector<double>(mat_n)),Theta(mat_m,vector<double>(mat_n));//梯度幅值矩阵M，方向矩阵theta
	Sobel_filter(imgGauss,M,P,Q);
	for(int i=1;i<mat_m-1;i++)
		for(int j=1;j<mat_n-1;j++)
		{
			Theta[i][j]=atan2((double)Q[i][j],(double)P[i][j])*180/3.1415;
			if(Theta[i][j]<0) Theta[i][j]+=360;
		}
//第四步，对梯度幅值沿灰度梯度方向进行非极大值抑制
	Mat N=Mat(mat_n,mat_m,CV_8U,Scalar::all(0));
    int g1=0, g2=0, g3=0, g4=0;                            //用于进行插值，得到亚像素点坐标值   
    double dTmp1=0.0, dTmp2=0.0;                           //保存两个亚像素点插值得到的灰度数据 
    double dWeight=0.0;                                    //插值的权重  

    for(int i=1;i<mat_m-1;i++)
    {
        for(int j=1;j<mat_n-1;j++)
        {
            //如果当前点梯度为0，该点就不是边缘点
            if (M[i][j]==0)
            {
                N.at<uchar>(Point(i,j))=0;
            }else
            {
                ////////首先判断属于那种情况，然后根据情况插值///////  
                ////////////////////第一种情况///////////////////////  
                /////////       g1  g2                  /////////////  
                /////////           C                   /////////////  
                /////////           g3  g4              /////////////  
                /////////////////////////////////////////////////////  
                if((Theta[i][j]>=90&&Theta[i][j]<135)||(Theta[i][j]>=270&&Theta[i][j]<315))
                {
                   g1=M[i-1][j-1];
                   g2=M[i][j-1];
                   g3=M[i][j+1];
                   g4=M[i+1][j+1];
                   dWeight=fabs((double)P[i][j])/fabs((double)Q[i][j]); 
                   dTmp1=g1*dWeight+(1-dWeight)*g2;
                   dTmp2=g4*dWeight+(1-dWeight)*g3;
                   ////////////////////第二种情况///////////////////////  
                   /////////       g1                      /////////////  
                   /////////       g2  C   g3              /////////////  
                   /////////               g4              /////////////  
                   /////////////////////////////////////////////////////  
                }else if((Theta[i][j]>=135&&Theta[i][j]<180)||(Theta[i][j]>=315&&Theta[i][j]<360))
                {
                    g1=M[i-1][j-1];
                    g2=M[i-1][j];
                    g3=M[i+1][j];
                    g4=M[i+1][j+1];
                    dWeight=fabs((double)Q[i][j])/fabs((double)P[i][j]); 
                    dTmp1=g1*dWeight+(1-dWeight)*g2;
                    dTmp2=g4*dWeight+(1-dWeight)*g3;
                    ////////////////////第三种情况///////////////////////  
                    /////////           g1  g2              /////////////  
                    /////////           C                   /////////////  
                    /////////       g4  g3                  /////////////  
                    /////////////////////////////////////////////////////  
                }else if((Theta[i][j]>=45&&Theta[i][j]<90)||(Theta[i][j]>=225&&Theta[i][j]<270))
                {
                    g1=M[i+1][j-1];
                    g2=M[i][j-1];
                    g3=M[i][j+1];
                    g4=M[i-1][j+1];
                    dWeight=fabs((double)P[i][j])/fabs((double)Q[i][j]); 
					dTmp1=g1*dWeight+(1-dWeight)*g2;
					dTmp2=g4*dWeight+(1-dWeight)*g3;
                    ////////////////////第四种情况///////////////////////  
                    /////////               g1              /////////////  
                    /////////       g4  C   g2              /////////////  
                    /////////       g3                      /////////////  
                    /////////////////////////////////////////////////////  
                }else if((Theta[i][j]>=0&&Theta[i][j]<45)||(Theta[i][j]>=180&&Theta[i][j]<225))
                {
                    g1=M[i+1][j-1];
                    g2=M[i+1][j];
                    g3=M[i-1][j];
                    g4=M[i-1][j+1];
                    dWeight=fabs((double)Q[i][j])/fabs((double)P[i][j]); 
                    dTmp1=g1*dWeight+(1-dWeight)*g2;
                    dTmp2=g4*dWeight+(1-dWeight)*g3;

                }

            }

            if ((M[i][j]>=dTmp1)&&(M[i][j]>=dTmp2))
            {
                  N.at<uchar>(Point(i,j))=225;

            }else  N.at<uchar>(Point(i,j))=0;

        }
    }
//第五步，选取双阈值
	int nHist[1024];//直方图
	int nEdgeNum;//所有边缘点的数目
	int nMaxMag=0;//最大梯度的幅值
	for(int k=0;k<1024;k++)
	{
		 nHist[k]=0;
	}
	for (int wx=0;wx<mat_m;wx++)
	{
		  for (int hy=0;hy<mat_n;hy++)
		 {
			  if(N.at<uchar>(Point(wx,hy))==225)
			{
			   int Mindex=M[wx][hy];
			   nHist[Mindex]++;//获取梯度直方图
			}
		 }
	}
	nEdgeNum=0;
	for (int index=1;index<1024;index++)
	{
	    if (nHist[index]!=0)
	   {
	       nMaxMag=index;
	   }
	   nEdgeNum+=nHist[index];//经过非极大值抑制后有多少边缘点像素  
	}
	//计算两个阈值
	int nThrHigh;
	int nThrLow;
	double dRateHigh=0.79;
	double dRateLow=0.5;
	int nHightcount=(int)(dRateHigh*nEdgeNum+0.5);
	int count=1;
	nEdgeNum=nHist[1];
	while((nEdgeNum<=nHightcount)&&(count<nMaxMag-1))
	{
		count++;
		nEdgeNum+=nHist[count];
	}	
	nThrHigh=count;
	nThrLow= (int)(nThrHigh*dRateLow+0.5);

//第六步，将经过非极大值抑制后的梯度幅值高于高阈值的像素点保留,低于低阈值的像素点去掉，在两者之间的则搜寻其8邻域，如果有高于高阈值的，则原像素点保留
	//对第二种保留的像素点，寻找其所在的低连通边缘

	for(int i=1;i<mat_m-1;i++)
		for(int j=1;j<mat_n-1;j++)
		{
			if(N.at<uchar>(Point(i,j))==225 && M[i][j]>=nThrHigh)
				N.at<uchar>(Point(i,j))=255;
			else if(N.at<uchar>(Point(i,j))!=225 || M[i][j]<nThrLow)
				N.at<uchar>(Point(i,j))=0;
			else if(N.at<uchar>(Point(i,j))==225 && M[i][j]>=nThrLow && M[i][j]<nThrHigh)
			{
				for(int k=0;k<8;k++){
					if(M[i+X[k]][j+Y[k]]>=nThrHigh)
					{	N.at<uchar>(Point(i,j))=255;
						PointReserved=true;
						isVis[i][j]=true;
						break;}
				}
				if(PointReserved==false) N.at<uchar>(Point(i,j))=0;
			}
		}

	for(int i=1;i<mat_m-1;i++)
		for(int j=1;j<mat_n-1;j++)
		{
			if(isVis[i][j]==true){
				Node s;
				s.x=i;
				s.y=j;
				BFS(s,N,M,nThrLow,nThrHigh);
			}
		}

//opencv的canny算子
	Mat O=Mat(mat_n,mat_m,CV_8U,Scalar::all(0));
	Canny(imgGauss,O,nThrLow,nThrHigh,3);


	//显示
	imshow("Canny of OpenCV",O);
	waitKey(50);
	imshow("Canny of my own",N);
	waitKey(0);
	destroyAllWindows();
}