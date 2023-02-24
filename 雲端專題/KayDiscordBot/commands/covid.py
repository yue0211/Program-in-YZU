from time import sleep
import discord,random,json,pytz,requests,os
import datetime 
from discord.ext import commands
from core.classes import  Cog_Extension 
from discord_slash import SlashContext,SlashCommand,cog_ext

with open('setting.json',mode='r',encoding='utf-8') as inFile: 
    data=json.load(inFile)


class Covid(Cog_Extension):


    #@commands.command(name="drugstore", help="用於查詢快篩藥局資訊(參數:地址,ex:xx市xx區)")  # 清除資料
    @cog_ext.cog_slash(name="drugstore", description="用於查詢快篩藥局資訊(參數:地址,ex:xx市xx區)")
    async def _drugstore(self,ctx,address): 

        jsonUrl = "https://raw.githubusercontent.com/SiongSng/Rapid-Antigen-Test-Taiwan-Map/data/data/antigen.json" #快篩藥局資訊

        jsonHeaders = { "Content-Type": "application/json" ,"User-Agent": "Mozilla/5.0 (X11; Linux aarch64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.188 Safari/537.36 CrKey/1.54.250320"}
        
        jsonResponse = requests.get(url=jsonUrl, headers=jsonHeaders)

        information = jsonResponse.json() #解析json檔案,讓data變成disctionary
        
        save_path = "/home/ubuntu/YueDiscordBot/commands/"
        
        completeName = os.path.join(save_path,"store.txt") 

        all_store = []

        with open(completeName, "w",encoding="utf-8") as file:

            
            

            for value in information.values():
                if address in value["address"]:
                    all_store.append("{} {}".format(value["address"],value["name"]))
                    
            for name in all_store:
                file.write(name+"\n")

        if len(all_store)!=0:
            await ctx.send("此為你的檔案:", file=discord.File(completeName, "store.txt"))
        else:
            await ctx.send("查無相關資訊")

        os.remove(completeName)


def setup(bot): #運行bot時,會呼叫 setup => 註冊
    bot.add_cog(Covid(bot))

