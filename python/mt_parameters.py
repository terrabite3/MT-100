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

    def set_value(self, value):
        self.value = value


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

    def set_value(self, value):
        value = min(value, self.offset + self.max)
        value = max(value, self.offset)
        self.value = value


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

    def set_value(self, value):
        value = min(value, self.float_max)
        value = max(value, self.float_min)
        self.value = value

        self.load_raw_value(self.get_raw_value())


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


class NoteProperty(ChoiceProperty):
    def __init__(self, name, address):
        notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

        pitches = []
        for octave in range(1, 9):
            for note in notes:
                pitches.append(note + str(octave))
        pitches.append('C9')

        ChoiceProperty.__init__(self, name, address, pitches)


class BiasPointDirProperty(ChoiceProperty):
    def __init__(self, name, address):
        notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

        pitches = []
        pitches.append('A1')
        pitches.append('A#1')
        pitches.append('B1')
        for octave in range(2, 7):
            for note in notes:
                pitches.append(note + str(octave))
        pitches.append('C7')

        biases = []
        for pitch in pitches:
            biases.append('<' + pitch)
        for pitch in pitches:
            biases.append('>' + pitch)

        if len(biases) != 128:
            raise RuntimeError('Bug in bias code: ' + str(biases))

        ChoiceProperty.__init__(self, name, address, biases)


class DummyProperty(Property):
    def __init__(self, address):
        Property.__init__(self, 'dummy', address)

    def write_dict(self, parent):
        pass

    def load_dict(self, json):
        pass

    def load_from_memory(self, memory):
        if self.address in memory:
            raw_value = memory[self.address]
            if raw_value != 0:
                raise RuntimeError('Unexpected value {} in dummy at address {}'.format(raw_value, self.address))

    def write_to_memory(self, memory):
        if self.value != None:
            memory[self.address] = 0

    


class GroupProperty(Property):
    def __init__(self, name, address):
        Property.__init__(self, name, address)

    def properties(self):
        for key, value in self.__dict__.items():
            if isinstance(value, Property):
                yield value

    def has_value(self):
        for prop in self.properties():
            if isinstance(prop, DummyProperty):
                continue
            elif isinstance(prop, GroupProperty):
                if prop.has_value():
                    return True
            else:
                if prop.value != None:
                    return True
        return False

    # Dummy properties should write 0 if anything else in this group is set
    def update_dummies(self):
        # First look for any dummy properties
        dummies = []
        for prop in self.properties():
            if isinstance(prop, DummyProperty):
                dummies.append(prop)

        something_set = self.has_value()
        for dummy in dummies:
            dummy.value = 0 if something_set else None



    def load_from_memory(self, memory):
        for prop in self.properties():
            prop.load_from_memory(memory)

    def write_to_memory(self, memory):
        self.update_dummies()

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
    def __init__(self, name, address, count, stride, child_type, start=1, child_args={}):
        GroupProperty.__init__(self, name, address)

        self.children = {}
        for index in range(count):
            name = str(index + start)
            addr = self.address + index * stride
            self.children[name] = child_type(name, addr, **child_args)

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
        self.patch_temp = ListProperty('patch_temp', self.PATCH_TEMP, 9, 0x10, PatchTemp)
        self.rhythm_setup = ListProperty('rhythm_setup', self.RHYTHM_SETUP, 64, 0x04, Rhythm, 24)
        self.timbre_temp = ListProperty('timbre_temp', self.TIMBRE_TEMP, 8, native(0x2_00), Timbre)
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
        self.partial_reserve = ListProperty('partial_reserve', address + 0x04, 9, 1, IntProperty, child_args={'max': 32})
        self.midi_channel = ListProperty('midi_channel', address + 0xD, 9, 1, ChoiceProperty, child_args={'choices': ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', 'OFF']})
        self.master_volume = IntProperty('master_volume', address + 0x16, 100)


class Patch(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        # Group A, Group B, Memory, Rhythm
        self.timbre_group = ChoiceProperty('timbre_group', address + 0x00, ['a', 'b', 'i', 'r'])
        self.timbre_number = IntProperty('timbre_number', address + 0x01, 63)
        self.key_shift = IntProperty('key_shift', address + 0x02, 48, -24)
        self.fine_tune = IntProperty('fine_tune', address + 0x03, 100, -50)
        self.bender_range = IntProperty('bender_range', address + 0x04, 24)
        self.assign_mode = ChoiceProperty('assign_mode', address + 0x05, ['POLY 1', 'POLY 2', 'POLY 3', 'POLY 4'])
        self.reverb_switch = ChoiceProperty('reverb_switch', address + 0x06, ['OFF', 'ON'])
        self.dummy = DummyProperty(address + 0x07)


class Timbre(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        self.common_param = TimbreCommonParam(address + 0x00)
        self.partial_param_1 = PartialParam('partial_parameter_1', address + 0x0E)
        self.partial_param_2 = PartialParam('partial_parameter_2', address + 0x48)
        self.partial_param_3 = PartialParam('partial_parameter_3', address + native(0x1_02))
        self.partial_param_4 = PartialParam('partial_parameter_4', address + native(0x1_3C))
        self.dummy6 = DummyProperty(address + native(0x1_76))
        self.dummy7 = DummyProperty(address + native(0x1_77))
        self.dummy8 = DummyProperty(address + native(0x1_78))
        self.dummy9 = DummyProperty(address + native(0x1_79))
        self.dummyA = DummyProperty(address + native(0x1_7A))
        self.dummyB = DummyProperty(address + native(0x1_7B))
        self.dummyC = DummyProperty(address + native(0x1_7C))
        self.dummyD = DummyProperty(address + native(0x1_7D))
        self.dummyE = DummyProperty(address + native(0x1_7E))
        self.dummyF = DummyProperty(address + native(0x1_7F))


class TimbreCommonParam(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'common_parameter', address)

        self.name_param = StringProperty('name', address + 0x00, 10)
        self.structure_1_2 = IntProperty('structure_1_2', address + 0xA, 12, 1)
        self.structure_3_4 = IntProperty('structure_3_4', address + 0xB, 12, 1)
        self.partial_mute = BitfieldProperty('partial_mute', address + 0xC, 4)
        self.envelope_mode = ChoiceProperty('envelope_mode', address + 0xD, ['Normal', 'No sustain'])

class PartialParam(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        self.wave_generator = WaveGenerator(address + 0x00)
        self.pitch = PartialPitch(address + 0x08)
        self.tvf = TVF(address + 0x17)
        self.tva = TVA(address + 0x29)


class WaveGenerator(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'wave_generator', address)

        self.pitch_coarse = NoteProperty('pitch_coarse', address + 0x00)
        self.pitch_fine = IntProperty('pitch_fine', address + 0x01, 100, -50)
        self.pitch_keyfollow = ChoiceProperty('pitch_keyfollow', address + 0x02, ['-1', '-1/2', '-1/4', '0', '1/8', '1/4', '3/8', '1/2', '5/8', '3/4', '7/8', '1', '5/4', '3/2', '2', 's1', 's2'])
        self.pitch_bender_sw = ChoiceProperty('pitch_bender_sw', address + 0x03, ['OFF', 'ON'])
        self.waveform = ChoiceProperty('waveform', address + 0x04, ['SQU', 'SAW'])
        self.pcm_wave_number = IntProperty('pcm_wave_number', address + 0x05, 127, 1)
        self.pulse_width = IntProperty('pulse_width', address + 0x06, 100)
        self.pulse_width_velo_sens = IntProperty('pulse_width_velo_sens', address + 0x07, 14, -7)


class PartialPitch(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'pitch', address)

        self.envelope = PitchEnvelope(self.address + 0x0)
        self.lfo = PitchLFO(self.address + 0xC)

class PitchEnvelope(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'envelope', address)

        self.depth = IntProperty('depth', address + 0x0, 10)
        self.velo_sens = IntProperty('velo_sens', address + 0x1, 100)
        self.time_keyfollow = IntProperty('time_keyfollow', address + 0x2, 4)
        self.time_1 = IntProperty('time_1', address + 0x3, 100)
        self.time_2 = IntProperty('time_2', address + 0x4, 100)
        self.time_3 = IntProperty('time_3', address + 0x5, 100)
        self.time_4 = IntProperty('time_4', address + 0x6, 100)
        self.level_0 = IntProperty('level_0', address + 0x7, 100, -50)
        self.level_1 = IntProperty('level_1', address + 0x8, 100, -50)
        self.level_2 = IntProperty('level_2', address + 0x9, 100, -50)
        self.level_sustain = IntProperty('level_sustain', address + 0xA, 100, -50)
        self.level_end = IntProperty('level_end', address + 0xB, 100, -50)
        
class PitchLFO(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'lfo', address)

        self.rate = IntProperty('rate', address + 0x0, 100)
        self.depth = IntProperty('depth', address + 0x1, 100)
        self.mod_sens = IntProperty('mod_sens', address + 0x2, 100)


class TVF(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'time_variant_filter', address)

        self.cutoff_freq = IntProperty('cutoff_freq', address + 0x0, 100)
        self.resonance = IntProperty('resonance', address + 0x1, 30)
        self.keyfollow = ChoiceProperty('keyfollow', address + 0x2, ['-1', '-1/2', '-1/4', '0', '1/8', '1/4', '3/8', '1/2', '5/8', '3/4', '7/8', '1', '5/4', '3/2', '2'])
        self.bias_point_dir = BiasPointDirProperty('bias_point_dir', address + 0x3)
        self.bias_level = IntProperty('bias_level', address + 0x4, 14, -7)
        self.envelope = TVFEnvelope(address + 0x5)
        
class TVFEnvelope(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'envelope', address)

        self.depth = IntProperty('depth', address + 0x0, 100)
        self.velo_sens = IntProperty('velo_sens', address + 0x1, 100)
        self.depth_keyfollow = IntProperty('depth_keyfollow', address + 0x2, 4)
        self.time_keyfollow = IntProperty('time_keyfollow', address + 0x3, 4)
        self.time_1 = IntProperty('time_1', address + 0x4, 100)
        self.time_2 = IntProperty('time_2', address + 0x5, 100)
        self.time_3 = IntProperty('time_3', address + 0x6, 100)
        self.time_4 = IntProperty('time_4', address + 0x7, 100)
        self.time_5 = IntProperty('time_5', address + 0x8, 100)
        self.level_1 = IntProperty('level_1', address + 0x9, 100)
        self.level_2 = IntProperty('level_2', address + 0xA, 100)
        self.level_3 = IntProperty('level_3', address + 0xB, 100)
        self.level_sustain = IntProperty('level_sustain', address + 0xC, 100)

        
class TVA(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'time_variant_amplifier', address)

        self.level = IntProperty('level', address + 0x0, 100)
        self.velo_sens = IntProperty('velo_sens', address + 0x1, 100, -50)
        self.bias_point_1 = BiasPointDirProperty('bias_point_1', address + 0x2)
        self.bias_level_1 = IntProperty('bias_level_1', address + 0x3, 12, -12)
        self.bias_point_2 = BiasPointDirProperty('bias_point_2', address + 0x4)
        self.bias_level_2 = IntProperty('bias_level_2', address + 0x5, 12, -12)
        self.envelope = TVAEnvelope(address + 0x6)
        
class TVAEnvelope(GroupProperty):
    def __init__(self, address):
        GroupProperty.__init__(self, 'envelope', address)

        self.time_keyfollow = IntProperty('time_keyfollow', address + 0x0, 4)
        self.time_v_follow = IntProperty('time_v_follow', address + 0x1, 4)
        self.time_1 = IntProperty('time_1', address + 0x2, 100)
        self.time_2 = IntProperty('time_2', address + 0x3, 100)
        self.time_3 = IntProperty('time_3', address + 0x4, 100)
        self.time_4 = IntProperty('time_4', address + 0x5, 100)
        self.time_5 = IntProperty('time_5', address + 0x6, 100)
        self.level_1 = IntProperty('level_1', address + 0x7, 100)
        self.level_2 = IntProperty('level_2', address + 0x8, 100)
        self.level_3 = IntProperty('level_3', address + 0x9, 100)
        self.level_sustain = IntProperty('level_sustain', address + 0xA, 100)


class Rhythm(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        self.timbre = TimbreReference(address + 0x0)
        self.output_level = IntProperty('output_level', address + 0x1, 100)
        self.panpot = IntProperty('panpot', address + 0x2, 14)
        self.reverb_switch = ChoiceProperty('reverb_switch', address + 0x3, ['OFF', 'ON'])


class TimbreReference(Property):
    def __init__(self, address):
        Property.__init__(self, 'timbre', address)

    def load_raw_value(self, raw_value):
        if raw_value < 64:
            self.value = 'i' + str(raw_value + 1)
            pass
        elif raw_value < 128:
            self.value = 'r' + str(raw_value - 63)
            pass
        else:
            raise RuntimeError('Value too large {} while loading {} from memory.'.format(raw_value, self.name))

    def get_raw_value(self):
        if self.value == None:
            return None

        if self.value.startswith('i'):
            raw_value = int(self.value[1:]) - 1
        elif self.value.startswith('r'):
            raw_value = int(self.value[1:]) + 63
        else:
            raise RuntimeError('Invalid value {} while writing {} to memory.'.format(raw_value, self.name))

        if raw_value < 0 or raw_value >= 128:
            raise RuntimeError('Invalid value {} while writing {} to memory.'.format(raw_value, self.name))
        return raw_value

class PatchTemp(GroupProperty):
    def __init__(self, name, address):
        GroupProperty.__init__(self, name, address)

        self.timbre_group = ChoiceProperty('timbre_group', address + 0x00, ['a', 'b', 'i', 'r'])
        self.timbre_number = IntProperty('timbre_number', address + 0x01, 63)
        self.key_shift = IntProperty('key_shift', address + 0x02, 48, -24)
        self.fine_tune = IntProperty('fine_tune', address + 0x03, 100, -50)
        self.bender_range = IntProperty('bender_range', address + 0x04, 24)
        self.assign_mode = ChoiceProperty('assign_mode', address + 0x05, ['POLY 1', 'POLY 2', 'POLY 3', 'POLY 4'])
        self.reverb_switch = ChoiceProperty('reverb_switch', address + 0x06, ['OFF', 'ON'])
        self.dummy7 = DummyProperty(address + 0x7)
        self.output_level = IntProperty('output_level', address + 0x08, 100)
        self.panpot = IntProperty('panpot', address + 0x09, 14)
        self.dummyA = DummyProperty(address + 0xA)
        self.dummyB = DummyProperty(address + 0xB)
        self.dummyC = DummyProperty(address + 0xC)
        self.dummyD = DummyProperty(address + 0xD)
        self.dummyE = DummyProperty(address + 0xE)
        self.dummyF = DummyProperty(address + 0xF)

