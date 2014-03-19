from socket import *
import time

clientSocket = socket(AF_INET,SOCK_DGRAM)
clientSocket.settimeout(1)

SERV = '192.168.1.235'
PORT = 12000

for i in range(0,10):
	print ('Sending ping ' + str(i+1) + '...')
	
	startTime = time.time()
	clientSocket.sendto('ping', (SERV, PORT))
	
	try:
		response = clientSocket.recvfrom(1024)
		elapsedTime = time.time() - startTime
		print 'Response: ' + str(response[0])
		print 'Time: ' + str(elapsedTime) + '\n'
	except:
		print 'Request timed out\n'
	
