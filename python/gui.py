import kivy
kivy.require('1.10.1')

from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.properties import ObjectProperty, NumericProperty
from kivy.uix.tabbedpanel import TabbedPanel
from kivy.uix.spinner import Spinner

import mt_parameters as mt
from sysex_memory import *

import sys
import os

parameters = mt.MtParameters()

if len(sys.argv) > 1:
    in_file = sys.argv[1]
    in_extension = os.path.splitext(in_file)[1].lower()
    
    memory = SysExMemory()

    if in_extension == '.json':
        with open(in_file, 'r') as json_file:
            in_dict = json.load(json_file)

        parameters.load_dict(in_dict)


    elif in_extension == '.syx':
        memory.read_syx(in_file)
        parameters.load_from_memory(memory.memory)


    elif in_extension == '.mem':
        memory.read_memory(in_file)
        parameters.load_from_memory(memory.memory)

class ParamSpinner(Spinner):
    param = ObjectProperty(mt.ChoiceProperty('', 0, ['']), rebind=True)

class IntSliderTextBox(GridLayout):
    param = ObjectProperty(mt.IntProperty('', 0), rebind=True)
    value = NumericProperty()

class ParamTextInput(TextInput):
    param = ObjectProperty

class SystemLayout(GridLayout):
    params = ObjectProperty(mt.MtParameters(), rebind=True)

class PitchEnvelope(GridLayout):
    params = ObjectProperty(mt.PitchEnvelope(0), rebind=True)

# class TimbreLayout(GridLayout):
#     params = ObjectProperty(mt.MtParameters(), rebind=True)

class MainLayout(TabbedPanel):
    params = ObjectProperty()

class MTApp(App):


    def build(self):
        return MainLayout(params=parameters)


if __name__ == '__main__':
    MTApp().run()

    result = {}
    parameters.write_dict(result)
    print(result)