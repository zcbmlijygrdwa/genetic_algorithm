clear all;
close all;

files = dir(".");

for i = 1:size(files,1)
  file = files(i).name;
  res = strfind(file, ".bd");
  
  if(size(res,1)>0)
    
    tokens = strsplit(file, ".");
    file_name = tokens{1}
    
    % if jpg already exists, skip this one
    if(exist(["images/" file_name ".jpg"])>0)
      continue;
    end
    
    
    data = csvread(file);
    img = zeros(data(end,1)+1, data(end,2)+1,3);

    
    
for i = 1:size(data,1)
  row = data(i,1)+1;
  col = data(i,2)+1;
  img(row, col,1) = data(i,3);
  img(row, col,2) = data(i,4);
  img(row, col,3) = data(i,5);
end

imwrite(img,["images/" file_name ".jpg"]);

%figure();
%imshow(img);  
  end
end




