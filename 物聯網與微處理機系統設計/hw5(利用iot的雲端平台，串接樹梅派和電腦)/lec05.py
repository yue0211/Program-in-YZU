import requests
import random
import time
import RPi.GPIO as GPIO

ENDPOINT = "things.ubidots.com"
DEVICE_LABEL = "weather-station"
VARIABLE_LABEL = "led"
TOKEN = "BBFF-ZWASr1Yu4iSwu7PdxbA8Wsiw7ib9C0" # replace with your TOKEN
DELAY = 1  # Delay in seconds
GPIO.setmode(GPIO.BOARD)
BTN_PIN = 11
WAIT_TIME = 0.2
GPIO.setup(BTN_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
previousStatus = None
previousTime = time.time()
currentTime = None
count = 0
number = {0,1}
def ButtonPressed():
    global count
    count = (count + 1) % 2
def main(dir):
    # Simulates sensor values
    #sensor_value = random.random() * 100
    ButtonPressed()
    # Builds Payload and topíc
    payload = {VARIABLE_LABEL: count}

    # Sends data
    post_var(payload)
GPIO.add_event_detect(BTN_PIN, GPIO.FALLING, main, 100)

def post_var(payload, url=ENDPOINT, device=DEVICE_LABEL, token=TOKEN):
    try:
        url = "http://{}/api/v1.6/devices/{}".format(url, device)
        headers = {"X-Auth-Token": token, "Content-Type": "application/json"}

        attempts = 0
        status_code = 400

        while status_code >= 400 and attempts < 5:
            print("[INFO] Sending data, attempt number: {}".format(attempts))
            req = requests.post(url=url, headers=headers,
                                json=payload)
            status_code = req.status_code
            attempts += 1
            time.sleep(1)

        print("[INFO] Results:")
        print(req.text)
    except Exception as e:
        print("[ERROR] Error posting, details: {}".format(e))

'''def button():
    input = GPIO.input(BTN_PIN)
    currentTime = time.time()
    if input == GPIO.LOW and previousStatus == GPIO.HIGH and (currentTime - previousTime) > WAIT_TIME:
        previousTime = currentTime
    
    #print("Button pressed @", time.ctime())
    previousStatus = input
'''


if __name__ == "__main__":
    while True:
#        main()
        time.sleep(DELAY)
