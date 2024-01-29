import discord
from discord import app_commands
from discord.ext import commands

from settings import *

intents = discord.Intents.all()
intents.messages = True

bot = commands.Bot(command_prefix="/", intents=intents)


@bot.event
async def on_ready():
    print(f"Logged in as {bot.user.name}")

    try:
        synced = await bot.tree.sync()
        print(f"Synced up {len(synced)} command(s)")
    except Exception as e:
        print(e)


@bot.tree.command(name="note")
@app_commands.describe(message="message")
async def start(
    intrection: discord.Interaction,
    message: str,
) -> None:

    output = message

    embed = discord.Embed(
        title=f"{intrection.user.name}",
        description=f"`{output}`",
        color=discord.Colour.red(),
    )

    embed.set_footer(text=f"{BOT_TAG} made this embed")

    await intrection.response.send_message(embed=embed, ephemeral=True)


bot.run(TOKEN)
