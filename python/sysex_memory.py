#!/usr/bin/env python3

import sys
from enum import Enum

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def seven(address):
    if address >= native(0x40_00_00):
        raise RuntimeError('Native address too large: ' + hex(address))

    result = address & 0x7f
    result += (address << 1) & 0x7f_00
    result += (address << 2) & 0x7f_00_00
    return result

def native(address):
    if type(address) is str:
        # Remove any leading or trailing whitespace
        address = address.strip()
        # Remove a leading '0x'
        if address[0:2].lower() == '0x':
            address = address[2:]
        # Remove any separating underscores
        address.replace('_', '')
        return native(int(address, 16))

    elif type(address) is bytearray:
        if len(address) == 3:
            result = address[0] << 14
            result += address[1] << 7
            result += address[2]
            return result

    elif type(address) is int:
        result = address & 0x7f
        result += (address & 0x7f_00) >> 1
        result += (address & 0x7f_00_00) >> 2 
        return result


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
                address = b * 128 * 128
                sum = b
                continue

            elif state == State.ADDR_MB:
                state = State.ADDR_LSB
                address += b * 128
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
                        eprint('Warning: overwriting ' + hex(memory[address]) + ' with ' + hex(b) + ' at address ' + hex(seven(address)))

                    pending_write = (address, b)

                    address += 1
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


    def write_syx(self, out_file=None):
        result = bytearray()


        # Each write is a 2-tuple (address, [data0, data1, ... dataN])
        writes = []

        pending_write = None

        for address in range(native(0x20_01_00)):
            # If an address is skipped, that's the end of the write
            if address not in self.memory:
                if pending_write:
                    writes.append(pending_write)
                    pending_write = None
                continue

            if not pending_write:
                pending_write = (seven(address), [])

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


        if out_file:
            open(out_file, 'wb').write(result)

        return result




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

            address = native(int(tokens[0], 16))

            byte_pairs = tokens[1].split()

            for pair in byte_pairs:
                if len(pair) != 4:
                    eprint('Invalid bytes: ' + pair)
                    continue

                byte0 = pair[0:2]
                byte1 = pair[2:4]

                if byte0 != '..':
                    if address in memory:
                        eprint('Warning: overwriting ' + hex(memory[address]) + ' with ' + byte0 + ' at address ' + hex(seven(address)))
                    memory[address] = int(byte0, 16)
                address += 1

                if byte1 != '..':
                    if address in memory:
                        eprint('Warning: overwriting ' + hex(memory[address]) + ' with ' + byte1 + ' at address ' + hex(seven(address)))
                    memory[address] = int(byte1, 16)
                address += 1

        self.memory = memory


    def write_memory(self, filename=None):
        result = ''

        for row_offset in sorted(set(x & native(0xFF_FF_F0) for x in self.memory)):
            row = ''

            if seven(row_offset) in self.address_names:
                row = self.address_names[seven(row_offset)] + '\n'

            row += '%0.6x:' % seven(row_offset)

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