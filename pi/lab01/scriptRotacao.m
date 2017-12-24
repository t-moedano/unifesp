%Thauany Moedano
%RA 92486

%Entradas básicas
image = imread('gaviao_cinza.jpg');
[line,colunm] = size(image);
alfa = pi/6;


%Rotação normal
imageRotatedSimple = zeros(line,colunm);

for u = 1:line
    for v = 1:colunm
        f = (u - line/2) * cos(alfa) + (v - colunm/2) * sin(alfa) + line/2;
        g = - (u - line/2) * sin(alfa) + (v - colunm/2) * cos(alfa) + colunm/2;
        if(f >= 1 & f <= line & g >= 1 & g <= colunm)
            imageRotatedSimple(round(f), round(g)) = image(u, v);
        end
    end
end

%Rotação inversa
imageRotated = zeros(line,colunm);

for u = 1:line
    for v = 1:colunm
        f = (u - line/2) * cos(alfa) + (v - colunm/2) * sin(alfa) + line/2;
        g = - (u - line/2) * sin(alfa) + (v - colunm/2) * cos(alfa) + colunm/2;
        if(f >= 1 & f <= line & g >= 1 & g <= colunm)
            imageRotated(u, v) = image(round(f), round(g));
        end
    end
end

%Cisalhamento horizontal
imageCisH = zeros(line, colunm);
ch = 0.25; 
for u = 1:line
    for v = 1:colunm
        f = u;
        g = v - u * ch;
        if(f >= 1 & f <= line & g >= 1 & g <= colunm)
            imageCisH(u, v) = image(round(f), round(g));
        end
    end
end

%Cisalhamento Vertical
imageCisV = zeros(line, colunm);
cv = 0.2; 
for u = 1:line
    for v = 1:colunm
        f = u - v * cv;
        g = v;
        if(f >= 1 & f <= line & g >= 1 & g <= colunm)
            imageCisV(u, v) = image(round(f), round(g));
        end
    end
end

%Cisalhamento Composto
imageCisHV = zeros(line, colunm);
cv = 0.25;
ch = -0.1;
for u = 1:line
    for v = 1:colunm
        f = u - v * cv;
        g = v - u * ch;
        if(f >= 1 & f <= line & g >= 1 & g <= colunm)
            imageCisHV(u, v) = image(round(f), round(g));
        end
    end
end

%Informação Básica Escala
sx = 1.5;
sy = 1.5;
lineScale = round(line * sx);
colunmScale = round(colunm * sy);


%Escala Inversa
imageScale = zeros(lineScale, colunmScale);

for u = 1:lineScale
    for v = 1:colunmScale
        f = round(u / sx);
        g = round(v / sy);
        if(f > 0 & f <= line & g > 0 & g <= colunm)
            imageScale(u,v) = image(f,g);
        end
    end
end


%Interpolação Bilinear
imageBilinear = zeros(lineScale, colunmScale);

for u = 1:lineScale
    for v = 1:colunmScale
        x = round(u / sx);
        y = round(v / sy);
        dx = abs((u/sx) - x);
        dy = abs((v/sy) - y);
        f = round(((1-dx)*(1-dy)*x + dx*(1-dy)*(x+1) + (1 - dx)*dy*x + dx*dy*(x+1)));
        g = round(((1-dx)*(1-dy)*y + dx*(1-dy)*(y) + (1 - dx)*dy*(y+1) + dx*dy*(y+1)));
        if(f > 0 & f <= line & g > 0 & g <= colunm)
            imageBilinear(u,v) = image(f,g);
        end
    end
end


%Interpolação Bicúbica
imageBicubic = zeros(lineScale, colunmScale);

for u = 1:lineScale
    for v = 1:colunmScale
        x = round(u / sx);
        y = round(v / sy);
        dx = abs((u/sx) - x);
        dy = abs((v/sy) - y);
        
        sumF = 0;
        sumG = 0;
        for m = -1:2
            for n = -1:2
                sumF = sumF + (x-m)* R(m-dx)*R(dy-n);
                sumG = sumG + (y-n)* R(m-dx)*R(dy-n);
            end
        end
        f = round(sumF);
        g = round(sumG);
        if(f > 0 & f <= line & g > 0 & g <= colunm)
            imageBicubic(u,v) = image(f,g);
        end
    end
end

%Rotação Bilinear
imageRotBilinear = zeros(lineScale, colunmScale);

for u = 1:lineScale
    for v = 1:colunmScale
        x = round((u - line/2) * cos(alfa) + (v - colunm/2) * sin(alfa) + line/2);
        y = round(- (u - line/2) * sin(alfa) + (v - colunm/2) * cos(alfa) + colunm/2);
        dx = abs((u - line/2) * cos(alfa) + (v - colunm/2) * sin(alfa) + line/2 - x);
        dy = abs(- (u - line/2) * sin(alfa) + (v - colunm/2) * cos(alfa) + colunm/2 - y);
        f = round(((1-dx)*(1-dy)*x + dx*(1-dy)*(x+1) + (1 - dx)*dy*x + dx*dy*(x+1)));
        g = round(((1-dx)*(1-dy)*y + dx*(1-dy)*(y) + (1 - dx)*dy*(y+1) + dx*dy*(y+1)));
        if(f > 0 & f <= line & g > 0 & g <= colunm)
            imageRotBilinear(u,v) = image(f,g);
        end
    end
end


%Rotação Interpolação Bicúbica
imageRotBicubic = zeros(lineScale, colunmScale);

for u = 1:lineScale
    for v = 1:colunmScale
        x = round((u - line/2) * cos(alfa) + (v - colunm/2) * sin(alfa) + line/2);
        y = round(- (u - line/2) * sin(alfa) + (v - colunm/2) * cos(alfa) + colunm/2);
        dx = abs((u - line/2) * cos(alfa) + (v - colunm/2) * sin(alfa) + line/2 - x);
        dy = abs(- (u - line/2) * sin(alfa) + (v - colunm/2) * cos(alfa) + colunm/2 - y);
        
        sumF = 0;
        sumG = 0;
        for m = -1:2
            for n = -1:2
                sumF = sumF + (x-m)* R(m-dx)*R(dy-n);
                sumG = sumG + (y-n)* R(m-dx)*R(dy-n);
            end
        end
        f = round(sumF);
        g = round(sumG);
        if(f > 0 & f <= line & g > 0 & g <= colunm)
            imageRotBicubic(u,v) = image(f,g);
        end
    end
end




%Plotando figuras
colormap(gray);
imagesc(imageRotatedSimple);
truesize();
title('Figura 11: Rotação - Vizinho Mais Próximo');%%%%
figure();


colormap(gray);
imagesc(image);
title('Figura 1: Original');
figure();
%%%%%%%%
colormap(gray);
imagesc(imageRotated);
title('Figura 2: Rotação Inversa');
figure();
%%%%%%%%
colormap(gray);
imagesc(imageCisH);
title('Figura 3: Cisalhamento Horizontal ch = 0.25');
figure();
%%%%%%%%
colormap(gray);
imagesc(imageCisV);
title('Figura 4: Cisalhamento Vertical cv = 0.2');
figure();
%%%%%%%%
colormap(gray);
imagesc(imageCisHV);
title('Figura 5: Cisalhamento Composto cv = 0.25 ch = -0.1');
figure();
%%%%%%%%
colormap(gray);
imagesc(imageScale);
title('Figura 6: Escala Inversa');
figure();
%%%%%%%%

colormap(gray);
imagesc(imageBilinear);
title('Figura 7: Escala - Interpolação Bilinear');
truesize();
figure();
%%%%%%%%
colormap(gray);
imagesc(imageBicubic);
truesize();
title('Figura 8: Escala - Interpolação Bicúbica');
figure();

%%%%%%%%%%%%
colormap(gray);
imagesc(imageRotBilinear);
title('Figura 9: Rotação - Interpolação Bilinear');
truesize();
figure();
%%%%%%%%
colormap(gray);
imagesc(imageRotBicubic);
truesize();
title('Figura 10: Rotação - Interpolação Bicúbica');

%%%%
%%%%%%%%



