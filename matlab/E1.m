function B = E1( A )
%UNTITLED2 �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
[m,n]=size(A);
for i=1:m
    for j=1:n
        if A(i,j)<0
            B(i,j)=0;
        elseif 2*A(i,j)>255
            B(i,j)=255;
        else B(i,j)=2*A(i,j);
        end
    end

end

