
%Thauany Moedano
%Wellington Chagas
%Projeto Final - Primeira abordagem 

%Leitura da imagem
imagem = imread('placa8.jpg');
imagem = rgb2gray(imagem);


%Mostra imagem original
figure;
colormap(gray);
imagesc(imagem);
title('Imagem Original');

%Usa otsu para fazer a binarização da placa 
limiarGlobal = graythresh(imagem);
imagemBinaria = imbinarize(imagem,limiarGlobal);

%Mostra imagem binarizada
figure;
colormap(gray);
imagesc(imagemBinaria);
title('Limiarização por Otsu');


%inverter binarização da imagem (erosao considera branco como objeto e
%preto fundo)
imagemBinariaInvertida = ~imagemBinaria;
figure;
colormap(gray);
imagesc(imagemBinariaInvertida); 

%Cria um elemento estruturante e aplica erosao na imagem para otimizar o
%reconhecimento
%se = strel('sphere',10)
%se = strel('square',18);
%se = strel('line',15,65);
elementoEstruturante = strel('square',16)
imagemErodida = imerode(imagemBinariaInvertida,elementoEstruturante);
figure;
colormap(gray);
imagesc(imagemErodida);

%Remove ruídos restantes
imagemErodida = bwareaopen(imagemErodida,200);

[matrizRotulos,numComponentes]=bwlabel(imagemErodida);

%Pegar assinatura de forma da placa
centroidesImagem = regionprops(matrizRotulos,'Centroid');
bordasImagem = bwboundaries(matrizRotulos);

%Imprime assinatura de forma das imagens
for i = 1 : numComponentes
   centroide = centroidesImagem(i).Centroid;
   borda = bordasImagem(i); 
   coordenadaYBorda = borda{1,1}(:,2);
   coordenadaXBorda = borda{1,1}(:,1);
   distanciaCentroide = sqrt(((coordenadaXBorda-centroide(1)).^2 + coordenadaYBorda-centroide(2)).^2);
   pontosVetor=1:1:length(distanciaCentroide);
   figure(i);
   plot(pontosVetor,distanciaCentroide);
end


