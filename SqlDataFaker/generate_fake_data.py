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

import random
import string
from faker import Faker
from config import config

fake = Faker()

_int_min_range = config["int"][0]
_int_max_range = config["int"][1]
_varchar_50_len = config["varchar50"]


def string_syntax(func):
    def newfunc(*args, **kwargs) -> str:
        output = func(*args, **kwargs)

        if type(output) is str:
            output = f'"{output}"'

        return output

    return newfunc


# THIS FUNCTION IS CALLED THAUSNADS OF TIMES FOR LARGE DATA SO MAKE IT QUICK!
@string_syntax
def convert_schema_str_to_type_random(
    typestr: str, id: int,
):  # this implementation is bad
    typestr = typestr.upper()

    if typestr == "INT":
        return random.randint(_int_min_range, _int_max_range)
    elif typestr == "DECIMAL52":
        return round(random.randint(0, 1000) / 2, 2)
    elif typestr == "DATE":
        # fake date of birth
        year_of_birth = random.randint(1, 2500)
        month_of_birth = random.randint(1, 12)
        day_of_birth = random.randint(1, 29)

        if month_of_birth == 2 and day_of_birth > 28:
            day_of_birth = 28

        # make into a string
        date_of_birth_str: str = (
            f"{year_of_birth:04d}-{month_of_birth:02d}-{day_of_birth:02d}"
        )

        return date_of_birth_str
    elif typestr == "VARCHAR50":
        return "".join([random.choice(string.ascii_letters) for _ in range(_varchar_50_len)])
    elif typestr == "NAME":
        return fake.name()
    elif typestr == "CITY":
        return fake.city()
    elif typestr == "FIRSTNAME":
        return fake.name().split()[0].strip()
    elif typestr == "LASTNAME":
        return fake.name().split()[1].strip()
    elif typestr == "ID9INT":
        return "".join(str(random.randint(0, 9)) for _ in range(9))
    elif typestr == "USERNAME":
        return fake.user_name()
    elif typestr == "PASSWORD":
        return fake.password()
    elif typestr == "INTID":
        return id
    else:
        raise TypeError("Invalid schema make sure your types are right!")


def fake_data(
    schema_json: list, id: int
) -> list:  # idk why i split it to 2 functions i just want it that way
    data: list = []

    for i in range(len(schema_json)):
        data.append(convert_schema_str_to_type_random(schema_json[i], id))

    return data
