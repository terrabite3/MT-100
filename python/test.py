
import sys
from sysex_memory import *
from mt_parameters import *
import json

if len(sys.argv) < 2:
    eprint("The first argument must be a .syx file.")
    exit(1)


parser = SysExMemory()

try:
    parser.read_syx(sys.argv[1])

    params = MtParameters()
    params.load_from_memory(parser.memory)

    j = json.dumps(params, cls=MtJsonEncoder)
    print(j)

    d = json.loads(j)
    d['display'] = 'Hello'
    d['system']['master_tune'] = 450

    params2 = MtParameters()
    params2.load_json(d)

    parser2 = SysExMemory()
    params2.write_to_memory(parser2.memory)

    print(parser2.write_memory())


except RuntimeError as error:
    eprint(error)

