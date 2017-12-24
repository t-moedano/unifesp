
g++ -o buscaProfundidade buscaProfundidade.cpp

g++ -o buscaLargura buscaLargura.cpp

g++ -o buscaGulosa buscaGulosa.cpp



ECHO Rodando Busca Profundidade

FOR /L %%i IN (1,1,100) DO buscaProfundidade


ECHO Rodando Busca Largura

FOR /L %%i IN (1,1,100) DO buscaLargura


ECHO Rodando Busca Gulosa

FOR /L %%i IN (1,1,100) DO buscaGulosa
 
