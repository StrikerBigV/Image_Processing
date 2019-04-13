function B = E3( A )
%UNTITLED2 此处显示有关此函数的摘要
%   此处显示详细说明
[m,n]=size(A);
for i=1:m
    for j=1:n
        if A(i,j)<0
            B(i,j)=0;
        elseif 1/2*A(i,j)>255
            B(i,j)=255;
        else B(i,j)=1/2*A(i,j);
        end
    end

end

