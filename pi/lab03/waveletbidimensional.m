I = imread('palhaco.jpg');
I = double(I);
[l,c] = size(I);

matSinal = zeros(l,c);
matSinalc = zeros(l,c);

media = zeros(c/2, 1);

j = 1;
for i = 1:l
    for n = 1:2:c 
        matSinal(i, j) =  ( I(i,n) + I(i,n+1) ) / sqrt(2);
        matSinal(i,j+(c/2)) = ( I(i,n) - I(i,n+1) ) / sqrt(2);
        j = j + 1;
    end 
    j = 1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

j = 1;
for i = 1:c
    for n = 1:2:c 
        matSinalc(j, i) =  ( matSinal(n,i) + matSinal(n+1,i) ) / sqrt(2);
        matSinalc(j+(l/2),i) = ( matSinal(n,i) - matSinal(n+1,i) ) / sqrt(2);
        j = j + 1;
    end 
    j = 1;
end


figure;
colormap(gray);
imagesc(matSinal);


figure;
colormap(gray);
imagesc(matSinalc); 




%%%%%%%%%%%%%%%%%
%RETORNO

matRetornoC = zeros(l,c);

j = 1;
for i = 1:c
    for n = 1:(l/2) 
        matRetornoC(j, i) =  ( matSinalc(n,i) + matSinalc(n+(l/2) ,i) ) / sqrt(2);
        matRetornoC(j+1,i) = ( matSinalc(n,i) - matSinalc(n+(l/2),i) ) / sqrt(2);
        j = j + 2;
    end 
    j = 1;
end

figure;
colormap(gray);
imagesc(matRetornoC); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

matRetorno = zeros(l,c);

j = 1;
for i = 1:l
    for n = 1:(c/2) 
        matRetorno(i, j) =  ( matRetornoC(i,n) + matRetornoC(i,n+ (c/2)) ) / sqrt(2);
        matRetorno(i,j+1) = ( matRetornoC(i,n) - matRetornoC(i, n + (c/2) ) ) / sqrt(2);
        j = j + 2;
    end 
    j = 1;
end

figure;
colormap(gray);
imagesc(matRetorno); 
