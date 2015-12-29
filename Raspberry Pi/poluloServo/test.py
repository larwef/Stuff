import time
import sys
from math import *
import RPi.GPIO as GPIO
from servoController import *

a = 1500;
b = 1500;
r = sqrt(250000/2)

servo = ServoController()

GPIO.setmode(GPIO.BOARD)
GPIO.setup(18, GPIO.OUT)

GPIO.output(18, True)

servo.setAccel(0,0)
servo.setSpeed(0,0)

servo.setPos(1,1000)
servo.setPos(0,1500)

while True:
	try:
		for theta in range(0,360):
			x = a + r*cos(radians(theta))
			y = a + r*sin(radians(theta))

			servo.setPos(0, x)
			servo.setPos(1, y)
			time.sleep(0.01)

	except KeyboardInterrupt:
		print "Program stopped"
		servo.close()
		GPIO.output(18, False)
		GPIO.cleanup()
		sys.exit()

servo.close()