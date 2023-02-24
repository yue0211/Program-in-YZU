import discord,random,json,pytz
import datetime,os 
from discord.ext import commands
from core.classes import  Cog_Extension 
from time import sleep
from discord_slash import cog_ext,SlashContext



with open('setting.json',mode='r',encoding='utf-8') as inFile: 
    data=json.load(inFile)


class Main(Cog_Extension):


   
    @commands.command(name="clean", help="用於刪除訊息(參數:訊息的數量)")
    async def clean(self,ctx,num:int): 
        await ctx.channel.purge(limit=num+1)

    #@commands.command(name="who", help="查看群組成員的個人資訊(參數:成員名稱)") # 看個人身份
    @cog_ext.cog_slash(name="who", description="查看群組成員的個人資訊(參數:成員名稱)")
    async def _who(self,ctx,name:str):
        for member in ctx.guild.members:
            if  member.name==name or member.nick==name:
                embed=discord.Embed(title="人頭", description="個人資訊", color=0xa85dd0,timestamp=datetime.datetime.now(pytz.timezone('Asia/Taipei')))
                embed.set_author(name="幹幹的", icon_url="https://imgur.dcard.tw/tn729YT.gif")
                embed.set_thumbnail(url=member.avatar_url)
                embed.add_field(name="名稱：", value=f"{member}", inline=False)
                embed.add_field(name="目前的狀態：", value=member.status, inline=False)
                await ctx.send(embed=embed)


    #@commands.command(name="em", help="用於顯示群規(參數:無)")
    @cog_ext.cog_slash(name="em", description="用於顯示群規(參數:無)")
    async def _em(self,ctx): # google 搜尋 discord embed 可以生成程式碼 ,time 要自己另外設定
        embed=discord.Embed(title="群規", description="非常重要", color=0xa85dd0,timestamp=datetime.datetime.now())
        embed.set_author(name="管理員", icon_url="https://imgur.dcard.tw/tn729YT.gif")
        embed.set_thumbnail(url="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQJpozH7Fz41uprarazDZUrs7_Wu06uGkUvRw&usqp=CAU")
        embed.add_field(name="1. 禁止引戰、謾罵、洗頻", value="我們不希望交流環境充滿烏煙瘴氣及負能量", inline=False)
        embed.add_field(name="2. 減少不雅用詞", value="我們希望塑造一個充滿和諧與素質的交流環境，請盡可能減少不雅用詞", inline=False)
        embed.add_field(name="3. 尊重與遵從管理員指示", value="也許社群會有一些額外的標準流程或規定，但任何時候請遵從管理員的指示與決定", inline=False)
        embed.add_field(name="4. 保持頻道主題相符話題", value="這有助於頻道整潔、話題的延續、歷史查詢", inline=False)
        embed.add_field(name="5. 不要用私訊問問題，除非問題涉及隱私", value="伺服器裡已經有問題詢問區，沒有特殊問題下私訊是很擾人的行為", inline=False)
        await ctx.send(embed=embed)


    #@commands.command(name="atid", help="用於產生Discord id(參數:無)") # 隨機產生id
    @cog_ext.cog_slash(name="atid", description="用於產生Discord id(參數:無)")
    async def _atid(self,ctx):
        box=""
        for i in range(4):
            box+=str(random.randrange(10))
        await ctx.send(box)

        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()
        id = self.all[0][0]
        temp="'"+box+"'"
        postgres_update_query = f"""UPDATE discord_yue SET id = {temp} WHERE id =%s """
        self.cursor.execute(postgres_update_query, (id,))
        self.conn.commit()
        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()

    #@commands.command(name="check", help="用於確認驗證碼(參數:驗證碼)") # 確認驗證碼
    @cog_ext.cog_slash(name="check", description="用於確認驗證碼(參數:驗證碼)")
    async def _check(self,ctx,code):
        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()

        if str(self.all[0][1])!=code:
           await ctx.send("驗證碼錯誤")
        else:
           await ctx.send(f"驗證碼正確,恭喜 {ctx.author.mention} 升級成高級會員")
           role = discord.utils.get(ctx.author.guild.roles,id=(int(data["YueHighMember"]))) #高級會員身份
           await ctx.author.add_roles(role)
           role = discord.utils.get(ctx.author.guild.roles,id=(int(data["YueNormalMember"]))) #普通會員身份
           await ctx.author.remove_roles(role)

   


    @cog_ext.cog_slash(name="Language", description="列出所有可以被翻譯的語言")
    async def _Language(self,ctx):
        languages = [('南非荷蘭文','af'),('阿爾巴尼亞文','sq'),('阿姆哈拉文','am'),('Arabic','ar'),('亞美尼亞人','hy'),('亞塞拜然文','az'),('孟加拉文',	'bn'),('波士尼亞文'	,'bs'),('保加利亞文','bg')
,('加泰羅尼亞語',	'ca'),('簡體中文'	,'zh'),('繁體中文'	,'zh-TW'),('克羅埃西亞文','hr'),('捷克文','cs'),('丹麥文','da'),('達里文','fa-AF'),('荷蘭文','nl'),('英文','en'),('Estonian','et')
,('波斯語','fa'),('菲律賓語 (菲律賓語)','tl'),('芬蘭文','fi'),('French','fr'),('法文 (加拿大)','fr-CA'),('喬治亞文','ka'),('德文','de'),('Greek','el'),('古吉拉特','gu'),('海地克裏奧爾','ht'),
('豪沙文','ha'),('Hebrew','he'),('北印度文','hi'),('匈牙利文','hu'),('冰島文','is'),('印尼文','id'),('愛爾蘭人','ga'),('義大利文','it'),('日文','ja'),('卡納達','kn'),('哈薩克人','kk'),('韓文','ko'),
('拉脫維亞文','lv'),('立陶宛語','lt'),('馬其頓語'	,'mk'),('馬來文',	'ms'),('馬拉雅拉姆',	'ml'),('馬爾濟斯'	,'mt'),('馬拉'	,'mr'),('Mongolian'	,'mn'),('挪威文',	'no'),('普什圖文'	,'ps'),('Polish',	'pl'),
('葡萄牙文 (巴西)'	,'pt'),('葡萄牙文 (葡萄牙)'	,'pt-PT'),('旁遮普',	'pa'),('羅馬尼亞文',	'ro'),('俄文'	,'ru'),('塞爾維亞文',	'sr'),('僧伽羅語',	'si'),('斯洛伐克文',	'sk'),
('斯洛維尼亞文',	'sl'),('索馬利亞文',	'so'),('西班牙文',	'es'),('西班牙文 (墨西哥)'	,'es-MX'),('史瓦西里文',	'sw'),('瑞典文',	'sv'),('坦米爾文'	,'ta'),('泰盧固',	'te'),('Thai'	,'th'),
('Turkish',	'tr'),('烏克蘭文',	'uk'),('烏都文',	'ur'),('烏茲別克'	,'uz'),('Vietnamese',	'vi'),('威爾斯文',	'cy')]
        
        
        save_path = "/home/ubuntu/YueDiscordBot/commands/"
        
        completeName = os.path.join(save_path,"language.json")
        
        with open(completeName,"w",encoding = "utf-8") as file:
            
            file.write("語言對照表\n\n")

            for number,language in zip(range(len(languages)),languages):
                file.write(str(number+1)+"."+language[0]+": "+language[1]+"\n")
        
        await ctx.send("語言對照檔案:",file=discord.File(completeName,"languages.txt"))

        os.remove(completeName)




    #@commands.command(name="trzh", help="將任何語言翻譯成簡體中文")
    @cog_ext.cog_slash(name="TranslateZh", description="將任何語言翻譯成簡體中文")
    async def _TranslateZh(self,ctx,*,text):
        data = {}
        data["Text"]=text
        data["SourceLanguageCode"]="auto"
        data["TargetLanguageCode"]="zh"
        with open("/home/ubuntu/YueDiscordBot/commands/translate.json","w+",encoding='utf-8') as file:
            json.dump(data,file,ensure_ascii=False)

        os.system("aws translate translate-text --region 'us-east-1' --cli-input-json file://commands/translate.json > /home/ubuntu/YueDiscordBot/commands/zhtranslated.json")
        
        with open("/home/ubuntu/YueDiscordBot/commands/zhtranslated.json",'r',encoding='utf-8') as rfile:

            self.zhtranslated = json.load(rfile)

        await ctx.send(self.zhtranslated["TranslatedText"])
    

    @cog_ext.cog_slash(name="Translate", description="將任何語言翻譯成選擇的語言")
    async def Translate(self,ctx,language,*,text):
        
        try:
            data = {}
            data["Text"]=text
            data["SourceLanguageCode"]="auto"
            data["TargetLanguageCode"]=language
            
            with open("/home/ubuntu/YueDiscordBot/commands/translate.json","w+",encoding='utf-8') as file:
                json.dump(data,file,ensure_ascii=False)
        
            os.system("aws translate translate-text --region 'us-east-1' --cli-input-json file://commands/translate.json > /home/ubuntu/YueDiscordBot/commands/zhtranslated.json")
        
            

            with open("/home/ubuntu/YueDiscordBot/commands/zhtranslated.json",'r',encoding='utf-8') as rfile:

                self.zhtranslated = json.load(rfile)

            await ctx.send(self.zhtranslated["TranslatedText"])
        
        except:

           await ctx.send("沒有該語言，請確認語言對照表")




    

    



def setup(bot): #運行bot時,會呼叫 setup => 註冊
    bot.add_cog(Main(bot))

