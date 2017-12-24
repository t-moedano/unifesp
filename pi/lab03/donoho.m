%Thauany Moedano
%RA: 92486

%% escolha de nivel e limiar (intensidade) 
nivel = 3;
limiar = 20;
%%


I = imread('Imgem_ruido1.tif');
I = double(I);
I = imresize(I, [512,512]); % -- se necessário, transformar imagem em
%potencia de 2
[l,c] = size(I);

figure;
colormap(gray);
imagesc(I);
title('Original');


matSignalLines = zeros(l,c);
matSignalColunm = zeros(l,c);


for index = 1:nivel
    
    j = 1;
    for i = 1:l
        for n = 1:2:c 
            matSignalLines(i, j) =  ( I(i,n) + I(i,n+1) ) / sqrt(2);
            matSignalLines(i,j+(c/2)) = ( I(i,n) - I(i,n+1) ) / sqrt(2);
            j = j + 1;
        end 
        j = 1;
    end

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    j = 1;
    for i = 1:c
        for n = 1:2:c 
            matSignalColunm(j, i) =  ( matSignalLines(n,i) + matSignalLines(n+1,i) ) / sqrt(2);
            matSignalColunm(j+(l/2),i) = ( matSignalLines(n,i) - matSignalLines(n+1,i) ) / sqrt(2);
            j = j + 1;
        end 
        j = 1;
    end

    I = matSignalColunm; 

    
end

    figure;
    colormap(gray);
    imagesc(matSignalColunm);
    title('Média e detalhes');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Retorno

for index = 1:nivel
    matInversaLines = zeros(l,c);

    j = 1;
    for i = 1:c
        for n = 1:(l/2) 
            matInversaLines(j, i) =  ( matSignalColunm(n,i) + matSignalColunm(n+(l/2) ,i) ) / sqrt(2);
            detalhe = ( matSignalColunm(n,i) - matSignalColunm(n+(l/2),i) ) / sqrt(2);
            %Executa a suavização pelo limiar
            if(detalhe > limiar)
                matInversaLines(j+1,i) = detalhe;
            else
                matInversaLines(j+1,i) = 0;
            end
            j = j + 2;
        end 
        j = 1;
    end

   

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    matInversaColunm = zeros(l,c);

    j = 1;
    for i = 1:l
        for n = 1:(c/2) 
            matInversaColunm(i, j) =  ( matInversaLines(i,n) + matInversaLines(i,n+ (c/2)) ) / sqrt(2);
            detalhe = ( matInversaLines(i,n) - matInversaLines(i, n + (c/2) ) ) / sqrt(2);
            if detalhe > limiar
                matInversaColunm(i,j+1) = detalhe;
            else
                 matInversaColunm(i,j+1) = 0;
            end
            j = j + 2;
        end 
        j = 1;
    end

   
    
    matSignalColunm = matInversaColunm;
end

    figure;
    colormap(gray);
    imagesc(matInversaColunm);
    title('Imagem suavizada');
   
