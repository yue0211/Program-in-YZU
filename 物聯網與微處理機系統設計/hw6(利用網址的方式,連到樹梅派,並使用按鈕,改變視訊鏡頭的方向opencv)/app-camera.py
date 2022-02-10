from flask import Flask, render_template, Response
from camera_pi import Camera
import RPi.GPIO as GPIO

count = 0

def ButtonPressed(btn):
    global count
    count = (count + 1) % 8


GPIO.setmode(GPIO.BOARD)
BTN_PIN = 11
GPIO.setup(BTN_PIN,GPIO.IN,pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(BTN_PIN, GPIO.FALLING, ButtonPressed, 200)

app = Flask(__name__)

def gen(camera):
    global count
    while True:
        frame = camera.get_frame(count)
        yield (b'--frame\r\n'b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')
    


@app.route('/')
def index():
    return Response(gen(Camera()), mimetype='multipart/x-mixed-replace; boundary=frame')



if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8000, debug=True)
