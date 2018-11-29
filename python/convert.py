#!/usr/bin/env python3

import sys
import os
from sysex_memory import *
from mt_parameters import *
import json

if len(sys.argv) < 3:
    eprint("Requires two file arguments, input and output")
    exit(1)

in_file = sys.argv[1]
out_file = sys.argv[2]

in_extension = os.path.splitext(in_file)[1].lower()
out_extension = os.path.splitext(out_file)[1].lower()

memory = SysExMemory()

if in_extension == '.json':
    with open(in_file, 'r') as json_file:
        in_dict = json.load(json_file)

    in_parameters = MtParameters()
    in_parameters.load_dict(in_dict)
    in_parameters.write_to_memory(memory.memory)


elif in_extension == '.syx':
    memory.read_syx(in_file)


elif in_extension == '.mem':
    memory.read_memory(in_file)


else:
    eprint('Unrecognized input file extension: ' + in_extension)
    exit(1)


if out_extension == '.json':
    out_parameters = MtParameters()
    out_parameters.load_from_memory(memory.memory)

    out_dict = {}
    out_parameters.write_dict(out_dict)

    with open(out_file, 'w') as json_file:
        json.dump(out_dict, json_file, indent=2)


elif out_extension == '.syx':
    memory.write_syx(out_file)


elif out_extension == '.mem':
    memory.write_memory(out_file)


else:
    eprint('Unrecognized output file extension: ' + out_extension)
    exit(1)

