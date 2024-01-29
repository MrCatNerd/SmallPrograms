import json

from os.path import join


def get_settings() -> dict:
    result = dict()

    with open(join("data", "settings.json"), "r") as sjf:
        result = json.load(sjf)

    return result


settings = get_settings()

# Defines the key length in bytes (for example, 32 bytes for a 256-bit key)
KEY_LENGTH_BYTES: int = settings["key length bytes"]
