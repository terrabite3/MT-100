#!/usr/bin/env python3

from sysex_memory import *
from json import JSONEncoder


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
        self.system = None
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


    def write_to_memory(self, memory):
        for x in range(20):
            if len(self.display) > x:
                memory[self.DISPLAY + x] = ord(self.display[x])
            else:
                memory[self.DISPLAY + x] = 0


    def __json__(self):
        result = {}
        
        if self.display:
            result['display'] = self.display

        return result

    def load_json(self, json):

        if 'display' in json:
            self.display = json['display']



class MtJsonEncoder(JSONEncoder):
    def default(self, obj):
        if hasattr(obj, '__json__'):
            return obj.__json__()
        return json.JSONEncoder.default(self, obj)

