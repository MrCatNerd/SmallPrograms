import socket
import threading
import json
import asyncio  # :(
import aiosqlite
from os.path import join

from keys import (
    is_key_valid,
    create_new_key,
    create_table_if_not_existing,
)
from utils import has_key

HOST: str = socket.gethostbyname(socket.gethostname())  # get ipv4 addr automaticall
PORT: int = 65432  # Port to listen on (non-privileged ports are > 1023)

# TODO: maximum amount of tries so people dont brueforce it


async def _json_with_none(data):  # custom json decoder
    try:
        return json.loads(data)
    except (
        ValueError
    ):  # simplejson.decoder.JSONDecodeError actually inherits from ValueError
        return None


async def handle_client(conn: socket.socket, addr: tuple) -> None:
    print(f"[{addr[0]}] New connection")

    while True:
        pure_recv = conn.recv(1024)
        if pure_recv:
            response = {
                "message": "Invalid request",
                "data": None,
                "error": True,
            }

            data: dict | None = await _json_with_none(pure_recv)

            if data is None:
                response = json.dumps(response).encode()
                conn.sendall(response)
                continue

            if has_key("action", data) and has_key("key", data):
                if data.get("action") == "isvalid":
                    # await is_key_valid(data)
                    pass
                elif data.get("action") == "newkey":
                    # await create_new_key(data["key"])
                    pass

            response = json.dumps(response).encode()
            conn.sendall(response)

    await close_sqlite_con()
    print(f"[{addr[0]}] Connection disconnected")


async def handle_clientz(reader, writer, sql_con) -> None:
    addr = writer.get_extra_info("peername")  # get ADDR

    connected: bool = True

    number_of_tries: int = 0

    print(f"[{addr}] New connection!")

    while connected:
        message = (await reader.read(1024)).decode()

        if message:
            response = {
                "message": "Invalid request",
                "data": None,
                "error": True,
            }

            if message.strip() == "!quit!":
                connected = False
                response["error"] = False
                response["message"] = "adios"
            else:
                data: dict | None = await _json_with_none(message)

                if has_key("action", data) and data is not None:
                    if data["action"] == "isvalid" and has_key("key", data):
                        response["data"] = (
                            await is_key_valid(data, sql_con)
                            if number_of_tries < 100
                            else False
                        )

                        if response["data"]:
                            response["message"] = ""

                        elif number_of_tries > 100:
                            response["message"] = "Too many tries"
                        else:
                            response["message"] = "Key isn't valid!"
                            number_of_tries += 1

                        response["error"] = response["data"]
                    elif data["action"] == "newkey":
                        response["data"] = await create_new_key(sql_con)
                        response["message"] = ""
                        response["error"] = False

            response = json.dumps(response)

            writer.write(response.encode())  # like send
            await writer.drain()  # waits til write is done

    # Close the connection
    writer.close()  # close connection
    await writer.wait_closed()  # wait til close is done
    print("Connection disconnected")


async def run_server() -> None:
    async with aiosqlite.connect(join("data", "data.db")) as sql_con:
        await create_table_if_not_existing(sql_con)

        server = await asyncio.start_server(
            lambda r, w: handle_clientz(r, w, sql_con), HOST, PORT
        )

        print("Server is up and running!")

        async with server:
            await server.serve_forever()
    print("Server is shut down!")


async def main() -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print("Server is up and running!")
        for _ in range(10):
            conn, addr = s.accept()

            t = threading.Thread(target=handle_client, args=(conn, addr))
            t.start()

    print("Server is shut down")


if __name__ == "__main__":
    asyncio.run(run_server())
    # print(generate_random_key_hex())
