import requests
import time
import RPi.GPIO as GPIO

'''
global variables
'''
LED_PIN = 12
GPIO.setmode(GPIO.BOARD)
GPIO.setup(LED_PIN, GPIO.OUT)

ENDPOINT = "things.ubidots.com"
DEVICE_LABEL = "weather-station"
VARIABLE_LABEL = "led"
TOKEN = "BBFF-ZWASr1Yu4iSwu7PdxbA8Wsiw7ib9C0" # replace with your TOKEN
DELAY = 0.2  # Delay in seconds
URL = "http://{}/api/v1.6/devices/{}/{}/lv".format(ENDPOINT, DEVICE_LABEL, VARIABLE_LABEL)
HEADERS = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"}

def led(cmd):
    if cmd == 1:
        print("led on.")
        GPIO.output(LED_PIN, GPIO.HIGH)
    elif cmd == 0:
        print("led off.")
        GPIO.output(LED_PIN, GPIO.LOW)

def get_var():
    try:               
        attempts = 0
        status_code = 400
        while status_code >= 400 and attempts < 5:            
            req = requests.get(url=URL, headers=HEADERS)
            status_code = req.status_code
            attempts += 1
            time.sleep(1)        
        # print(req.text)
        led(int(float(req.text)))
    except Exception as e:
        print("[ERROR] Error posting, details: {}".format(e))

if __name__ == "__main__":
    try:
        while True:
            get_var()
            time.sleep(DELAY)
    except KeyboardInterrupt:
        print("Exception: KeyboardInterrupt")
    finally:
        GPIO.cleanup()
    
