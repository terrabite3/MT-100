import kivy
kivy.require('1.10.1')

from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.slider import Slider
from kivy.uix.textinput import TextInput
from kivy.uix.dropdown import DropDown
from kivy.uix.button import Button
from kivy.properties import NumericProperty
from kivy.properties import ObjectProperty
from kivy.properties import StringProperty
from kivy.uix.widget import Widget

import mt_parameters as mt


parameters = mt.MtParameters()


class SliderTextBox(GridLayout):

    my_value = NumericProperty(0.)
    param = ObjectProperty()

    def __init__(self, **kwargs):
        super(SliderTextBox, self).__init__(**kwargs)
        self.cols = 2

        self.bind(param=self.populate)


    def populate(self, inst, args):
        if isinstance(self.param, mt.FloatProperty):
            self.mode = 'float'
            min_val = self.param.float_min
            max_val = self.param.float_max
            step = (max_val - min_val) / (self.param.raw_max - self.param.raw_min + 1)
        elif isinstance(self.param, mt.IntProperty):
            self.mode = 'int'
            min_val = self.param.offset
            max_val = self.param.offset + self.param.max
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
            self.param.set_value(float(args))
        elif self.mode == 'int':
            self.param.set_value(int(args))
        actual_value = self.param.value

        self.text.text = str(actual_value)
        self.slider.value = float(actual_value)


class ChoiceWidget(GridLayout):

    param = ObjectProperty()

    def __init__(self, **kwargs):
        super(ChoiceWidget, self).__init__(**kwargs)
        self.cols = 1

        self.bind(param=self.populate)

    def populate(self, inst, args):

        self.dropdown = DropDown()

        for choice in self.param.choices:
            btn = Button(text=choice, size_hint_y=None, height=30)
            btn.bind(on_release=lambda btn: self.dropdown.select(btn.text))
            self.dropdown.add_widget(btn)

        self.mainbutton = Button(text=self.param.choices[0])
        self.mainbutton.bind(on_release=self.dropdown.open)

        self.dropdown.bind(on_select=self.option_selected)

        self.add_widget(self.mainbutton)

    def option_selected(self, instance, value):
        self.mainbutton.text = value
        self.param.set_value(value)



class SystemLayout(GridLayout):
    params = ObjectProperty()

class MTApp(App):


    def build(self):
        return SystemLayout(params=parameters)


if __name__ == '__main__':
    MTApp().run()

    result = {}
    parameters.write_dict(result)
    print(result)