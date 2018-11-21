#!/usr/bin/env python3

import sys
import os
from sysex_memory import *
from mt_parameters import *
import json

if len(sys.argv) < 2:
    eprint("The first argument must be a .json file.")
    exit(1)

with open(sys.argv[1], 'r') as json_file:
    # Load a dictionary from the JSON file
    forward_dictionary = json.load(json_file)

    # Load the parameters from the dictionary
    forward_params = MtParameters()
    forward_params.load_dict(forward_dictionary)

    # Write the memory from the parameters
    forward_memory = SysExMemory()
    forward_params.write_to_memory(forward_memory.memory)

    # Write a SYX file from the memory
    forward_memory.write_syx('temp.syx')


    # Read the SYX file into memory
    reverse_memory = SysExMemory()
    reverse_memory.read_syx('temp.syx')

    # Remove the temporary file
    os.remove('temp.syx')

    # Read the memory into parameters
    reverse_params = MtParameters()
    reverse_params.load_from_memory(reverse_memory.memory)

    # Write the parameters to a dictionary
    reverse_dictionary = {}
    reverse_params.write_dict(reverse_dictionary)


    # Compare the two dictionaries as JSON strings
    original_json_string = json.dumps(forward_dictionary, sort_keys=True, indent=2)
    final_json_string = json.dumps(reverse_dictionary, sort_keys=True, indent=2)

    if original_json_string == final_json_string:
        print('Success')
        exit(0)
    else:
        print('Mismatch')
        print('Original: ' + str(original_json_string))
        print('Final: ' + str(final_json_string))