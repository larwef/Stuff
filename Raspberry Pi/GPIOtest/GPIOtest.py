import RPi.GPIO as GPIO
from socket import *
import sys
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(24, GPIO.IN)
GPIO.setup(26, GPIO.OUT)

host = "192.168.1.255"
port = 12000

serverSocket = socket(AF_INET,SOCK_DGRAM)
serverSocket.bind((host, port))

while True:
	try:
		message, address = serverSocket.recvfrom(1024)
		print "Recieved: " + message

		if message.lower() == "on":
			GPIO.output(26, True)
		elif message.lower() == "off":
			GPIO.output(26, False)
		else:
			print "Invalid message"

		if GPIO.input(24):
			print "Led is on"
		else:
			print "Led is off"

	except KeyboardInterrupt:
		GPIO.cleanup()
		print "Program stopped"
		sys.exit()