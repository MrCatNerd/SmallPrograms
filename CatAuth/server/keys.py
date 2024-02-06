import secrets

import aiosqlite
import aiosqlite

from settings import KEY_LENGTH_BYTES


async def create_table_if_not_existing(sql_con: aiosqlite.Connection) -> None:
    await sql_con.execute("CREATE TABLE IF NOT EXISTS keys (key STRING PRIMARY KEY);")
    await sql_con.commit()


async def is_key_valid(data: dict, sql_con: aiosqlite.Connection) -> bool:
    sql_cursor = await sql_con.execute("SELECT * FROM keys;")

    fa = map(lambda tuple_type: tuple_type[0], await sql_cursor.fetchall())

    return data["key"] in fa


async def create_new_key(sql_con: aiosqlite.Connection) -> str:
    key = secrets.token_bytes(KEY_LENGTH_BYTES).hex()

    await sql_con.execute(
        "INSERT INTO keys VALUES (?);",
        (key,),
    )
    await sql_con.commit()

    return key
