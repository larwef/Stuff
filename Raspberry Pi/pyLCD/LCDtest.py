import sys
import serial
import time

mySerial = serial.Serial('/dev/ttyAMA0', 9600, timeout = 1)
mySerial.open()

while True:
	try:
		mySerial.write(chr(254)) # move cursor to beginning of first line
		mySerial.write(chr(128))
		mySerial.write("                ")
		mySerial.write("                ")
		
		mySerial.write(chr(254))
		mySerial.write(chr(128))
		mySerial.write("Test:")

		for i in range(0,20):
			mySerial.write(chr(254))
			mySerial.write(chr(133))
			mySerial.write(str(i))
			time.sleep(0.5)

	except KeyboardInterrupt:
		print "Program stopped"
		mySerial.close()
		sys.exit()