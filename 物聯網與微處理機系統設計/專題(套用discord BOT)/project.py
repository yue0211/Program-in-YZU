import speech_recognition as sr
from gtts import gTTS
import os
import sys
import time
import psycopg2
import cv2
import numpy as np
from PIL import Image
from RepeatedTimer import RepeatedTimer
import requests
import RPi.GPIO as GPIO
import Adafruit_DHT 
import readchar
from distutils.log import set_verbosity
import smtplib
from urllib import response
import requests
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from random import randint

chara_list  = ["ayame", "azki", "koyori", "meru", "miko", "nanora", "nene", "ninnja", "peko", "pon", "rushia", "senchou", "sora", "suisei", "watame", "yamada"]
color_list1 = ["#8E8E8E", "#FF00FF", "#FFC1E0", "#FFC552", "#FF7070", "#FF44FF", "#FFA51F", "#7AFFE4", "#B8CEFF", "#CB5252", "#42FFEF", "#DD2727", "#9B99FF", "#46A3FF", "#F7F259", "#6c48a8"]
color_list2 = ["#750000", "#4DFFFF", "#4DFFFF", "#EA0000", "#A9C700", "#A5C0CF", "#27C200", "#FFE570", "#FFB8B8", "	#272727", "#F83F35", "#F6DA60", "#FF0080", "#FFD747", "#fcafb2", "#fdc569"]

text_input = False
ENDPOINT = "things.ubidots.com"
DEVICE_LABEL = "car-station"
VARIABLE_LABEL = "status"
VARIABLE_LABEL2 = "direction"
VARIABLE_LABEL3 = "cartime"
TOKEN = "BBFF-ZWASr1Yu4iSwu7PdxbA8Wsiw7ib9C0"  # replace with your TOKEN
Motor_R1_Pin = 16
Motor_R2_Pin = 18
Motor_L1_Pin = 11
Motor_L2_Pin = 13
t = 0.5

BUZZ_PIN = 22
GPIO.setmode(GPIO.BOARD)

GPIO.setup(Motor_R1_Pin, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(Motor_R2_Pin, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(Motor_L1_Pin, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(Motor_L2_Pin, GPIO.OUT, initial=GPIO.LOW)


GPIO.setup(BUZZ_PIN, GPIO.OUT)
pwm = GPIO.PWM(BUZZ_PIN, 256)
pwm.start(0)



def stop():
    GPIO.output(Motor_R1_Pin, False)
    GPIO.output(Motor_R2_Pin, False)
    GPIO.output(Motor_L1_Pin, False)
    GPIO.output(Motor_L2_Pin, False)

def forward():
    GPIO.output(Motor_R1_Pin, True)
    GPIO.output(Motor_R2_Pin, False)
    GPIO.output(Motor_L1_Pin, True)
    GPIO.output(Motor_L2_Pin, False)
    time.sleep(t)
    stop()

def backward():
    GPIO.output(Motor_R1_Pin, False)
    GPIO.output(Motor_R2_Pin, True)
    GPIO.output(Motor_L1_Pin, False)
    GPIO.output(Motor_L2_Pin, True)
    time.sleep(t)
    stop()

def turnRight():
    GPIO.output(Motor_R1_Pin, False)
    GPIO.output(Motor_R2_Pin, False)
    GPIO.output(Motor_L1_Pin, True)
    GPIO.output(Motor_L2_Pin, False)
    time.sleep(t)
    stop()

def turnLeft():
    GPIO.output(Motor_R1_Pin, True)
    GPIO.output(Motor_R2_Pin, False)
    GPIO.output(Motor_L1_Pin, False)
    GPIO.output(Motor_L2_Pin, False)
    time.sleep(t)
    stop()

def getAllAccount():
    postgres_select_query = f"""SELECT * FROM account"""
    cursor.execute(postgres_select_query)
    return cursor.fetchall()

def calculate(image1, image2):
    hist1 = cv2.calcHist([image1], [0], None, [256], [0.0, 255.0])
    hist2 = cv2.calcHist([image2], [0], None, [256], [0.0, 255.0])
    degree = 0
    for i in range(len(hist1)):
        if hist1[i] != hist2[i]:
            degree = degree + \
                (1 - abs(hist1[i] - hist2[i]) / max(hist1[i], hist2[i]))
        else:
            degree = degree + 1
    degree = degree / len(hist1)
    return degree

def classify_hist_with_split(image1, image2, size=(256, 256)):
    image1 = cv2.resize(image1, size)
    image2 = cv2.resize(image2, size)
    sub_image1 = cv2.split(image1)
    sub_image2 = cv2.split(image2)
    sub_data = 0
    for im1, im2 in zip(sub_image1, sub_image2):
        sub_data += calculate(im1, im2)
    sub_data = sub_data / 3
    return round(sub_data[0], 3)

def voice(text="文字", voice_file="音檔名"):
    tts = gTTS(text=text, lang='zh-TW')
    tts.save('{}.mp3'.format(voice_file))
    os.system('omxplayer -o local -p {}.mp3 > /dev/null 2>&1'.format(voice_file))

def input_data(creat_mode=0, resend_mode=0):
    try:
        input_data.count += 1
    except:
        input_data.count = 1
    allAccount = getAllAccount()
    while True:
        os.system("clear")
        print("\n請輸入帳號 : ", end='')
        voice(text="請輸入帳號八", voice_file="input")
        account = input()
        if creat_mode == 1:
            if account in [i[0] for i in allAccount]:
                print("帳號已存在 請重新輸入")
                voice(text="帳號已存在", voice_file="input")
                continue
        if creat_mode == 0:
            if account not in [i[0] for i in allAccount]:
                print("帳號不存在 請重新輸入")
                voice(text="帳號不存在", voice_file="input")
                continue
        print("請輸入密碼 : ", end='')
        voice(text="請輸入密碼八", voice_file="input")
        password = input()
        print("請確認密碼 : ", end='')
        voice(text="請確認密碼八", voice_file="input")
        confirm_password = input()
        if password == confirm_password:
            print("已確認\n ")
            voice(text="已確認喔", voice_file="confirm")
            if creat_mode == 0:
                apCorrect = False
                allAccount = getAllAccount()
                for acc in allAccount:
                    if account == acc[0] and password == acc[1]:
                        apCorrect = True
                        break
                if not apCorrect:
                    print("密碼錯誤 請重新輸入")
                    voice(text="密碼錯誤", voice_file="input")
                    continue
            break
        else:
            print("輸入錯誤 請重新輸入帳號密碼")
            voice(text="請重新輸入帳號密碼八", voice_file="error")
            if resend_mode == 1:
                return None, None

    if resend_mode == 1:
        return account, password
    camera = cv2.VideoCapture(0, cv2.CAP_V4L)
    camera.set(4, 720)  # horizontal pixels
    camera.set(3, 1080)  # vertical pixels
    ok = False
    while not ok:
        os.system("clear")
        print("\n\
        請將證件正面對準鏡頭左上方\n\
        盡可能地塞滿畫面\n\
        對準時請按鍵盤空白建")
        voice(text="請將證件正面對準鏡頭左上方優", voice_file="none")
        voice(text="盡可能地塞滿畫面優", voice_file="none")
        voice(text="對準時請按鍵盤空白建", voice_file="none")
        while (True):
            ok2 = False
            ret, frame = camera.read()
            cv2.imshow('frame',frame)
            if cv2.waitKey(1) == 32:
                cv2.imwrite("test.png", frame)
                img = cv2.imread("test.png")
                cv2.imshow('確認畫面', img)
                print("請按鍵確認畫面是否正確 : y(確認)/n(重新拍攝))")
                voice(text="請按鍵確認畫面是否正確八", voice_file="confirm")
                while True:
                    key = cv2.waitKey(0)
                    if key == 89 or key == 121:
                        os.system("clear")
                        # print(img)
                        # time.sleep(60)
                        print("\n已確認")
                        voice(text="已確認了", voice_file="confirm")
                        ok = True
                        camera.release()#+
                        cv2.destroyAllWindows()
                        break
                    elif key == 78 or key == 110:
                        os.system("clear")
                        print("\n重新拍攝")
                        voice(text="重新拍攝八", voice_file="confirm")
                        cv2.destroyAllWindows()
                        break
                ok2 = True
            if ok2:
                break
    camera.release()#+
    return account, password

def creat_account():
    account, password = input_data(creat_mode=1)
    # 將值丟入資料庫
    with open('test.png', 'rb') as f:
        image = f.read()
    record = (account, password,psycopg2.Binary(image))
    table_columns = '(account, password,image)'
    postgres_insert_query = f"""INSERT INTO account {table_columns} VALUES (%s, %s,%s);"""
    cursor.execute(postgres_insert_query, record)
    DatabaseConnect.commit()
    os.system("clear")
    print("\n帳戶創建成功\n")
    voice(text="帳戶創建成功了", voice_file="success")
    print("帳號 : {}".format(account))
    print("密碼 : {}".format(password))
    if send_mail(resend=False):
        print("\n三秒後返回主選單喔")
        time.sleep(3)

def check(account, password):
    allAccount = getAllAccount()
    apCorrect = False
    for acc in allAccount:
        if account == acc[0] and password == acc[1]:
            apCorrect = True
            break
    if not apCorrect:
        return False
    with open("correct.png", "wb") as f:
        f.write(acc[2])

    img_test = cv2.imread("test.png")
    img_correct = cv2.imread("correct.png")
    value = classify_hist_with_split(img_test, img_correct)
    print("與創建帳號時使用之證件照相似度(0~1) :", value)
    if value >= 0.67:
        return True
    print("\n與創建帳號時使用之證件照差異過大\n")
    voice(text="證件不符", voice_file="success")
    time.sleep(3)
    return False

def post_var(payload, url=ENDPOINT, device=DEVICE_LABEL, token=TOKEN):
    try:
        url = "http://{}/api/v1.6/devices/{}".format(url, device)
        headers = {"X-Auth-Token": token, "Content-Type": "application/json"}

        attempts = 0
        status_code = 400

        while status_code >= 400 and attempts < 5:
            #print("[INFO] Sending data, attempt number: {}".format(attempts))
            req = requests.post(url=url, headers=headers,
                                json=payload)
            status_code = req.status_code
            attempts += 1
            time.sleep(1)

        #print("[INFO] Results:")
        #print(req.text)
    except Exception as e:
        #pass
        print("[ERROR] Error posting, details: {}".format(e))

def get_var(url=ENDPOINT, device=DEVICE_LABEL, variable=VARIABLE_LABEL2,token=TOKEN):
        try:
            URL = "http://{}/api/v1.6/devices/{}/{}/lv".format(url, device, variable)
            headers = {"X-Auth-Token": token, "Content-Type": "application/json"}
            attempts = 0
            status_code = 400
            while status_code >= 400 and attempts < 5:
                #print("[INFO] Retrieving data, attempt number: {}".format(attempts))
                req = requests.get(url=URL, headers=headers)
                status_code = req.status_code
                attempts += 1
                time.sleep(1)
                #print("[INFO] Results:")
                return int(float(req.text))

        except Exception as e:
            #pass
            print("[ERROR] Error posting, details: {}".format(e))

def car_run(num:int):
    if num == 1:
        forward()
    elif num == 2:
        backward()
    elif num == 3:
        turnLeft()
    elif num == 4:
        turnRight()
    elif num == 5:
        pwm.ChangeDutyCycle(50)
        time.sleep(1)
        pwm.ChangeDutyCycle(0)

def link():
    post_var(payload = {VARIABLE_LABEL : 1})#link.status
    os.system("clear")
    print("\n登入成功!!")
    voice(text="登入成功", voice_file="log_in")
    time.sleep(2)
    instList = ['', "前進", "後退", "左轉", "右轉", "喇叭"]

    while True:
        os.system("clear")
        print("\n欲登出請在discord輸入指令")
        instNum = get_var()
        tm = get_var(variable=VARIABLE_LABEL3)
        #print(instNum, type(instNum))
        if instNum == -1:
            GPIO.cleanup()#+
            pwm.stop()
            break
        if instNum > 0:
            if instNum >= 1 and instNum <= 5:
                rt = RepeatedTimer(1, car_run, instNum)
            else:
                pass
            try:
                print(instList[instNum], "開始執行...")
                time.sleep(tm-1)
                post_var(payload = {VARIABLE_LABEL2 : 0})#instNum
                print(instList[instNum], "執行結束")
                time.sleep(1)
            finally:
                rt.stop()
    post_var(payload = {VARIABLE_LABEL : 0})#link.status
    post_var(payload = {VARIABLE_LABEL2 : 0})#instNum

    os.system("clear")
    print('\n登出成功!!')
    voice(text="登出成功", voice_file="log_out")
    time.sleep(2)

def log_in(resend_mode=0):
    input_data.count = 0
    while True:
        os.system("clear")
        if input_data.count == 3:
            if resend_mode == 1:
                return "exit"
            print('\n輸入次數已達三次 三秒後返回主選單')
            voice(text="三秒後返回主選單喔", voice_file="return")
            time.sleep(3)
            return "exit"
        account, password = input_data(creat_mode=0, resend_mode=resend_mode)

        if resend_mode == 1:
            if account == None and password == None:
                continue
            else:
                return
        if check(account, password) == True:
            break
        
        print("輸入錯誤 請重新輸入")
        voice(text="請重新輸入八", voice_file="error")
        time.sleep(1)
    
    print("登入成功")
    voice(text="登入成功優", voice_file="success")
    time.sleep(1)
    os.system("clear")
    link()

def log_in_account():
    try:
        while True:
            os.system("clear")
            if text_input:
                print("\n\
                請輸入欲執行事項\n\
                1.登入帳戶\n\
                2.返回主選單\n")
                voice(text="請輸入欲執行事項", voice_file="confirm")
                choice1_t = input()
                if choice1_t == "一" or choice1_t == "登入帳戶" or choice1_t == "1":
                    if log_in() == "exit":
                        return
                elif choice1_t == "2" or choice1_t == "返回主選單" or choice1_t == "二":
                    return
                else:
                    print("輸入錯誤 請重新輸入\n")
                    voice(text="輸入錯誤喔", voice_file="error")

            else:
                with sr.Microphone() as source:
                    print("\n\
                    請輸入欲執行事項\n\
                    1.登入帳戶\n\
                    2.返回主選單\n")
                    choice1 = r.listen(source)
                    choice1_t = r.recognize_google(choice1, language='zh-TW')
                    print(choice1_t)
                    if choice1_t == "一" or choice1_t == "登入帳戶" or choice1_t == "1":
                        if log_in() == "exit":
                            return
                    elif choice1_t == "2" or choice1_t == "返回主選單" or choice1_t == "二":
                        return
                    else:
                        print("輸入錯誤 請重新輸入\n")
                        voice(text="輸入錯誤喔", voice_file="error")
    except sr.RequestError as e:
        print("No response from Google Speech Recognition service: {0}".format(e))
    except sr.UnknownValueError:
       print("Google Speech Recognition could not understand audio")
    except sr.RequestError as e:
       print("No response from Google Speech Recognition service: {0}".format(e))
    except:
        pass

def send_mail(resend=False):
    if resend:
        if log_in(resend_mode=1) == "exit":
            return 

    msg = MIMEMultipart()
    msg["From"] = "asx5566123@gmail.com"
    msg["Subject"] = "樹梅派自走車會員認證信"
    
    os.system("clear")
    print("\n請在鍵盤輸入電子郵件帳號 : ", end="")
    voice(text="請在鍵盤輸入電子郵件帳號八", voice_file="input_mailAdd")
    ok = False
    while not ok:
        msg["To"] = input()
        print("請確認電子郵件帳號是否正確 : y(確認)/n(重新輸入))")
        voice(text="請確認電子郵件帳號是否正確八", voice_file="confirm")
        while True:
            key = input()
            if key == "y" or key == "Y":
                os.system("clear")
                print("\n已確認電子郵件帳號")
                voice(text="已確認電子郵件帳號", voice_file="confirm")
                ok = True
                break
            elif key == "n" or key == "N":
                os.system("clear")
                print("\n請重新輸入電子郵件帳號 : ", end="")
                voice(text="請重新輸入電子郵件帳號", voice_file="confirm")
                break
            else:
                print("\n輸入錯誤  請確認電子郵件帳號是否正確 : y(確認)/n(重新輸入))")
                voice(text="請確認電子郵件帳號是否正確八", voice_file="confirm")

    rand_num = randint(0, 15)

    #Attach Text
    msgText = MIMEText("<h1 style='color:" + color_list1[rand_num] + ";'>帳號已註冊成功</h1>"+"<p style='color:" + color_list2[rand_num] + ";'><strong style='font-size:15px;'>掃描附件的QR Code，即可加入discord群，與大家一起玩自走車</strong></p>", 'html')
    msg.attach(msgText)

    #Attach Image 
    fp = open('{}.png'.format(chara_list[rand_num]), 'rb') #Read image 
    msgImage = MIMEImage(fp.read())
    fp.close()
    msgImage.add_header('Content-ID', '<image1>')
    msg.attach(msgImage)

    # 到網路上搜尋 gmail smtp server 或是 yahoo smtp server
    server = smtplib.SMTP_SSL("smtp.gmail.com",465)
    server.login("asx5566123@gmail.com","asx5566789")
    response = requests.get("https://isitarealemail.com/api/email/validate", params = {'email': msg["To"]})
    status = response.json()['status']

    if status =="valid":
        server.send_message(msg)
        print("\n郵件傳送成功")
        voice(text="郵件傳送成功", voice_file="sec")
        return True
    else:
        print("\n郵件地址錯誤  傳送失敗")
        print("\n請嘗試重新發送群組邀請郵件")
        print('\n三秒後返回主選單')
        voice(text="三秒後返回主選單喔", voice_file="return")
        time.sleep(3)
        return False

if __name__ == '__main__':
    r = sr.Recognizer()
    DatabaseConnect = psycopg2.connect(database="dfdobug1c771t2",\
                                       user="cbynnhmmgimwaq",\
                                       password="3d7fc902098189e0744a6ec5a9c84904af2cd1607c297488d51fda4654c6c518",\
                                       host="ec2-52-2-118-38.compute-1.amazonaws.com",\
                                       port="5432")
    cursor = DatabaseConnect.cursor()
    os.system("clear")
    print("\n請選擇是否使用鍵盤輸入代替語音輸入 : y(使用鍵盤輸入)/n(使用語音輸入))")
    voice(text="請選擇是否使用鍵盤輸入八", voice_file="confirm")
    while True:
        choice1_t = input()
        if choice1_t == 'y' or choice1_t == 'Y':
            print("\n已使用鍵盤輸入")
            voice(text="已使用鍵盤輸入", voice_file="confirm")
            text_input = True
            break
        elif choice1_t == 'n' or choice1_t == 'N':
            print("\n已使用語音輸入")
            voice(text="已使用語音輸入", voice_file="confirm")
            break
    while True:
        try:
            os.system("clear")
            if text_input:
                print("\n\
                請輸入欲執行事項\n\
                1.創建帳戶\n\
                2.登入帳戶\n\
                3.重新發送群組邀請郵件\n\
                4.結束程式\n")
                voice(text="請輸入欲執行事項", voice_file="confirm")
                choice1_t = input()
                if choice1_t == "1" or choice1_t == "創建帳戶" or choice1_t == "一":
                    creat_account()
                elif choice1_t == "2" or choice1_t == "登入帳戶" or choice1_t == "二":
                    log_in_account()
                elif choice1_t == "3" or choice1_t == "重新發送群組邀請郵件" or choice1_t == "三":
                    send_mail(resend=True)
                elif choice1_t == "4" or choice1_t == "結束程式" or choice1_t == "四":
                    os.system("clear")
                    #sys.exit(0)
                    break
                else:
                    print("輸入錯誤 請重新輸入\n")
                    voice(text="輸入錯誤喔", voice_file="error")
            else:
                with sr.Microphone() as source:
                    r.adjust_for_ambient_noise(source, duration=1)
                    print("\n\
                    請輸入欲執行事項\n\
                    1.創建帳戶\n\
                    2.登入帳戶\n\
                    3.重新發送群組邀請郵件\n\
                    4.結束程式\n")
                    choice1 = r.listen(source)
                    choice1_t = r.recognize_google(choice1, language='zh-TW')
                    print(choice1_t)
                    if choice1_t == "一" or choice1_t == "創建帳戶" or choice1_t == "1":
                        creat_account()
                    elif choice1_t == "2" or choice1_t == "登入帳戶" or choice1_t == "二":
                        log_in_account()
                    elif choice1_t == "3" or choice1_t == "重新發送群組邀請郵件" or choice1_t == "三":
                        send_mail(resend=True)
                    elif choice1_t == "4" or choice1_t == "結束程式" or choice1_t == "四":
                        os.system("clear")
                        #sys.exit(0)
                        break
                    else:
                        print("輸入錯誤 請重新輸入\n")
                        voice(text="輸入錯誤喔", voice_file="error")
        except sr.RequestError as e:
            print("No response from Google Speech Recognition service: {0}".format(e))
        except sr.UnknownValueError:
            print("Google Speech Recognition could not understand audio")
        except sr.RequestError as e:
            print("No response from Google Speech Recognition service: {0}".format(e))
        except:
            try:
                GPIO.cleanup()
                post_var(payload = {VARIABLE_LABEL : 0})#link.status
                post_var(payload = {VARIABLE_LABEL2 : 0})#instNum
            except:
                pass