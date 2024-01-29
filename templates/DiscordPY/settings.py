import json
from os.path import join

with open(
    join("data", "settings.json"),
    "r",
) as settings:
    data: dict = json.load(settings)

TOKEN = data["token"]
BOT_TAG = data["bot tag"]

del json, join, data
