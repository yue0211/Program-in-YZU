import discord,random,json,pytz
import datetime 
from discord.ext import commands
from core.classes import  Cog_Extension 

with open('setting.json',mode='r',encoding='utf-8') as inFile: 
    data=json.load(inFile)


class Main(Cog_Extension):


    @commands.command(name="clean", help="用於刪除訊息(參數:訊息的數量)")  # 清除資料
    async def clean(self,ctx,num:int): 
        await ctx.channel.purge(limit=num+1)

    @commands.command(name="who", help="查看群組成員的個人資訊(參數:成員名稱)") # 看個人身份
    async def who(self,ctx,name:str):
        for member in ctx.guild.members:
            if  member.name==name or member.nick==name:
                embed=discord.Embed(title="人頭", description="個人資訊", color=0xa85dd0,timestamp=datetime.datetime.now(pytz.timezone('Asia/Taipei')))
                embed.set_author(name="幹幹的", icon_url="https://imgur.dcard.tw/tn729YT.gif")
                embed.set_thumbnail(url=member.avatar_url)
                embed.add_field(name="名稱：", value=f"{member}", inline=False)
                embed.add_field(name="目前的狀態：", value=member.status, inline=False)
                await ctx.channel.send(embed=embed)


    @commands.command(name="em", help="用於顯示群規(參數:無)")
    async def em(self,ctx): # google 搜尋 discord embed 可以生成程式碼 ,time 要自己另外設定
        embed=discord.Embed(title="群規", description="非常重要", color=0xa85dd0,timestamp=datetime.datetime.now())
        embed.set_author(name="管理員", icon_url="https://imgur.dcard.tw/tn729YT.gif")
        embed.set_thumbnail(url="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQJpozH7Fz41uprarazDZUrs7_Wu06uGkUvRw&usqp=CAU")
        embed.add_field(name="1. 禁止引戰、謾罵、洗頻", value="我們不希望交流環境充滿烏煙瘴氣及負能量", inline=False)
        embed.add_field(name="2. 減少不雅用詞", value="我們希望塑造一個充滿和諧與素質的交流環境，請盡可能減少不雅用詞", inline=False)
        embed.add_field(name="3. 尊重與遵從管理員指示", value="也許社群會有一些額外的標準流程或規定，但任何時候請遵從管理員的指示與決定", inline=False)
        embed.add_field(name="4. 保持頻道主題相符話題", value="這有助於頻道整潔、話題的延續、歷史查詢", inline=False)
        embed.add_field(name="5. 不要用私訊問問題，除非問題涉及隱私", value="伺服器裡已經有問題詢問區，沒有特殊問題下私訊是很擾人的行為", inline=False)
        await ctx.send(embed=embed)


    @commands.command(name="atid", help="用於產生Discord id(參數:無)") # 隨機產生id
    async def atid(self,ctx):
        box=""
        for i in range(4):
            box+=str(random.randrange(10))
        await ctx.channel.send(box)

        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()
        id = self.all[0][0]
        temp="'"+box+"'"
        postgres_update_query = f"""UPDATE discord_yue SET id = {temp} WHERE id =%s """
        self.cursor.execute(postgres_update_query, (id,))
        self.conn.commit()
        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()

    @commands.command(name="check", help="用於確認驗證碼(參數:驗證碼)") # 確認驗證碼
    async def check(self,ctx,code):
        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()

        if str(self.all[0][1])!=code:
           await ctx.channel.send("驗證碼錯誤")
        else:
           await ctx.channel.send(f"驗證碼正確,恭喜 {ctx.author.mention} 升級成高級會員")
           role = discord.utils.get(ctx.author.guild.roles,id=(int(data["YueHighMember"]))) #高級會員身份
           await ctx.author.add_roles(role)
           role = discord.utils.get(ctx.author.guild.roles,id=(int(data["YueNormalMember"]))) #普通會員身份
           await ctx.author.remove_roles(role)


def setup(bot): #運行bot時,會呼叫 setup => 註冊
    bot.add_cog(Main(bot))

