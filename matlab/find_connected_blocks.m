I=imread('D:\Image\2.jpg');%��ȡ��ɫͼ��
G=rgb2gray(I);%����ɫͼ��ת���ɻҶ�ͼ��
gray_level=graythresh(G);%��ȡ�Ҷ���ֵ
B=im2bw(G,gray_level);%���ݻҶ���ֵ���Ҷ�ͼ��ת���ɶ�ֵͼ��
[l,n]=bwlabel(B,8)%��ȡ��Ǿ�����ͨ��������8��ʾ8��ͨ

imshow(B)
hold on
for k=1:n
[r,c]=find(l==k);%�ҵ���ͨ��k��λ��
rbar=mean(r);
cbar=mean(c);
plot(cbar,rbar,'Marker','o','MarkerEdgeColor','k','MarkerFaceColor','k','MarkerSize',10);
plot(cbar,rbar,'Marker','*','MarkerEdgecolor','w');
end
