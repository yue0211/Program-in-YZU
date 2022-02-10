import time
from enum import Enum
import RPi.GPIO as GPIO
import spidev
import struct
import RPi.GPIO as GPIO
import math
spi = spidev.SpiDev()
spi.open(0, 0)
spi.mode = 0b11
spi.max_speed_hz = 2000000
BUZZ_PIN = 16
pitches = [262, 294, 330, 349, 392, 440, 493]
GPIO.setmode(GPIO.BOARD)
GPIO.setup(BUZZ_PIN, GPIO.OUT)
pwm = GPIO.PWM(BUZZ_PIN, pitches[0])
pwm.start(0)
#pwm = GPIO.PWM(BUZZ_PIN, pitches[0])
#pwm.start(0)

def writeByte(reg, val):
    spi.xfer2([reg, val])

def writeRegBytes(reg, vals):
    packet = [0] * (len(vals) + 1)
    packet[0] = reg | 0x40
    packet[1:(len(vals)+1)] = vals
    spi.xfer2(packet)

def readByte(reg):
    packet = [0] * 2
    packet[0] = reg | 0x80
    reply = spi.xfer2(packet)
    return reply[1]

deviceID = readByte(0x00)
print("ID: %x" % deviceID)

# ADXL345 address, 0x53(83)
# Select power control register, 0x2D(45)
# 0x08(08) Auto Sleep disable
writeByte(0x2D, 0x00)
time.sleep(0.1)
writeByte(0x2D, 0x08)

# ADXL345 address, 0x53(83)
# Select data format register, 0x31(49)
# 0x08(08) Self test disabled, 4-wire interface
# Full resolution, Range = +/-2g
writeByte(0x31, 0x08)

time.sleep(0.5)

try:
    while True:
        # ADXL345 address, 0x53(83)
        # Read data back from 0x32(50), 2 bytes
        accel = {'x' : 0, 'y' : 0, 'z': 0}
        # X-Axis LSB, X-Axis MSB
        data0 = readByte(0x32)
        data1 = readByte(0x33)
        # Convert the data to 10-bits
        xAccl = struct.unpack('<h', bytes([data0, data1]))[0]
        accel['x'] = xAccl / 256
        number = (xAccl / 256 ) // 0.14285
        #number1 = (int)number
       # round(number)
      #  print(number)
       # print(type(number))
        pwm.ChangeDutyCycle(50)
        print(pitches[round(number)])
        pwm.ChangeFrequency(pitches[round(number)])
        time.sleep(1)
        pwm.ChangeDutyCycle(0)
        time.sleep(1) 
        # ADXL345 address, 0x53(83)
        # Read data back from 0x34(52), 2 bytes
        # Y-Axis LSB, Y-Axis MSB
        data0 = readByte(0x34)
        data1 = readByte(0x35)
        # Convert the data to 10-bits
        yAccl = struct.unpack('<h', bytes([data0, data1]))[0]
        accel['y'] = yAccl / 256

        # ADXL345 address, 0x53(83)
        # Read data back from 0x36(54), 2 bytes
        # Z-Axis LSB, Z-Axis MSB
        data0 = readByte(0x36)
        data1 = readByte(0x37)
        # Convert the data to 10-bits
        zAccl = struct.unpack('<h', bytes([data0, data1]))[0]
        accel['z'] = zAccl / 256

        # Output data to screen
        print ("Ax Ay Az: %.3f %.3f %.3f" % (accel['x'], accel['y'], accel['z']))
        time.sleep(0.1)
except KeyboardInterrupt:
    print("Ctrl+C Break")
    spi.close()
pwm.stop()
GPIO.cleanup()
