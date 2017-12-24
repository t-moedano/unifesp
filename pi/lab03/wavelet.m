N = 1024
for n = 1:N
    m = (n-1) / N;
    g(n) = 20 * m^2 * (1-m)^4 * cos(12*pi*m);
end

figure
plot(g)

i = 1;
media = zeros(512,1);
detalhe = zeros(512,1);


for n = 1:2:N
    
     media(i) =  ( g(n) + g(n+1) ) / sqrt(2);
     detalhe(i) = ( g(n+1) - g(n) ) / sqrt(2);
    
    i = i + 1;
end

sinalTransformado = [media;detalhe];

inverso = zeros(1024,1);

i = 1;
for j = 1:2:N
    inverso(j) = ( media(i) + detalhe(i) ) / sqrt(2);
    inverso(j+1) = ( media(i) - detalhe(i) ) / sqrt(2);
    i = i + 1;
end

figure,plot(g)
hold on
plot(inverso)
hold off

%nivel 2


N = 512
i = 1;
media2 = zeros(256,1);
detalhe2 = zeros(256,1);


for n = 1:2:N
    
     media2(i) =  ( media(n) + media(n+1) ) / sqrt(2);
     detalhe2(i) = ( media(n+1) - media(n) ) / sqrt(2);
    
    i = i + 1;
end

sinalTransformado2 = [media2;detalhe2];

inverso2 = zeros(512,1);

i = 1;
for j = 1:2:N
    inverso2(j) = ( media2(i) + detalhe2(i) ) / sqrt(2);
    inverso2(j+1) = ( media2(i) - detalhe2(i) ) / sqrt(2);
    i = i + 1;
end

figure,plot(media2)
hold on
plot(inverso2)
hold off