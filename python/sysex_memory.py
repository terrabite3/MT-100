#!/bin/env python3

import sys
from enum import Enum

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

class SysExMemory:

    
    START_SYSEX = 0xf0
    END_SYSEX = 0xf7
    ROLAND_ID = 0x41
    DEV_ID = 0x10
    MODEL_ID = 0x16

    CMD_DATA_SET = 0x12


    address_names = {
        0x02_00_00: '# Timbre Temp',
        0x03_00_00: '# Patch Temp',
        0x03_01_10: '# Rhythm Setup Temp',
        0x04_00_00: '# Timbre Temp',
        0x05_00_00: '# Patch Memory',
        0x08_00_00: '# Timbre Memory',
        0x10_00_00: '# System Area',
        0x20_00_00: '# Display',
    }


    def __init__(self):
        self.memory = {}

    
    # Increment the address, keeping in mind 7-bit hex format
    def next_address(self, address):
        address += 1
        if address & 0x80:
            address = (address & 0xFF_FF_00) + 0x1_00
        if address & 0x80_00:
            address = (address & 0xFF_00_FF) + 0x1_00_00
        if address & 0xFF_80_80_80:
            eprint('Bad address: ' + hex(address))
        return address


    def read_syx(self, filename):
        class State(Enum):
            INIT = 0
            MFG_ID = 1
            DEV_ID = 2
            MODEL_ID = 3
            COMMAND = 4
            ADDR_MSB = 5
            ADDR_MB = 6
            ADDR_LSB = 7
            DATA = 8

            UNRECOGNIZED = 100

        # Don't overwrite the memory until we finish successfully
        memory = {}
        state = State.INIT
        address = 0
        pending_write = None
        sum = 0

        bytes_read = open(filename, 'rb').read()

        for b in bytes_read:

            if state == State.INIT:
                if b == self.START_SYSEX:
                    state = State.MFG_ID
                    continue

            elif state == State.MFG_ID:
                if b == self.ROLAND_ID:
                    state = State.DEV_ID
                    continue
            
            elif state == State.DEV_ID:
                if b == self.DEV_ID:
                    state = State.MODEL_ID
                    continue

            elif state == State.MODEL_ID:
                if b == self.MODEL_ID:
                    state = State.COMMAND
                    continue

            elif state == State.COMMAND:
                if b == self.CMD_DATA_SET:
                    state = State.ADDR_MSB
                    continue
                else:
                    eprint('Unknown command: ' + hex(b))
                    state = UNRECOGNIZED
                    continue
            

            elif state == State.ADDR_MSB:
                state = State.ADDR_MB
                address = b * 256 * 256
                sum = b
                continue

            elif state == State.ADDR_MB:
                state = State.ADDR_LSB
                address += b * 256
                sum += b
                continue

            elif state == State.ADDR_LSB:
                state = State.DATA
                address += b
                sum += b
                continue

            elif state == State.DATA:
                if b == self.END_SYSEX:
                    state = State.INIT

                    pending_write = None

                    if sum & 0x7f:
                        eprint('Warning: checksum error')


                    continue
                else:
                    if pending_write:
                        memory[pending_write[0]] = pending_write[1]
                        pending_write = None

                    if address in memory:
                        eprint('Warning: overwriting ' + hex(memory[address]) + ' with ' + hex(b) + ' at address ' + hex(address))

                    pending_write = (address, b)

                    address = self.next_address(address)
                    sum += b
                    continue

            elif state == State.UNRECOGNIZED:
                if b == self.END_SYSEX:
                    state = State.INIT
                    continue

            else:
                raise RuntimeError('Unimplemented state: ' + str(state))

            raise RuntimeError('Unexpected byte ' + hex(b) + ' while in ' + str(state))

        # Store the completed memory in the object
        self.memory = memory


    def write_syx(self, out_file):
        result = bytearray()


        # Each write is a 2-tuple (address, [data0, data1, ... dataN])
        writes = []

        pending_write = None

        # Avoid looping over empty regions
        for window in sorted(set(x & 0xff_00_00 for x in self.memory)):
            for address in range(window, window + 0x1_00_01):

                # Skip invalid 7-bit addresses
                if address & 0x80_80_80:
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

            address = write[0]
            data = write[1]

            # Start with the header
            result.append(self.START_SYSEX)
            result.append(self.ROLAND_ID)
            result.append(self.DEV_ID)
            result.append(self.MODEL_ID)
            result.append(self.CMD_DATA_SET)

            # Address
            result.append((address & 0x7f_00_00) >> 16)
            result.append((address & 0x7f_00) >> 8)
            result.append(address & 0x7f)
            sum = (address & 0x7f_00_00) >> 16
            sum += (address & 0x7f_00) >> 8
            sum += address & 0x7f

            # Data
            for byte in data:
                result.append(byte)
                sum += byte

            # Checksum
            result.append(0x80 - (sum & 0x7f))

            # End SYSEX
            result.append(self.END_SYSEX)


        open(out_file, 'wb').write(result)




    def read_memory(self, filename):
        memory = {}

        for line in open(filename, 'r').readlines():
            # Treat anything after a # as a comment
            if '#' in line:
                line = line[:line.find('#')]

            # Ignore empty lines
            if len(line.strip()) == 0:
                continue

            tokens = line.split(':')
            if len(tokens) != 2:
                eprint('Invalid line: ' + line)
                continue

            address = int(tokens[0], 16)

            if address & 0xFF_80_80_80:
                eprint('Bad address: ' + hex(address))
                continue

            byte_pairs = tokens[1].split()

            for pair in byte_pairs:
                if len(pair) != 4:
                    eprint('Invalid bytes: ' + pair)
                    continue

                byte0 = pair[0:2]
                byte1 = pair[2:4]

                if byte0 != '..':
                    if address in memory:
                        eprint('Warning: overwriting ' + hex(memory[address]) + ' with ' + byte0 + ' at address ' + hex(address))
                    memory[address] = int(byte0, 16)
                address += 1

                if byte1 != '..':
                    if address in memory:
                        eprint('Warning: overwriting ' + hex(memory[address]) + ' with ' + byte1 + ' at address ' + hex(address))
                    memory[address] = int(byte1, 16)
                address += 1

        self.memory = memory


    def write_memory(self, filename=None):
        result = ''

        for row_offset in sorted(set(x & 0xFF_FF_F0 for x in self.memory)):
            row = ''

            # Skip invalid addresses (7-bit hex)
            if row_offset & 0x80_80_80:
                continue

            if row_offset in self.address_names:
                row = self.address_names[row_offset] + '\n'

            row += '%0.6x:' % row_offset

            for addr in range(0x10):
                if not addr & 1:
                    row += ' '

                if row_offset + addr in self.memory:
                    row += '%0.2x' % self.memory[row_offset + addr]
                else:
                    row += '..'

            result += row + '\n'

        if filename:
            open(filename, 'w').write(result)

        return result