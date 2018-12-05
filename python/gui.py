import kivy
kivy.require('1.10.1') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.slider import Slider
from kivy.uix.textinput import TextInput
from kivy.uix.dropdown import DropDown
from kivy.uix.button import Button
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

        if isinstance(parameter, FloatProperty):
            self.mode = 'float'
            min_val = self.parameter.float_min
            max_val = self.parameter.float_max
            step = (max_val - min_val) / (self.parameter.raw_max - self.parameter.raw_min + 1)
        elif isinstance(parameter, IntProperty):
            self.mode = 'int'
            min_val = parameter.offset
            max_val = parameter.offset + parameter.max
            step = 1

        self.slider = Slider(min=min_val, max=max_val, step=step)
        self.add_widget(self.slider)

        self.text = TextInput(text=str(min_val), multiline=False)
        self.add_widget(self.text)

        self.slider.bind(value=self.on_slider_changed)
        self.bind(my_value=self.update_value)

        self.text.bind(on_text_validate=self.on_text_changed)
        self.bind(my_value=self.update_value)


    def on_slider_changed(self, instance, args):
        self.my_value = args

    def on_text_changed(self, instance):
        if self.mode == 'float':
            self.my_value = float(instance.text)
        elif self.mode == 'int':
            self.my_value = int(instance.text)

    def update_value(self, instance, args):
        if self.mode == 'float':
            self.parameter.set_value(float(args))
        elif self.mode == 'int':
            self.parameter.set_value(int(args))
        actual_value = self.parameter.value

        self.text.text = str(actual_value)
        self.slider.value = float(actual_value)


class ChoiceWidget(GridLayout):
    def __init__(self, parameter, **kwargs):
        super(ChoiceWidget, self).__init__(**kwargs)
        self.cols = 1

        self.parameter = parameter

        self.dropdown = DropDown()

        for choice in self.parameter.choices:
            btn = Button(text=choice, size_hint_y=None, height=30)
            btn.bind(on_release=lambda btn: self.dropdown.select(btn.text))
            self.dropdown.add_widget(btn)

        self.mainbutton = Button(text=self.parameter.choices[0])
        self.mainbutton.bind(on_release=self.dropdown.open)

        self.dropdown.bind(on_select=self.option_selected)

        self.add_widget(self.mainbutton)

    def option_selected(self, instance, value):
        self.mainbutton.text = value
        self.parameter.set_value(value)



class SystemLayout(GridLayout):
    def __init__(self, **kwargs):
        super(SystemLayout, self).__init__(**kwargs)
        self.cols = 2

        self.add_widget(Label(text='Master Tune'))
        self.add_widget(SliderTextBox(parameter=parameters.system.master_tune))

        self.add_widget(Label(text='Reverb Mode'))
        self.add_widget(ChoiceWidget(parameter=parameters.system.reverb_mode))
        
        self.add_widget(Label(text='Reverb Time'))
        self.add_widget(SliderTextBox(parameter=parameters.system.reverb_time))


        self.add_widget(Label(text=''))

class MT_100(App):


    def build(self):
        return SystemLayout()


if __name__ == '__main__':
    MT_100().run()

    result = {}
    parameters.write_dict(result)
    print(result)