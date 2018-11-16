#!/bin/env python3

# This tool will read in a .syx file and output a memory file with the corresponding writes.

import sys
from sysex_memory import SysExMemory


if len(sys.argv) < 2:
    eprint("The first argument must be a .syx file.")
    exit(1)


parser = SysExMemory()

try:
    parser.read_syx(sys.argv[1])

    if len(sys.argv) >= 3:
        parser.write_memory(sys.argv[2])
    else:
        print(parser.write_memory())

except RuntimeError as error:
    eprint(error)

