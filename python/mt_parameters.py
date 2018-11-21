#!/usr/bin/env python3

from sysex_memory import *
from json import JSONEncoder


class Property:
    def __init__(self, name, address):
        self.name = name
        self.address = address
        self.value = None

    def write_dict(self, parent):
        if self.value:
            parent[self.name] = self.value

    def load_dict(self, json):
        if self.name in json:
            self.value = json[self.name]

class ChoiceProperty(Property):
    def __init__(self, name, address, choices):
        Property.__init__(self, name, address)
        self.choices = choices

    def load_from_memory(self, memory):
        if self.address in memory:
            raw_value = memory[self.address]
            if raw_value >= len(self.choices) or raw_value < 0:
                raise RuntimeError('Invalid index {} while loading {} from memory.'.format(raw_value, self.name))
            self.value = self.choices[raw_value]

    def write_to_memory(self, memory):
        if self.value:
            try:
                index = self.choices.index(self.value)
                memory[self.address] = index
            except ValueError as e:
                raise RuntimeError('Invalid choice {} while writing {} to memory.'.format(self.value, self.name))

class StringProperty(Property):
    def __init__(self, name, address, length):
        Property.__init__(self, name, address)
        self.length = length

    def load_from_memory(self, memory):
        if self.address in memory:
            value = ''
            for x in range(self.address, self.address + self.length):
                if x in memory:
                    if memory[x] == 0:
                        break
                    value += chr(memory[x])
                else:
                    break
            self.value = value

    def write_to_memory(self, memory):
        if self.value != None:
            for x in range(self.length):
                if len(self.value) > x:
                    memory[self.address + x] = ord(self.value[x])
                else:
                    memory[self.address + x] = 0

class FloatProperty(Property):
    def __init__(self, name, address, raw_min, raw_max, float_min, float_max):
        Property.__init__(self, name, address)
        self.raw_min = raw_min
        self.raw_max = raw_max
        self.float_min = float_min
        self.float_max = float_max

    def load_from_memory(self, memory):
        if self.address in memory:
            raw_value = memory[self.address]
            if raw_value < self.raw_min or raw_value > self.raw_max:
                raise RuntimeError('Invalid raw value {} while loading {} from memory.'.format(raw_value, self.name))
            self.value = self.float_min + (self.float_max - self.float_min) * ((raw_value - self.raw_min) / (self.raw_max - self.raw_min))
            
    def write_to_memory(self, memory):
        if self.value != None:
            raw_value = (self.value - self.float_min) / (self.float_max - self.float_min) * (self.raw_max - self.raw_min) + self.raw_min
            raw_value = round(raw_value)
            raw_value = min(raw_value, self.raw_max)
            raw_value = max(raw_value, self.raw_min)
            memory[self.address] = raw_value
        

class MtParameters:
    CHANNEL_TIMBRE_TEMP =   native(0x02_00_00)
    PATCH_TEMP =            native(0x03_00_00)
    RHYTHM_SETUP =          native(0x03_01_10)
    TIMBRE_TEMP =           native(0x40_00_00)
    PATCH_MEMORY =          native(0x50_00_00)
    TIMBRE_MEMORY =         native(0x80_00_00)
    SYSTEM_AREA =           native(0x10_00_00)
    DISPLAY =               native(0x20_00_00)
    WRITE_REQUEST =         native(0x40_00_00)

    def __init__(self):
        self.patch_temp = {}
        self.rhythm_setup_temp = {}
        self.timbre_temp = {}
        self.patch_memory = []
        self.timbre_memory = []
        self.system = System(self.SYSTEM_AREA)
        self.display = StringProperty('display', self.DISPLAY, 20)


    def load_from_memory(self, memory):
        self.display.load_from_memory(memory)

        if self.SYSTEM_AREA in memory:
            self.system.load_from_memory(memory)


    def write_to_memory(self, memory):
        self.display.write_to_memory(memory)

        self.system.write_to_memory(memory)


    def write_dict(self, parent):
        self.display.write_dict(parent)

        parent['system'] = {}
        self.system.write_dict(parent['system'])

    def load_dict(self, json):
        self.display.load_dict(json)

        if 'system' in json:
            self.system.load_dict(json['system'])


class System:

    def __init__(self, offset):
        self.offset = offset

        self.master_tune = FloatProperty('master_tune', offset + 0x00, 0, 127, 432.1, 457.6)
        self.reverb_mode = ChoiceProperty('reverb_mode', offset + 0x01, ['Room', 'Hall', 'Plate', 'Tap delay'])

    def load_from_memory(self, memory):
        self.master_tune.load_from_memory(memory)
        self.reverb_mode.load_from_memory(memory)

    def write_to_memory(self, memory):
        self.master_tune.write_to_memory(memory)
        self.reverb_mode.write_to_memory(memory)

    def write_dict(self, parent):
        self.master_tune.write_dict(parent)
        self.reverb_mode.write_dict(parent)

    def load_dict(self, json):
        self.master_tune.load_dict(json)
        self.reverb_mode.load_dict(json)

