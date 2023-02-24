import discord
import json 
import os
from discord.ext import commands
from discord_slash import SlashContext,SlashCommand
intents = discord.Intents.all()


with open('setting.json',mode='r',encoding='utf-8') as inFile: 
    data=json.load(inFile)


bot = commands.Bot(command_prefix="/",intents=intents)
slash = SlashCommand(bot,sync_commands=True)

for fileName in os.listdir("./commands"): 
    if fileName.endswith(".py"):  
       bot.load_extension(f'commands.{fileName[:-3]}') 


@bot.event 
async def on_ready():
    print(">>>Bot is online<<<")

#load
@bot.command()  
async def load(ctx,extension): 
    bot.load_extension(f'commands.{extension}')
    await ctx.send(f'Loaded {extension} done.')

#unload
@bot.command()
async def unload(ctx,extension): 
    bot.unload_extension(f'commands.{extension}')
    await ctx.send(f'Un - Loaded {extension} done.') 


#reload
@bot.command() 
async def reload(ctx,extension): 
    bot.reload_extension(f'commands.{extension}')
    await ctx.send(f'Re - Loaded {extension} done.') 


if __name__=="__main__":  
    bot.run(data["Token"])

