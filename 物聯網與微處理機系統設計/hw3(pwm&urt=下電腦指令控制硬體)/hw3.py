import time
import serial
import pigpio
import RPi.GPIO as GPIO

PWM_PIN = 18 # BCM Number
pi = pigpio.pi()
pi.set_PWM_frequency(PWM_PIN, 100)
pi.set_PWM_range(PWM_PIN, 255)
pi.set_PWM_dutycycle(PWM_PIN, 0)

BUZZ_PIN = 16#bcm
pitch = [262, 294, 330, 349, 392, 440, 493]
GPIO.setmode(GPIO.BOARD)
GPIO.setup(BUZZ_PIN, GPIO.OUT)
pwm = GPIO.PWM(BUZZ_PIN, pitch[0])
pwm.start(0)
ser = serial.Serial('/dev/ttyAMA1',baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize = serial.EIGHTBITS
                   )
try:
    while True:
        data = ser.readline()
        command = data.decode("utf-8").strip()
        pi.set_PWM_dutycycle(PWM_PIN, 0)
        if "play" in command:
            test = command[5:].split(",")
            for x in test:
                if  x=="c":
                    print("c")
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[0])
                    time.sleep(2)
                elif x=="d":
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[1])
                    time.sleep(2)
                elif x=="e":
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[2])
                    time.sleep(2)
                elif x=="f":
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[3])
                    time.sleep(2)
                elif x=="g":
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[4])
                    time.sleep(2)
                elif x=="a":
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[5])
                    time.sleep(2)
                elif x=="b":
                    pwm.ChangeDutyCycle(50)
                    pwm.ChangeFrequency(pitch[6])
                    time.sleep(2)
            pwm.ChangeDutyCycle(0)
        elif 'set' in command:
            brightness = command[4:]
            if not brightness.isdigit() or int(brightness) > 100 or int(brightness) < 0:
                continue
            pi.set_PWM_dutycycle(PWM_PIN, 255*int(brightness)/100)
            time.sleep(0.05)
        
except KeyboardInterrupt:
    print("execept")

ser.close()
pi.set_PWM_dutycycle(PWM_PIN, 0)
pi.stop()
pwm.stop()
GPIO.cleanup()