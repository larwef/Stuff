import serial

ser = serial.Serial('/dev/ttyAMA0', 9600, timeout = 1)
ser.open()

pos = raw_input("Velg posisjon: ")
speed = raw_input("Velg fart: ")
accel = raw_input("Akselerasjon: ")
pos = int(pos)
speed = int(speed)
accel = int(accel)

#one = chr(170) #Start byte
#two = chr(12) #Device number
#three = chr(4) #Command number
#four = chr(0) #Servo number
#five = chr(pos & 127)
#six = chr((pos >> 7) & 127)

#command = one + two + three + four + five + six

#byteone = int(254*pos/180)
#data = chr(0xFF)+chr(0)+chr(byteone)

lsb = speed & 0x7f #7 bits for least significant byte
msb = (speed >> 7) & 0x7f #shift 7 and take next 7 bits for msb
# Send Pololu intro, device number, command, channel, speed lsb, speed msb
cmd = chr(0xaa) + chr(0x0c) + chr(0x07) + chr(0) + chr(lsb) + chr(msb)
ser.write(cmd)

lsb = accel & 0x7f #7 bits for least significant byte
msb = (accel >> 7) & 0x7f #shift 7 and take next 7 bits for msb
# Send Pololu intro, device number, command, channel, accel lsb, accel msb
cmd = chr(0xaa) + chr(0x0c) + chr(0x09) + chr(0) + chr(lsb) + chr(msb)
ser.write(cmd)

pos = pos * 4
poslo = (pos & 0x7f)
poshi = (pos >> 7) & 0x7f
chan  = 0
data =  chr(0xaa) + chr(0x0c) + chr(0x04) + chr(chan) + chr(poslo) + chr(poshi)

ser.write(data)

pos = raw_input("Velg posisjon: ")
pos =int(pos)
pos = pos * 4
poslo = (pos & 0x7f)
poshi = (pos >> 7) & 0x7f
chan  = 0
data =  chr(0xaa) + chr(0x0c) + chr(0x04) + chr(chan) + chr(poslo) + chr(poshi)

ser.write(data)

data =  chr(0xaa) + chr(0x0c) + chr(0x10) + chr(chan)
ser.write(data)
w1 = ord(ser.read())
w2 = ord(ser.read())

print (w1 << 8) + w2

data =  chr(0xaa) + chr(0x0c) + chr(0x21)
ser.write(data)
w1 = ord(ser.read())
w2 = ord(ser.read())

print (w1 << 8) + w2

ser.close()