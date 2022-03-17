clear all;
close all;

data = csvread("example.txt");

img = zeros(data(end,1)+1, data(end,2)+1,3);

for i = 1:size(data,1)
  row = data(i,1)+1;
  col = data(i,2)+1;
  img(row, col,1) = data(i,3);
  img(row, col,2) = data(i,4);
  img(row, col,3) = data(i,5);
end

figure();
imshow(img);

