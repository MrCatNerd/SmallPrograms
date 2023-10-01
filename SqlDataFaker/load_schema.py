# TODO: add more types

"""
types:
    INT,
    DECIMAL52,
    DATE,
    VARCHAR50,
    NAME,
    CITY,
    FIRSTNAME,
    LASTNAME,
    ID9INT,
    USERNAME,
    PASSWORD,
    INTID
"""

import json

def get_schema_types(path:str="schema.json") -> list:
    with open(path, "r") as fp:
        schema_json = json.load(fp)

    return schema_json
