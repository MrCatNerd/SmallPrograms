from faker import Faker
from load_schema import get_schema_types
from generate_fake_data import fake_data

fake = Faker()


def create_sql_syntax(id: int, n: int, data: list) -> str:
    # extract data cause f-strings are anoyying

    syntax = "("

    for i in range(len(data)):
        item = data[i]

        if i == len(data) - 1:
            syntax = f"{syntax}{item}"
        else:
            syntax = f"{syntax}{item}, "

    if id < n:
        syntax = f"{syntax}),\n"
    else:
        syntax = f"{syntax});"

    return syntax


def assemble(n: int, db_name: str = "mydb_fake") -> str:
    lines: list[str] = []
    for id in range(1, n + 1):
        data = fake_data(get_schema_types(), id)

        syntax: str = create_sql_syntax(id, n, data)
        lines.append(syntax)

    insertions = "".join(str(line) for line in lines)

    result = f"USE {db_name};\n\nINSERT INTO person VALUES\n{insertions}\n\nSELECT * FROM person LIMIT 50;".strip()

    return result
