function[x] = mediana(img)

[linha,coluna] = size(img);
x = zeros(linha,coluna);
vetor = zeros(1,9);

for i = 1:linha
    for j = 1:coluna
        if(i-1 > 0 && j-1 >0 && j+1 <= coluna && i+1 <= linha)
           indice = 1;
           for a = i-1:i+1
               for b=j-1:j+1
                   vetor(indice) = img(a,b);
                   indice = indice+1;
               end
           end
           vetor = sort(vetor);
           x(i,j) = vetor(5);
        else
            x(i,j) = img(i,j);
        end
    end
end


return;