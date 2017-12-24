I = imread('figura1.jpg');
vi = (0:255);
n = zeros(256,1);
h = zeros(1,256);

for u = 0:255
    h(u+1) = length(find(I==u)
    );
end

for i = 1:256
    %classe 1
    v1 = (0:i-1);
    h1 = h(1:i);
    w1 = sum(h1);
    
    %classe 2
    v2 = (i:255);
    h2 = h(i+1:256);
    w2 = sum(h2);
    
    ms1 = double(sum(v1.*h1));
    ms2 = double(sum(v2.*h2));
    
    m1 = ms1/w1;
    m2 = ms2/w2;
    mg = ms1 + ms2;
    
    varg = sum(((vi - mg).^2).*h);
    varb = w1*w2*((m1-m2)^2);
    n(i) = varb/varg;
end

T = find(n==max(n)); %indice com valor maximo de n

[l,c] = size(I);
mascaras = zeros(l,c);

for i = 1:l
    for j = 1:c
        if(I(i,j) > T)
            mascaras(i,j) = 1;
        else
            mascaras(i,j) = 0;
        end  
    end
end


colormap(gray);
figure;
imagesc(mascaras);
title('mascara');


colormap(gray);
figure;
imagesc(I);
title('imagem');