import kivy
kivy.require('1.10.1') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.slider import Slider
from kivy.uix.textinput import TextInput
from kivy.properties import NumericProperty

from mt_parameters import *


parameters = MtParameters()


def set_value_callback(parameter, instance, args):
    parameter.set_value(args)


class SliderTextBox(GridLayout):

    my_value = NumericProperty(0.)

    def __init__(self, parameter, **kwargs):
        super(SliderTextBox, self).__init__(**kwargs)
        self.cols = 2

        self.parameter = parameter

        self.slider = Slider(min=432.1, max=457.6, step=(457.6 - 432.1) / 128)
        self.add_widget(self.slider)

        self.text = TextInput(text='0', multiline=False)
        self.add_widget(self.text, index=1)

        self.slider.bind(value=self.on_slider_changed)
        self.bind(my_value=self.update_value)

        self.text.bind(on_text_validate=self.on_text_changed)
        self.bind(my_value=self.update_value)


    def on_slider_changed(self, instance, args):
        self.my_value = float(args)

    def on_text_changed(self, instance):
        self.my_value = float(instance.text)

    def update_value(self, instance, args):
        self.parameter.set_value(float(args))
        actual_value = self.parameter.value

        self.text.text = str(actual_value)
        self.slider.value = float(actual_value)




class SystemLayout(GridLayout):
    def __init__(self, **kwargs):
        super(SystemLayout, self).__init__(**kwargs)
        self.cols = 3

        self.add_widget(Label(text='Master Tune'))

        self.master_tune = SliderTextBox(parameter=parameters.system.master_tune)
        self.add_widget(self.master_tune)




class MT_100(App):


    def build(self):
        return SystemLayout()


if __name__ == '__main__':
    MT_100().run()

    result = {}
    parameters.write_dict(result)
    print(result)