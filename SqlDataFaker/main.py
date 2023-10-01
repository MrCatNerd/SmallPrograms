# TODO: make a thing that uses the api instead of generating syntax

import time

from syntax import assemble

print("counting...")
start = time.time()
result = assemble(10000, "anotherdb")

WRITE_TO_FILE: bool = True

if WRITE_TO_FILE:
    with open("result.txt", "w") as f:
        f.write(result)
else:
    print(result)

end = time.time()

generating_time = round((end - start), 3)

print(f"generating time: {generating_time}s")
