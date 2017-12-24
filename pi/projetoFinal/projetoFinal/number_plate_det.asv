%Thauany Moedano
%Wellington Chagas
%Projeto Final  

%Limpando a tela
clc
close all;
clear;
load imgfildata;

%Lendo e carregando imagem
[arquivo,caminho] = uigetfile({'*.jpg;*.bmp;*.png;*.tif'},'Choose an image');
imagem = [caminho,arquivo];
imagem = imread(imagem);
[~,cc] = size(imagem);
imagem = imresize(imagem,[300 500]);
imagem = rgb2gray(imagem);


%Binarização por Otsu
limiarGlobal = graythresh(imagem);
imagem = imbinarize(imagem,limiarGlobal);
imagem = ~imagem;

%Passos para remover componentes indesejados - Faz operações para remover
%componentes conexos menores que X pixels. 
imagem = bwareaopen(imagem,1900);
imshow(imagem)
title('dps de tirar 2200px');

if cc > 2000
    imagemSemRuido1 = bwareaopen(imagem,6500);
else
    imagemSemRuido1 = bwareaopen(imagem,6000);
end


figure;
imshow(imagemSemRuido1);
title('dps de tirar 6000 ou 6500 px');


imagemSemRuido2 = imagem-imagemSemRuido1;
figure;
imshow(imagemSemRuido2);
%titulo ?

imagemSemRuido2 = bwareaopen(imagemSemRuido2,200);
figure;
imshow(imagemSemRuido2);
%titulo ?

[matrizRotulos,numComponentes] = bwlabel(imagemSemRuido2);
bordasImagem = regionprops(matrizRotulos,'BoundingBox');

hold on
pause(1)
for i = 1:size(bordasImagem,1)
  rectangle('Position',bordasImagem(i).BoundingBox,'EdgeColor','g','LineWidth',2)
end
hold off

figure
placa = [];
t = [];

%O que isso faz ?
for i = 1:numComponentes
  [r,c] = find(matrizRotulos==i);
  n1=imagem(min(r):max(r),min(c):max(c));
  n1=imresize(n1,[32,16]);
  imshow(n1)
  pause(0.2)
  x=[ ];
%O que isso faz ?
  totalLetters=size(imgfile,2);
  for k=1:totalLetters    
    y = corr2(imgfile{1,k},n1);
    %correlação das assinaturas 
    x=[x y];
  end
 
 %Se a correlação for superior a 45%, é um match 
 if max(x)>.45
     z = find(x==max(x));
     out = cell2mat(imgfile(2,z));
     
     %Como o algoritmo confunde muito 1 com I, O com 0 e B com 8, verifica
     %a posição na placa para identificar se é letra ou número. 
     if (out == '1I')
         if(i <= 3)
             out = 'I';
         else
             out = '1';
         end
     end
     
     if(out == '0O')
         if(i<=3)
             out = 'O';
         else
             out = '0';
         end
     end
     
     if(out == 'B8')
         if(i<=3)
             out = 'O';
         else
             out = '0';
         end
     end
     
     placa = [placa out];
 end
end

