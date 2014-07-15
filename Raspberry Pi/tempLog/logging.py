# Temperature logging program using Raspberry Pi and Arduino. The Arduino is used to read an analog
# temperature sensor. The Arduino will read and send the value over serial communication when it
# recieves anything on its own serial-inn port.
# 
# Author Lars Wefald
#
# Some of the code and the circuit between the Arduino and the Pi is taken from:
# http://blog.oscarliang.net/raspberry-pi-and-arduino-connected-serial-gpio/
# This is a good tutorial for getting you started with using serial on RPi.
#
# The Arduino code is in a seperate file.

import RPi.GPIO as GPIO
import sys
import serial
import time
import datetime

resetPin = 16;

# The program is made for recording and writing a sample with a few minutes between each sample.
# It is not well suited for sampling with few seconds intervals becuse of the time the program uses.
# It is however possible to do it for testing purposes.
# The timing of sampletimes is a bit dogy and may result in shifting of samples (e.g. start at 12.00
# with and interval of 5min and ending up with a sample at 13.11 then 13.16 etc.) even though this
# problem should be resolved by line 72.
sampleIntervalH = 0; # Sampe interval hours
sampleIntervalM = 5; # Sampe interval minutes
sampleIntervalS = 0; # Sampe interval seconds
failCount = 0; # Keeps track of no. of fails, resets Arduino at a certain number.

#Setup part
print "Setting up..."
GPIO.setmode(GPIO.BOARD) # Pins assigned by pin number.
GPIO.setup(resetPin, GPIO.OUT) # Sets up the in used to reset the Arduino board.

ser = serial.Serial('/dev/ttyAMA0', 9600, timeout = 1)
ser.open()

GPIO.output(resetPin, True)
time.sleep(1)
GPIO.output(resetPin, False)
time.sleep(2)
print "Setup complete.\n"

# Operational Part.
nextSampleTime = datetime.datetime.today()
while True:
	try:
		currentTime = datetime.datetime.today()
		if currentTime > nextSampleTime:
			timeStamp = datetime.datetime.now().strftime("%d/%m/%Y %H:%M")
			print "Getting temperature..."
			ser.write(" ")
			temp = ser.readline().rstrip("\r\n")

			if temp == "": #If the read times out. Used instead of exceptions.
				print "Failed to get temperature"
				errorLog = open("errorLog.txt", "a")
				errorLog.write(timeStamp + "Failed to get temperature\n")
				failCount += 1
				if failCount == 3:
					print "Resetting Arduino board..."
					errorLog.write(timeStamp + "Resetting Arduino board\n")
					GPIO.output(resetPin, True)
					time.sleep(1)
					GPIO.output(resetPin, False)
					time.sleep(1)
					print "Board reset."
				errorLog.close()
			else:
				currentTime = currentTime.replace(microsecond = 0)
				nextSampleTime = (currentTime + 
					datetime.timedelta(hours = sampleIntervalH) +
					datetime.timedelta(minutes = sampleIntervalM) +
					datetime.timedelta(seconds = sampleIntervalS))
				failCount = 0
				tempLog = open("tempLog.txt", "a")
				tempLog.write(timeStamp + " " + temp + "\n")
				print "Temperature: " + temp + " @ " + timeStamp
				tempLog.close()
		else:
			time.sleep(1)

	except KeyboardInterrupt:
		print "Program stopped"
		ser.close()
		GPIO.cleanup()
		sys.exit()