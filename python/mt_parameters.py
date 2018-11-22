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

    def load_from_memory(self, memory):
        if self.address in memory:
            raw_value = memory[self.address]
            self.load_raw_value(raw_value)

    def write_to_memory(self, memory):
        raw_value = self.get_raw_value()
        if raw_value != None:
            memory[self.address] = raw_value

class ChoiceProperty(Property):
    def __init__(self, name, address, choices):
        Property.__init__(self, name, address)
        self.choices = choices

    def load_raw_value(self, raw_value):
        if raw_value >= len(self.choices) or raw_value < 0:
            raise RuntimeError('Invalid index {} while loading {} from memory.'.format(raw_value, self.name))
        self.value = self.choices[raw_value]
        
    def get_raw_value(self):
        if self.value == None:
            return None
        try:
            return self.choices.index(self.value)
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

    def load_raw_value(self, raw_value):
        if raw_value > self.max:
            raise RuntimeError('Value too large {} while loading {} from memory.'.format(raw_value, self.name))
        self.value = raw_value + self.offset

    def get_raw_value(self):
        if self.value == None:
            return None
        raw_value = self.value - self.offset
        if raw_value > self.max:
            raise RuntimeError('Value too large {} while writing {} to memory.'.format(raw_value, self.name))
        return raw_value


class FloatProperty(Property):
    def __init__(self, name, address, raw_min, raw_max, float_min, float_max):
        Property.__init__(self, name, address)
        self.raw_min = raw_min
        self.raw_max = raw_max
        self.float_min = float_min
        self.float_max = float_max

    def load_raw_value(self, raw_value):
        if raw_value < self.raw_min or raw_value > self.raw_max:
            raise RuntimeError('Invalid raw value {} while loading {} from memory.'.format(raw_value, self.name))
        self.value = self.float_min + (self.float_max - self.float_min) * ((raw_value - self.raw_min) / (self.raw_max - self.raw_min))
        
        # Determine the number of digits needed to unambiguously define values
        delta_v = (self.float_max - self.float_min) / (self.raw_max - self.raw_min + 1)
        ndigits = ceil(-log10(delta_v))

        self.value = round(self.value, ndigits)

    def get_raw_value(self):
        if self.value == None:
            return None
        raw_value = (self.value - self.float_min) / (self.float_max - self.float_min) * (self.raw_max - self.raw_min) + self.raw_min
        raw_value = round(raw_value)
        raw_value = min(raw_value, self.raw_max)
        raw_value = max(raw_value, self.raw_min)
        return raw_value

        

class BitfieldProperty(Property):
    def __init__(self, name, address, bits):
        Property.__init__(self, name, address)
        self.bits = bits

    def load_raw_value(self, raw_value):
        if raw_value >= 1 << self.bits:
            raise RuntimeError('Invalid valid {} while reading {}.'.format(self.value, self.name))
        self.value = ('{0:0' + str(self.bits) + 'b}').format(raw_value)

    def get_raw_value(self):
        if self.value == None:
            return None
        if len(self.value) != self.bits:
            raise RuntimeError('Invalid value {} while writing {}'.format(self.value, self.name))

        return int(self.value, base=2)


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


class ListProperty(GroupProperty):
    def __init__(self, name, address, count, stride, child_type):
        GroupProperty.__init__(self, name, address)

        self.children = {}
        for index in range(count):
            name = str(index + 1)
            addr = self.address + index * stride
            self.children[name] = child_type(name, addr)

    def properties(self):
        for key, child in self.children.items():
            yield child

class MtParameters(GroupProperty):
    CHANNEL_TIMBRE_TEMP =   native(0x02_00_00)
    PATCH_TEMP =            native(0x03_00_00)
    RHYTHM_SETUP =          native(0x03_01_10)
    TIMBRE_TEMP =           native(0x04_00_00)
    PATCH_MEMORY =          native(0x05_00_00)
    TIMBRE_MEMORY =         native(0x08_00_00)
    SYSTEM_AREA =           native(0x10_00_00)
    DISPLAY =               native(0x20_00_00)
    WRITE_REQUEST =         native(0x40_00_00)

    def __init__(self):
        self.patch_memory = ListProperty('patch_memory', self.PATCH_MEMORY, 128, 0x08, Patch)
        self.timbre_memory = ListProperty('timbre_memory', self.TIMBRE_MEMORY, 64, native(0x2_00), Timbre)
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


class Patch(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        self.timbre_group = ChoiceProperty('timbre_group', address + 0x00, ['a', 'b', 'i', 'r'])
        self.timbre_number = IntProperty('timbre_number', address + 0x01, 63)
        self.key_shift = IntProperty('key_shift', address + 0x02, 48, -24)
        self.fine_tune = IntProperty('fine_tune', address + 0x03, 100, -50)
        self.bender_range = IntProperty('bender_range', address + 0x04, 24)
        self.assign_mode = ChoiceProperty('assign_mode', address + 0x05, ['POLY 1', 'POLY 2', 'POLY 3', 'POLY 4'])
        self.reverb_switch = ChoiceProperty('reverb_switch', address + 0x06, ['OFF', 'ON'])


class Timbre(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        self.common_param = TimbreCommonParam(address + 0x00)
        # self.partial_param_1 = PartialParameter('partial_parameter_1', address + 0x0E)
        # self.partial_param_2 = PartialParameter('partial_parameter_2', address + 0x48)
        # self.partial_param_3 = PartialParameter('partial_parameter_3', address + native(0x1_02))
        # self.partial_param_4 = PartialParameter('partial_parameter_4', address + native(0x1_3C))


class TimbreCommonParam(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'common_parameter', address)

        self.name_param = StringProperty('name', address + 0x00, 10)
        self.structure_1_2 = IntProperty('structure_partial_1_2', address + 0xA, 12, 1)
        self.structure_3_4 = IntProperty('structure_partial_3_4', address + 0xB, 12, 1)
        self.partial_mute = BitfieldProperty('partial_mute', address + 0xC, 4)
        self.envelope_mode = ChoiceProperty('envelope_mode', address + 0xD, ['Normal', 'No sustain'])

# class TimbrePartialParam(GroupProperty):
#     def __init__(self, name, address):
#         GroupProperty.__init__(self, name, address)