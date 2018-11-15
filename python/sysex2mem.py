#!/bin/env python3

# This tool will read in a .syx file and output a memory file with the corresponding writes.

import sys
from enum import Enum

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

START_SYSEX = 0xf0
END_SYSEX = 0xf7
ROLAND_ID = 0x41
DEV_ID = 0x10
MODEL_ID = 0x16

CMD_DATA_SET = 0x12


class SyxParser:



    def __init__(self):
        self.state = State.INIT
        self.address = 0
        self.memory = {}
        self.pending_write = None

    def readByte(self, b):
        if self.state == State.INIT:
            if b == START_SYSEX:
                self.state = State.MFG_ID
                return

        elif self.state == State.MFG_ID:
            if b == ROLAND_ID:
                self.state = State.DEV_ID
                return
        
        elif self.state == State.DEV_ID:
            if b == DEV_ID:
                self.state = State.MODEL_ID
                return

        elif self.state == State.MODEL_ID:
            if b == MODEL_ID:
                self.state = State.COMMAND
                return

        elif self.state == State.COMMAND:
            if b == CMD_DATA_SET:
                self.state = State.ADDR_MSB
                return
            else:
                print('Unknown command: ' + hex(b))
                self.state = UNRECOGNIZED
                return
        

        elif self.state == State.ADDR_MSB:
            self.state = State.ADDR_MB
            self.address = b * 256 * 256
            self.sum = b
            return

        elif self.state == State.ADDR_MB:
            self.state = State.ADDR_LSB
            self.address += b * 256
            self.sum += b
            return

        elif self.state == State.ADDR_LSB:
            self.state = State.DATA
            self.address += b
            self.sum += b
            return

        elif self.state == State.DATA:
            if b == END_SYSEX:
                self.state = State.INIT

                self.pending_write = None

                if self.sum & 0x7f:
                    print('Warning: checksum error')


                return
            else:
                if self.pending_write:
                    self.memory[self.pending_write[0]] = self.pending_write[1]
                    self.pending_write = None

                if self.address in self.memory:
                    print('Warning: overwriting ' + hex(self.memory[self.address]) + ' with ' + hex(b) + ' at address ' + hex(self.address))
                # self.memory[self.address] = b

                self.pending_write = (self.address, b)

                # print('Writing ' + hex(b) + ' to address ' + hex(self.address))

                self.address = self.next_address(self.address)
                self.sum += b
                return

        elif self.state == State.UNRECOGNIZED:
            if b == END_SYSEX:
                self.state = State.INIT
                return

        else:
            raise RuntimeError('Unimplemented state: ' + str(self.state))


        self.complain(b)


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
            




    # Raise an exception
    def complain(self, b):
        raise RuntimeError('Unexpected byte ' + hex(b) + ' while in ' + str(self.state))



if len(sys.argv) < 2:
    print("The first argument must be a .syx file.")
    exit(1)

parser = SyxParser()

with open(sys.argv[1], "rb") as f:
    counter = 0

    try:
        byte = f.read(1)
        while byte:
            # print(int.from_bytes(byte, byteorder='big'))
            parser.readByte(int.from_bytes(byte, byteorder='big'))
            counter += 1
            byte = f.read(1)
    except RuntimeError as error:
        print(error)
        print('At byte ' + hex(counter))

print(parser.dump_memory())