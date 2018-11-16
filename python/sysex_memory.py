#!/bin/env python3

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

    def __init__(self):
        self.memory = {}

    
    # Increment the address, keeping in mind 7-bit hex format
    def next_address(self, address):
        address += 1
        if address & 0x80:
            address = (address & 0xFFFF00) + 0x100
        if address & 0x8000:
            address = (address & 0xFF00FF) + 0x10000
        if address & 0xFF808080:
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
        

    def write_memory(self, filename=None):
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

        if filename:
            open(filename, 'w').write(result)

        return result