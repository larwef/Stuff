import random
from socket import *

host = "192.168.1.255"
port = 12000

clientSocket = socket(AF_INET,SOCK_DGRAM)
clientSocket.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

while True:
	message = raw_input("Message: ")
	clientSocket.sendto(message, (host, port))