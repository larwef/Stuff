import sys
import time
from servoController import *
import RPi.GPIO as GPIO
 
# Henta fra http://rosettacode.org/wiki/Keyboard_input/Keypress_check#Python
try:
    from msvcrt import getch
except ImportError:
    def getch():
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

GPIO.setmode(GPIO.BOARD)
GPIO.setup(18, GPIO.OUT)

servo = ServoController()

servo.setAccel(0,0)
servo.setSpeed(0,0)

posx = 1500
posy = 1500

laser = False

while True:
	try:
		char = getch()

		if char is not None:
			if char == 'a':
				posx += 30

			if char == 'w':
				posy += 30

			if char == 's':
				posy -= 30

			if char == 'd':
				posx -= 30

			if char == 'e':
				if laser == False:
					laser = True
					GPIO.output(18, True)
				else:
					laser = False
					GPIO.output(18, False)


			if char == '\x03':
				sys.exit()

		if posx > 650 and posx < 2300:
			servo.setPos(0, posx)
		if posy > 650 and posy < 2300:
			servo.setPos(1, posy)
		time.sleep(0.01)


	except KeyboardInterrupt:
		print "Program stopped"
		servo.Close()
		GPIO.cleanup()
		sys.exit()