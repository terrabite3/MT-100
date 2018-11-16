#!/usr/bin/env python3

# This tool will read in a memory file and output a .syx file with the corresponding writes.

import sys
from sysex_memory import *


if len(sys.argv) < 3:
    eprint("The first argument must be a memory file. The second argument must be the output file.")
    exit(1)


parser = SysExMemory()

try:
    parser.read_memory(sys.argv[1])
    
    parser.write_syx(sys.argv[2])

except RuntimeError as error:
    eprint(error)
