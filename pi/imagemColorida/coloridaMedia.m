clear all

I = imread('fig2.tif');

R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);

[l,c] = size(R);

%filtrar cada canal RGB

filR = media(R);
filG = media(G);
filB = media(B);


%Associar na imagem

I(:,:,1) = filR;
I(:,:,2) = filG;
I(:,:,3) = filB;

%converter para hsi

hsi = rgb_to_hsi(I);

%filtrar o canal I
hsi_I = hsi(:,:,3);
filHSI = media(hsi_I);
hsi(:,:,3) = filHSI;

%converter imagem filtrada para o RGB
rgbNew = hsi_to_rgb(hsi);

figure;
imshow(I);

figure;
imshow(rgbNew);

figure;
imshow(abs(double(rgbNew)-hsi));

%colorida2;
