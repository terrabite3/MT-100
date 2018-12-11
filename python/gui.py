import kivy
kivy.require('1.10.1')

from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.properties import ObjectProperty, NumericProperty
from kivy.uix.tabbedpanel import TabbedPanel
from kivy.uix.spinner import Spinner

import mt_parameters as mt

parameters = mt.MtParameters()

class ParamSpinner(Spinner):
    param = ObjectProperty(mt.ChoiceProperty('', 0, ['']), rebind=True)

class IntSliderTextBox(GridLayout):
    param = ObjectProperty(mt.IntProperty('', 0), rebind=True)
    value = NumericProperty()

class SystemLayout(GridLayout):
    params = ObjectProperty(mt.MtParameters(), rebind=True)

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