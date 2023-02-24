
mapping = input("mapping: ").split(",") # 輸入的字串以逗號分隔

dictionary={}

for x in mapping:
    temp = x.split(":")
    dictionary.update({temp[0]:temp[1]}) # 在字典 新增 key 和 value

respotory = []

with open("symbols.txt","r") as inFile:
    respotory = inFile.read()

sign =  respotory.split("\n")  
sign.reverse()

for i in sign:
    for j in i:
        if j in dictionary.keys():
            print(dictionary[j],end="")
    print("")


# 可利用 查看變數的 type 來 debug