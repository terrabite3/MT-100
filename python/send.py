import time
import rtmidi
import sys
import os
import json

from sysex_memory import *
from mt_parameters import *

if len(sys.argv) < 2:
    eprint("Requires an argument syx file")
    exit(1)
    
in_file = sys.argv[1]
in_extension = os.path.splitext(in_file)[1].lower()

midiout = rtmidi.MidiOut()
available_ports = midiout.get_ports()


for i in range(len(available_ports)):
    if 'UMC404' in available_ports[i]:
        midiout.open_port(i)
        break


if in_extension == '.json':
    with open(in_file, 'r') as json_file:
        in_dict = json.load(json_file)

    in_parameters = MtParameters()
    in_parameters.load_dict(in_dict)

    memory = SysExMemory()

    in_parameters.write_to_memory(memory.memory)

    bytes_read = memory.write_syx()


elif in_extension == '.mem':
    memory = SysExMemory()
    memory.read_memory(in_file)

    bytes_read = memory.write_syx()

elif in_extension == '.syx':
    bytes_read = open(in_file, mode='rb').read()
    

else:
    eprint('Unrecognized input file extension: ' + in_extension)
    exit(1)


syx_message = [int(byte) for byte in bytes_read]

midiout.send_message(syx_message)

del midiout