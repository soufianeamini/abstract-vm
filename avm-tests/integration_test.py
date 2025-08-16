from subprocess import Popen, PIPE

def run_program(args: list[str]) -> Popen[bytes]:
    p = Popen(["./avm"] + args, stdin=PIPE, stdout=PIPE)
    return p


def test_example_program():
    with open("./avm-tests/example.avm.output") as output:
        expected = output.read()
        p = run_program(["avm-tests/example.avm"])
        stdout, _ = p.communicate()

        assert p.returncode == 0
        assert stdout == expected.encode()

def test_example_program_from_input():
    with open("./avm-tests/example.avm.output") as output, open("./avm-tests/example.avm.input") as input:
        expected = output.read()
        p = run_program([])
        stdout, _ = p.communicate(input.read().encode(), timeout=3)

        assert p.returncode == 0
        assert stdout == expected.encode()
