from subprocess import Popen, PIPE
from ward import test

def run_program(args: list[str]) -> Popen[bytes]:
    p = Popen(["./avm"] + args, stdin=PIPE, stdout=PIPE)
    return p


@test("Test example program")
def _():
    with open("./tests/example.avm.output") as output:
        expected = output.read()
        p = run_program(["tests/example.avm"])
        stdout, _ = p.communicate()

        assert p.returncode == 0
        assert stdout == expected.encode()

@test("Test example program from input")
def _():
    with open("./tests/example.avm.output") as output, open("./tests/example.avm.input") as input:
        expected = output.read()
        p = run_program([])
        stdout, _ = p.communicate(input.read().encode(), timeout=3)

        assert p.returncode == 0
        assert stdout == expected.encode()
