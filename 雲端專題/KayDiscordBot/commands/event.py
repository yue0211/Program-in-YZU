import discord
import json 
from discord.ext import commands
from core.classes import  Cog_Extension 


with open('setting.json',mode='r',encoding='utf-8') as inFile: 
    data=json.load(inFile)


class Event(Cog_Extension):
    @commands.Cog.listener() 
    async def on_member_join(self,member):  #成員加入頻道
        if member.guild.id==(int(data["Yue"])):
            channel=self.bot.get_channel(int(data["YueEnterAndLeave"]))
            channelTwo=self.bot.get_channel(int(data["YueLevelUp"])) #升級會員資料 頻道
            await channel.send(f'{member.mention}已加入本群,如要解鎖更多頻道權限請去 {channelTwo.mention} 設定資料') 
            role = discord.utils.get(member.guild.roles,id=(int(data["YueNormalMember"]))) #普通會員身份
            await member.add_roles(role)
            await member.send(f"{member.name} 群內有許多資源,可善加利用,並遵守相關規定,謝謝配合")
        elif member.guild.id==(int(data["Rabbit"])):
            channel=self.bot.get_channel(int(data["RabbitMainRoom"]))
            await channel.send(f'{member}已加入,太草了') 
            role = discord.utils.get(member.guild.roles,id=(int(data["RabbitRoleNormalPeople"]))) 
            await member.add_roles(role)
            await member.send(f"{member.name} 程式討論區中有提供不同程式的身份組,如有需要可點按表情領取")




    @commands.Cog.listener()
    async def on_member_remove(self,member): #成員離開頻道
        if member.guild.id==(int(data["Yue"])):
            channel=self.bot.get_channel(int(data["YueEnterAndLeave"]))  
            await channel.send(f'{member}已離開本群') 
        elif member.guild.id==(int(data["Rabbit"])):
            channel=self.bot.get_channel(int(data["RabbitMainRoom"]))
            await channel.send(f'{member}已離開,哭阿') 


    @commands.Cog.listener() 
    async def on_message(self,msg):  
        if msg.guild.id==(int(data["Yue"])):
            if msg.channel.id==(int(data["YueAnime"])):
                if msg.content == "柯南": 
                    await msg.channel.send(f'下載連結: {data["柯南"]}')
                elif msg.content == "命運石之門": 
                    await msg.channel.send(f'下載連結: {data["命運石之門"]}')
                elif msg.content == "中二病也想": 
                    await msg.channel.send(f'下載連結: {data["中二病也想"]}')
                elif msg.content == "我的英雄學院": 
                    await msg.channel.send(f'下載連結: {data["我的英雄學院"]}')
                elif msg.content == "瓦尼塔斯": 
                    await msg.channel.send(f'下載連結: {data["瓦尼塔斯"]}')
                elif msg.content == "我們的重製人生": 
                    await msg.channel.send(f'下載連結: {data["我們的重製人生"]}')
                elif msg.content == "死神少爺": 
                    await msg.channel.send(f'下載連結: {data["死神少爺"]}')
                elif msg.content == "現實主義勇者": 
                    await msg.channel.send(f'下載連結: {data["現實主義勇者"]}')
                elif msg.content == "關於我轉生": 
                    await msg.channel.send(f'下載連結: {data["關於我轉生"]}')
                elif msg.content == "壞人大小姐": 
                    await msg.channel.send(f'下載連結: {data["壞人大小姐"]}')
                elif msg.content == "急戰五秒": 
                    await msg.channel.send(f'下載連結: {data["急戰五秒"]}')
                elif msg.content == "小林家": 
                    await msg.channel.send(f'下載連結: {data["小林家"]}')
                elif msg.content == "桃子男孩": 
                    await msg.channel.send(f'下載連結: {data["桃子男孩"]}')
                elif msg.content == "平穩世代": 
                    await msg.channel.send(f'下載連結: {data["平穩世代"]}')
                elif msg.content == "緋紅結繫": 
                    await msg.channel.send(f'下載連結: {data["緋紅結繫"]}')
                elif msg.content == "女神宿舍": 
                    await msg.channel.send(f'下載連結: {data["女神宿舍"]}')
                elif msg.content == "不存在": 
                    await msg.channel.send(f'下載連結: {data["不存在"]}')
                elif msg.content == "海賊王": 
                    await msg.channel.send(f'下載連結: {data["海賊王"]}')
                elif msg.content == "東京復仇者": 
                    await msg.channel.send(f'下載連結: {data["東京復仇者"]}')
                elif msg.content == "奇巧計程車": 
                    await msg.channel.send(f'下載連結: {data["奇巧計程車"]}')
                elif msg.content == "魔法科高中": 
                    await msg.channel.send(f'下載連結: {data["魔法科高中"]}')
                elif msg.content == "暗黑企業": 
                    await msg.channel.send(f'下載連結: {data["暗黑企業"]}')
                elif msg.content == "伊甸星原": 
                    await msg.channel.send(f'下載連結: {data["伊甸星原"]}')
               
                

        

     # 新增反應貼圖獲取身份組
    @commands.Cog.listener()                    
    async def on_raw_reaction_add(self,payload): 
        guild=self.bot.get_guild(payload.guild_id)
        if guild.id == (int(data["Yue"])):
            if payload.message_id == (int(data["YueRoleMessage"])):
                if str(payload.emoji)==data["YueProgram"]:
                    role=guild.get_role((int(data["YueRoleProgram"])))
                    await payload.member.add_roles(role)
                    await payload.member.send(f"你取得了 {role}身份組!!")
                elif str(payload.emoji)==data["YuePeko"]:
                    role=guild.get_role((int(data["YueRolePeko"])))
                    await payload.member.add_roles(role)
                    await payload.member.send(f"你取得了 {role}身份組!!")
                elif str(payload.emoji)==data["YueTalesRunner"]: 
                    role=guild.get_role((int(data["YueRoleTalesRunner"]))) 
                    await payload.member.add_roles(role) 
                    await payload.member.send(f"你取得了 {role}身份組!!")
        elif guild.id == (int(data["Rabbit"])):
            if payload.message_id == (int(data["RabbitRoleMessage"])):
                if str(payload.emoji)==data["RabbitC++"]: 
                    role=guild.get_role((int(data["RabbitRoleC++"])))
                    await payload.member.add_roles(role) 
                    await payload.member.send(f"你取得了 {role}身份組!!")
                elif str(payload.emoji)==data["RabbitPython"]: 
                    role=guild.get_role((int(data["RabbitRolePython"]))) 
                    await payload.member.add_roles(role) 
                    await payload.member.send(f"你取得了 {role}身份組!!")







     # 取消反應貼圖取消身份組
    @commands.Cog.listener()                   
    async def on_raw_reaction_remove(self,payload): 
        guild=self.bot.get_guild(payload.guild_id) 
        if guild.id == (int(data["Yue"])):
            if payload.message_id == (int(data["YueRoleMessage"])):
                if str(payload.emoji)==data["YueProgram"]: 
                    role=guild.get_role((int(data["YueRoleProgram"]))) 
                    member=guild.get_member(payload.user_id)
                    await member.remove_roles(role) 
                    await member.send(f"你移除了{role}身份組!!")
                elif str(payload.emoji)==data["YuePeko"]:  
                    role=guild.get_role((int(data["YueRolePeko"]))) 
                    member=guild.get_member(payload.user_id)
                    await member.remove_roles(role) 
                    await member.send(f"你移除了{role}身份組!!")
                elif str(payload.emoji)==data["YueTalesRunner"]:  
                    role=guild.get_role((int(data["YueRoleTalesRunner"]))) 
                    member=guild.get_member(payload.user_id)
                    await member.remove_roles(role) 
                    await member.send(f"你移除了{role}身份組!!")
        elif guild.id == (int(data["Rabbit"])):
            if payload.message_id == (int(data["RabbitRoleMessage"])):
                if str(payload.emoji)== data["RabbitC++"]: 
                    role=guild.get_role((int(data["RabbitRoleC++"]))) 
                    member=guild.get_member(payload.user_id) 
                    await member.remove_roles(role)
                    await member.send(f"你移除了{role}身份組!!")
                elif str(payload.emoji)==data["RabbitPython"]:  
                    role=guild.get_role((int(data["RabbitRolePython"]))) 
                    member=guild.get_member(payload.user_id)
                    await member.remove_roles(role) 
                    await member.send(f"你移除了{role}身份組!!")





def setup(bot): #運行bot時,會呼叫 setup => 註冊 cog
    bot.add_cog(Event(bot))
