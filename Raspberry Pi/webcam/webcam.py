from socket import *
import picamera

serverSocket = socket(AF_INET, SOCK_STREAM)
HOST = ''
PORT = 8080

serverSocket.bind((HOST,PORT))
serverSocket.listen(1)

camera = picamera.PiCamera()
camera.vflip = True
camera.hflip = True

while True:
	print 'Ready to serve...'
	connectionSocket, addr = serverSocket.accept()
	print 'Got connection from', addr

	try:
		camera.capture('pic.jpg')
		image = open('pic.jpg', 'rb')
		image_data = image.read()
		image.close()

		connectionSocket.send('HTTP/1.1 200 OK\r\n')
		
		connectionSocket.send('Content-Type: image/jpg\r\n\r\n')
		connectionSocket.send(image_data)
		connectionSocket.close()
		
	except IOError:
		f = open('404.html')
		fof = f.read()
		connectionSocket.send('HTTP/1.1 404 Not Found\r\n\r\n')
		connectionSocket.send(fof)

		connectionSocket.close()
		break

	except KeyboardInterrupt:
		connectionSocket.close()
		print "Program stopped"
		break
	
serverSocket.close()
sys.exit()