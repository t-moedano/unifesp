%Thauany Moedano
%RA: 92486

I = imread('Seq2_51.jpg');
vec = zeros(1,256);
probSum = zeros(1,256);
[l,c] = size(I);
sum = 0;
for u = 0:255
    vec(u+1) = length(find(I==u));
end

prob = vec/(c*l);
probSum(1) = prob(1);

for v = 2:256
    probSum(v) = probSum(v-1) + prob(v);
end

newGray = round(probSum * 255);
newImg = zeros(l,c);

for f = 1:l
    for g = 1:c
            newImg(f,g) = newGray(I(f,g)+1);
        
        
    end
end


%%Exponencial

newImgExp = zeros(l,c);
alfa = 3;

probSum(256) = 0.99;

newGrayExp = -((1/alfa)*log(1 - probSum));

newGrayExp(find(newGrayExp>1)) = 1;
   
for f = 1:l
    for g = 1:c
            newImgExp(f,g) = newGrayExp(I(f,g)+1);
      
    end
end


%%Logaritmica

alfa = 0.5;
newGrayLog = zeros(1,length(probSum));

for i = 1:length(probSum)
    newGrayLog(i) = (2*alfa^2 .* log(1/(1-probSum(i))))^(1/2);
end

newGrayLog(find(newGrayLog>1)) = 1;

newImgLog = zeros(l,c);
for f = 1:l
    for g = 1:c
            newImgLog(f,g) = newGrayLog(I(f,g)+1);
       
    end
end

%Hipercúbica
newGrayCubic = zeros(1,length(probSum));

for i = 1:length(probSum)
    newGrayCubic(i) = (nthroot(255,3) * probSum(i))^3;
end


newImgCubic = zeros(l,c);
for f = 1:l
    for g = 1:c
            newImgCubic(f,g) = newGrayCubic(I(f,g)+1);
        
    end
end

%Janela

vec = zeros(1,256);
probSum = zeros(1,256);
[l,c] = size(I);
sum = 0;
newImgWindow = zeros(l,c);

for m = 1: l
    for n = 1:c
        n1 = [7,7];
        for u = 1:7
            for v = 1:7
              n1(u,v) = I(m,n);
            end
        end
        
        for u = 0:255
            vec(u+1) = length(find(n1==u));
        end

        prob = vec/(49);
        probSum(1) = prob(1);

        for v = 2:256
            probSum(v) = probSum(v-1) + prob(v);
        end

        newGrayWindow = round(probSum * 255);
        

        for f = 1:7
            for g = 1:7
                    newImgWindow(m,n) = newGray(I(m,n)+1);


            end
        end
    end
end





%Plot - imagem original
figure;
imagesc(I);
title('Original');
colormap(gray);


%Plot - equalização uniforme
figure;
imagesc(newImg);
title('Uniforme');
colormap(gray);

%Plot - imagem equalizada exp
figure;
imagesc(newImgExp);
title('Exponencial');
colormap(gray);

%Plot - imagem equalizada log
figure;
imagesc(newImgLog);
title('Logaritmica');
colormap(gray);


%Plot - imagem equalizada cubica
figure;
imagesc(newImgCubic);
title('HiperCubica');

%Plot - imagem Window
colormap(gray);
figure;
imagesc(newImgWindow);
title('Janela');
colormap(gray);

