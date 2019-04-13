I=imread('D:\Image\2.jpg');%读取彩色图像
G=rgb2gray(I);%将彩色图像转换成灰度图像
gray_level=graythresh(G);%获取灰度阈值
B=im2bw(G,gray_level);%根据灰度阈值将灰度图像转换成二值图像
[l,n]=bwlabel(B,8)%获取标记矩阵及连通块数量，8表示8连通

imshow(B)
hold on
for k=1:n
[r,c]=find(l==k);%找到连通块k的位置
rbar=mean(r);
cbar=mean(c);
plot(cbar,rbar,'Marker','o','MarkerEdgeColor','k','MarkerFaceColor','k','MarkerSize',10);
plot(cbar,rbar,'Marker','*','MarkerEdgecolor','w');
end
