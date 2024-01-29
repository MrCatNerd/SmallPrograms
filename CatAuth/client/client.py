import socket
import json

HOST: str = socket.gethostbyname(socket.gethostname())  # get ipv4 addr automaticall
PORT: int = 65432  # Port to listen on (non-privileged ports are > 1023)
ADDR: tuple[str, int] = (HOST, PORT)
EXIT_THINGY: str = "yes"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    connected: bool = True

    server.connect(ADDR)

    while connected:
        msg = {
            "action": "isvalid",
            "key": "8591813fab40938654310a176b6ee44714d9404451664533d11d4ec2b859de37",
        }  # check if a certain key is valid
        # msg = {"action": "newkey"}  # create new key

        inp = input("Do you want to quit? ")

        if inp.strip() == EXIT_THINGY:
            msg = "!quit!"
            connected = False
        else:
            msg = json.dumps(msg)

        server.send(msg.encode())

        data = server.recv(1024).decode()

        # if not data:
        #     print("yes")
        #     break
        #
        # print(json.loads(data))
        print(data)

    server.close()
