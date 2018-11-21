#!/usr/bin/env python3

from sysex_memory import *
from json import JSONEncoder
from math import ceil, log10

class Property:
    def __init__(self, name, address):
        self.name = name
        self.address = address
        self.value = None

    def write_dict(self, parent):
        if self.value != None:
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

class IntProperty(Property):
    # max is in terms of raw value, not offset value
    # If the property is from 1 to 8 corresponding to raw values 0 to 7, then max=7 and offset=1
    def __init__(self, name, address, max=127, offset=0):
        Property.__init__(self, name, address)
        self.max = max
        self.offset = offset

    def load_from_memory(self, memory):
        if self.address in memory:
            raw_value = memory[self.address]
            if raw_value > self.max:
                raise RuntimeError('Value too large {} while loading {} from memory.'.format(raw_value, self.name))
            self.value = raw_value + self.offset

    def write_to_memory(self, memory):
        if self.value != None:
            raw_value = self.value - self.offset
            if raw_value > self.max:
                raise RuntimeError('Value too large {} while writing {} to memory.'.format(raw_value, self.name))
            memory[self.address] = raw_value

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
            
            # Determine the number of digits needed to unambiguously define values
            delta_v = (self.float_max - self.float_min) / (self.raw_max - self.raw_min + 1)
            ndigits = ceil(-log10(delta_v))

            self.value = round(self.value, ndigits)
            
    def write_to_memory(self, memory):
        if self.value != None:
            raw_value = (self.value - self.float_min) / (self.float_max - self.float_min) * (self.raw_max - self.raw_min) + self.raw_min
            raw_value = round(raw_value)
            raw_value = min(raw_value, self.raw_max)
            raw_value = max(raw_value, self.raw_min)
            memory[self.address] = raw_value
        

class GroupProperty(Property):
    def __init__(self, name, address):
        Property.__init__(self, name, address)

    def properties(self):
        for key, value in self.__dict__.items():
            if isinstance(value, Property):
                yield value

    def load_from_memory(self, memory):
        for prop in self.properties():
            prop.load_from_memory(memory)

    def write_to_memory(self, memory):
        for prop in self.properties():
            prop.write_to_memory(memory)

    def write_dict(self, parent):
        if self.name in parent:
            my_dict = parent[self.name]
        else:
            my_dict = {}

        for prop in self.properties():
            prop.write_dict(my_dict)

        if my_dict:
            parent[self.name] = my_dict

    def load_dict(self, json):
        if self.name in json:
            for prop in self.properties():
                prop.load_dict(json[self.name])

class MtParameters(GroupProperty):
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
        self.system = System(self.SYSTEM_AREA)
        self.display = StringProperty('display', self.DISPLAY, 20)

    def write_dict(self, parent):
        for prop in self.properties():
            prop.write_dict(parent)

    def load_dict(self, json):
        for prop in self.properties():
            prop.load_dict(json)


class System(GroupProperty):

    def __init__(self, address):
        GroupProperty.__init__(self, 'system', address)

        self.master_tune = FloatProperty('master_tune', address + 0x00, 0, 127, 432.1, 457.6)
        self.reverb_mode = ChoiceProperty('reverb_mode', address + 0x01, ['Room', 'Hall', 'Plate', 'Tap delay'])
        self.reverb_time = IntProperty('reverb_time', address + 0x02, 7, 1)
        self.reverb_level = IntProperty('reverb_level', address + 0x03, 7)

        # TODO: Add partial reserves
        # TODO: Add MIDI channels

        self.master_volume = IntProperty('master_volume', address + 0x16, 100)



