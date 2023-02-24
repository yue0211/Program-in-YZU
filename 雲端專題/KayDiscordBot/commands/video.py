import discord
from discord.ext import commands
from core.classes import  Cog_Extension
from youtube_dl import YoutubeDL
import bitly_api
from discord_slash import SlashContext,SlashCommand,cog_ext


class Video(Cog_Extension):
    
    def __init__(self,*args,**kwargs): 
        super().__init__(*args,**kwargs)

        #all the music related stuff
        self.is_playing = False

        # 2d array containing [song, channel]
        self.music_queue = []
        self.YDL_OPTIONS = {'format': 'bestaudio', 'noplaylist':'True'}
        self.FFMPEG_OPTIONS = {'before_options': '-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 5', 'options': '-vn'}

        self.vc = ""

    #searching the item on youtube
    def search_yt(self, item):
        with YoutubeDL(self.YDL_OPTIONS) as ydl:
            try: 
                info = ydl.extract_info("ytsearch:%s" % item, download=False)['entries'][0]
            except Exception: 
                return False

        return {'source': info['formats'][0]['url'], 'title': info['title']}

    #@commands.command(name="download", help="用於下載youtube影片(參數:網址)")
    @cog_ext.cog_slash(name="download", description="用於下載youtube影片")
    async def __download(self, ctx,*,url):

        query = url
        

        video = self.search_yt(query)

        if type(video) == type(True):
            await ctx.send("無法下載影片")
        else:

            BITLY_ACCESS_TOKEN ="b0af76aa8515aee580ffac8d6f26d7ee02501ddc"

            x = bitly_api.Connection(access_token = BITLY_ACCESS_TOKEN)

            shorten_url = x.shorten(video["source"])

            await ctx.send("下載連結: "+ shorten_url["url"])  #

                
def setup(bot): #運行bot時,會呼叫 setup => 註冊
    bot.add_cog(Video(bot))
