clear all;
close all;

data = imread("data/lion2.png");

data_mat = zeros(size(data,1)*size(data,2)+1,5);

data_mat(1,:) = [size(data,1), size(data,2), 0,0,0];

count = 2;
for i = 1:size(data,1)
  for j = 1:size(data,2)
    data_mat(count,:) = [i-1,j-1,data(i,j,1),data(i,j,2),data(i,j,3)];
    count = count + 1;
  endfor
endfor

csvwrite ("lion2.dat", data_mat);