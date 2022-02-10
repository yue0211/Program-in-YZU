import speech_recognition as sr
from gtts import gTTS
import os
import apa102
import time
LED_NUM = 3
leds = apa102.APA102(num_led=3)
colors = [[255,0,0],[0,255,0],[0,0,255]] # LED0: R, LED1: G, LED2: B
#obtain audio from the microphone
r=sr.Recognizer()

# recognize speech using Google Speech Recognition
try:
    while True:
        with sr.Microphone() as source:
            print("Please wait. Calibrating microphone...")
        #listen for 1 seconds and create the ambient noise energy level
            r.adjust_for_ambient_noise(source, duration=1)
            print("Say something!")
            audio=r.listen(source)

        text1 = r.recognize_google(audio, language='zh-TW')
        print("Google Speech Recognition thinks you said:",text1)
        if text1=="開燈":
            leds.set_pixel(1, colors[1][0], colors[1][1], colors[1][2], 10)
            leds.show()
            time.sleep(1)
            tts = gTTS(text="燈已開啟", lang='zh-TW')
            tts.save('hello_tw.mp3')
            os.system('omxplayer -o local -p hello_tw.mp3 > /dev/null 2>&1')
        elif text1=="關燈":
            leds.clear_strip()
            time.sleep(1)
            tts = gTTS(text="燈已關閉", lang='zh-TW')
            tts.save('hello_tw.mp3')
            os.system('omxplayer -o local -p hello_tw.mp3 > /dev/null 2>&1')
#except sr.UnknownValueError:
#    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("No response from Google Speech Recognition service: {0}".format(e))
#except sr.UnknownValueError:
#    print("Google Speech Recognition could not understand audio")
#except sr.RequestError as e:
#    print("No response from Google Speech Recognition service: {0}".format(e))
finally:
    leds.clear_strip()
    leds.cleanup()
    

