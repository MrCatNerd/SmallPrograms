config = {"int": [0, 1000], "varchar50": 50}  # min, max  # length

# makes sure that the config is valid

if config["varchar50"] > 50:
    config["varchar50"] = 50

config["varchar50"] = int(config["varchar50"])
config["int"] = [int(config["int"][0]), int(config["int"][1])]
