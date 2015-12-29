# Help from examples:
# https://github.com/FRC4564/Maestro/blob/master/maestro.py
# http://martinsant.net/?page_id=479

# Simple modifications can be made to make it function on daisy chained devices.

import serial

serialConn = '/dev/ttyAMA0'
baudRate = 9600
timeout = 1
deviceNo = 0x0c

class ServoController:
	def __init__(self):
		self.ser = serial.Serial(serialConn, baudRate, timeout = timeout)
		self.ser.open()

	def close(self):
		self.ser.close()

	def setAccel(self, chan, accel):
		cmdByte = 0x09
		loBits = accel & 0x7f
		hiBits = (accel >>7) & 0x7f
		cmd = chr(0xaa) + chr(deviceNo) + chr(cmdByte) + chr(chan) + chr(loBits) + chr(hiBits)
		self.ser.write(cmd)
		return

	def setSpeed(self, chan, speed):
		cmdByte = 0x07
		loBits = speed & 0x7f
		hiBits = (speed >>7) & 0x7f
		cmd = chr(0xaa) + chr(deviceNo) + chr(cmdByte) + chr(chan) + chr(loBits) + chr(hiBits)
		self.ser.write(cmd)
		return

	def setPos(self, chan, pos):
		pos = int(pos * 4)
		cmdByte = 0x04
		loBits = pos & 0x7f
		hiBits = (pos >>7) & 0x7f
		cmd = chr(0xaa) + chr(deviceNo) + chr(cmdByte) + chr(chan) + chr(loBits) + chr(hiBits)
		self.ser.write(cmd)
		return

	def getPos():
		cmd = chr(0xaa) + chr(deviceNo) + chr(0x10) + chr(chan)
		self.ser.write(cmd)
		loBits = ord(self.ser.read())
		hiBits = ord(self.ser.read())
		return (hiBits << 8) + loBits

	def getMovingState():
		cmd = chr(0xaa) + chr(deviceNo) + chr(0x13)
		self.ser.write(cmd)
		if self.ser.read() == chr(0):
			return False
		else:
			return True
	def getError():
		cmd =  chr(0xaa) + chr(deviceNo) + chr(0x21)
		self.ser.write(data)
		w1 = ord(self.ser.read())
		w2 = ord(self.ser.read())
		return w1, w2
