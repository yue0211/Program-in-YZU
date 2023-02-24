import RPi.GPIO as GPIO
import time
count = 0
def ButtonPressed(btn):
   global count
   count = (count + 1) % 3
GPIO.setmode(GPIO.BOARD)
BTN_PIN = 15
LED_PIN = 16
GPIO.setup(BTN_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.add_event_detect(BTN_PIN, GPIO.FALLING, ButtonPressed, 200)
t = [1,0.5,0.25]
try:
    while True:
        GPIO.output(LED_PIN,GPIO.HIGH)
        time.sleep(t[count])
        GPIO.output(LED_PIN,GPIO.LOW)
        time.sleep(t[count])
        print(t[count])
except KeyboardInterrupt:
    print("Exception: KeyboardInterrupt")
finally:
    GPIO.cleanup()