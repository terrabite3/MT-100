#!/usr/bin/env python3

from sysex_memory import *
from json import JSONEncoder


class Property:
    def __init__(self, name, address):
        self.name = name
        self.address = address
        self.value = None

    def __json__(self, parent):
        if self.value:
            parent[self.name] = self.value

    def load_json(self, json):
        if self.name in json:
            self.value = json[self.name]

class ChoiceProperty(Property):
    def __init__(self, name, address, choices):
        Property.__init__(self, name, address)
        self.choices = choices
        print(hex(seven(self.address)))

    def load_from_memory(self, memory):
        print(hex(seven(self.address)))
        if self.address in memory:
            raw_value = memory[self.address]
            if raw_value >= len(self.choices) or raw_value < 0:
                raise RuntimeError('Invalid index {} while loading {} from memory.'.format(raw_value, self.name))
            self.value = self.choices[raw_value]

    def write_to_memory(self, memory):
        if self.value:
            try:
                index = self.choices.index(self.value)
                print(hex(seven(self.address)))
                print(index)
                memory[self.address] = index
            except ValueError as e:
                raise RuntimeError('Invalid choice {} while writing {} to memory.'.format(self.value, self.name))



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
        self.display = None


    def load_from_memory(self, memory):
        if self.DISPLAY in memory:
            name = ''
            for x in range(self.DISPLAY, self.DISPLAY + 20):
                if x in memory:
                    if memory[x] == 0:
                        break
                    name += chr(memory[x])
                else:
                    break
            self.display = name

        if self.SYSTEM_AREA in memory:
            self.system.load_from_memory(memory)


    def write_to_memory(self, memory):
        for x in range(20):
            if len(self.display) > x:
                memory[self.DISPLAY + x] = ord(self.display[x])
            else:
                memory[self.DISPLAY + x] = 0

        self.system.write_to_memory(memory)


    def __json__(self):
        result = {}
        
        if self.display:
            result['display'] = self.display

        result['system'] = self.system.__json__()

        return result

    def load_json(self, json):

        if 'display' in json:
            self.display = json['display']

        if 'system' in json:
            self.system.load_json(json['system'])


class System:

    MASTER_TUNE = 0x00
    MASTER_TUNE_MIN = 432.1
    MASTER_TUNE_MAX = 457.6
    

    def __init__(self, offset):
        self.offset = offset

        self.master_tune = None
        
        self.reverb_mode = ChoiceProperty('reverb_mode', 0x01, ['Room', 'Hall', 'Plate', 'Tap delay'])
        self.reverb_mode.address += offset

    def load_from_memory(self, memory):
        if self.offset + self.MASTER_TUNE in memory:
            raw_value = memory[self.offset + self.MASTER_TUNE]
            f_min = self.MASTER_TUNE_MIN
            f_max = self.MASTER_TUNE_MAX
            self.master_tune = f_min + (f_max - f_min) * (raw_value / 127)

        self.reverb_mode.load_from_memory(memory)

    def write_to_memory(self, memory):
        if self.master_tune:
            f_min = self.MASTER_TUNE_MIN
            f_max = self.MASTER_TUNE_MAX
            raw_value = round((self.master_tune - f_min) / (f_max - f_min) * 127)
            # Clamp
            raw_value = min(raw_value, 127)
            raw_value = max(raw_value, 0)
            memory[self.offset + self.MASTER_TUNE] = raw_value

        self.reverb_mode.write_to_memory(memory)


    def __json__(self):
        result = {}
        
        if self.master_tune:
            result['master_tune'] = self.master_tune

        self.reverb_mode.__json__(result)

        return result

    def load_json(self, json):
        if 'master_tune' in json:
            self.master_tune = json['master_tune']

        self.reverb_mode.load_json(json)



class MtJsonEncoder(JSONEncoder):
    def default(self, obj):
        if hasattr(obj, '__json__'):
            return obj.__json__()
        return json.JSONEncoder.default(self, obj)

