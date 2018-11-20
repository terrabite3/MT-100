
import sys
from sysex_memory import *
from mt_parameters import MtParameters

if len(sys.argv) < 2:
    eprint("The first argument must be a .syx file.")
    exit(1)


parser = SysExMemory()

try:
    parser.read_syx(sys.argv[1])

    params = MtParameters()
    params.load_from_memory(parser.memory)
    params.display = 'Hello'
    params.write_to_memory(parser.memory)

    print(parser.write_memory())


except RuntimeError as error:
    eprint(error)

