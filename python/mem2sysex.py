#!/bin/env python3

# This tool will read in a memory file and output a .syx file with the corresponding writes.

import sys

START_SYSEX = 0xf0
END_SYSEX = 0xf7
ROLAND_ID = 0x41
DEV_ID = 0x10
MODEL_ID = 0x16

CMD_DATA_SET = 0x12


class MemParser:

    def __init__(self):
        self.memory = {}

    def readLine(self, line):
        # Ignore empty lines
        if len(line.strip()) == 0:
            return
        
        tokens = line.split(':')
        if len(tokens) != 2:
            print('Invalid line: ' + line)
            return

        address = int(tokens[0], 16)

        if address & 0xFF808080:
            print('Bad address: ' + hex(address))
            return

        byte_pairs = tokens[1].split()

        for pair in byte_pairs:
            if len(pair) != 4:
                print('Invalid bytes: ' + pair)
                return

            byte0 = pair[0:2]
            byte1 = pair[2:4]

            if byte0 != '..':
                if address in self.memory:
                    print('Warning: overwriting ' + hex(self.memory[address]) + ' with ' + byte0 + ' at address ' + hex(address))
                self.memory[address] = int(byte0, 16)
            address += 1

            if byte1 != '..':
                if address in self.memory:
                    print('Warning: overwriting ' + hex(self.memory[address]) + ' with ' + byte1 + ' at address ' + hex(address))
                self.memory[address] = int(byte1, 16)
            address += 1

    def dump_memory(self):
        result = ''

        prev_row_found = False

        for row_offset in range(0, 0x800000, 0x10):
            # Skip invalid addresses (7-bit hex)
            if row_offset & 0x808080:
                continue

            found_data = False
            row = '%0.6x:' % row_offset

            for addr in range(0x10):
                if not addr & 1:
                    row += ' '

                if row_offset + addr in self.memory:
                    found_data = True
                    row += '%0.2x' % self.memory[row_offset + addr]
                else:
                    row += '..'

            if found_data:
                result += row + '\n'
            elif prev_row_found:
                # Insert a single blank line when there is a gap
                result += '\n'

            prev_row_found = found_data

        return result
            

    # Increment the address, keeping in mind 7-bit hex format
    def next_address(self, address):
        address += 1
        if address & 0x80:
            address = (address & 0xFFFF00) + 0x100
        if address & 0x8000:
            address = (address & 0xFF00FF) + 0x10000
        if address & 0xFF808080:
            print('Bad address: ' + hex(address))
        return address


    def dump_commands(self, out_file):

        # Each write is a 2-tuple (address, [data0, data1, ... dataN])
        writes = []

        pending_write = None

        for address in range(0, 0x800000):

            # Skip invalid 7-bit addresses
            if address & 0x808080:
                continue

            # If an address is skipped, that's the end of the write
            if address not in self.memory:
                if pending_write:
                    writes.append(pending_write)
                    pending_write = None
                continue

            if not pending_write:
                pending_write = (address, [])

            pending_write[1].append(self.memory[address])

            if len(pending_write[1]) == 256:
                writes.append(pending_write)
                pending_write = None

        

        for write in writes:
            # print(write)

            address = write[0]
            data = write[1]

            # Start with the header
            ba = bytearray( [
                START_SYSEX,
                ROLAND_ID,
                DEV_ID,
                MODEL_ID,
                CMD_DATA_SET
            ] )

            # Address
            ba.append((address & 0x7f0000) >> 16)
            ba.append((address & 0x7f00) >> 8)
            ba.append(address & 0x7f)
            sum = (address & 0x7f0000) >> 16
            sum += (address & 0x7f00) >> 8
            sum += address & 0x7f

            # Data
            for byte in data:
                ba.append(byte)
                sum += byte

            # Checksum
            ba.append(0x80 - (sum & 0x7f))

            # End SYSEX
            ba.append(END_SYSEX)

            out_file.write(ba)




if len(sys.argv) < 3:
    print("The first argument must be a memory file. The second argument must be the output file.")
    exit(1)

parser = MemParser()

with open(sys.argv[1], "r") as f:
    counter = 0

    try:
        line = f.readline()
        while line:
            parser.readLine(line)
            counter += 1
            line = f.readline()
    except RuntimeError as error:
        print(error)
        print('At line ' + hex(counter))

with open(sys.argv[2], 'wb') as f:
    parser.dump_commands(f)