import discord
import psycopg2
from discord.ext import commands

class Cog_Extension(commands.Cog): 
    def __init__(self,bot):
        self.bot = bot
        # 把 Heroku Postgres 的相關資訊寫到下列指令 (database, user, password, host, port)
        self.conn=psycopg2.connect(database="postgres",user="kay",password="asx5566789",host="discordbotdatabase.czhutqsbjfeu.us-east-1.rds.amazonaws.com",port="5432")
        self.cursor=self.conn.cursor()
        self.create_table_query = '''CREATE TABLE IF NOT EXISTS discord_Yue(
                                id VARCHAR (50) ,
                                code VARCHAR (50) 
                                );'''
        self.cursor.execute(self.create_table_query)
        self.conn.commit()

        #record = ('','')  # id,code
        #table_columns = '(id,code)'
        #postgres_insert_query = f"""INSERT INTO discord_Yue {table_columns} VALUES (%s, %s);"""

        #self.cursor.execute(postgres_insert_query, record)
        #self.conn.commit()

        #delete_table_query = '''DROP TABLE IF EXISTS discord_yue'''
        #self.cursor.execute(delete_table_query)
        #self.conn.commit()

        self.postgres_select_query = f"""SELECT * FROM discord_Yue"""
        self.cursor.execute(self.postgres_select_query)
        self.all=self.cursor.fetchall()



