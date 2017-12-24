%Função que calcula o R
function r = R(s)
    r = (P(s+2)^3 - 4*P(s+1)^3 + 6*P(s)^3 -4*P(s-1)^3)/6;
end

