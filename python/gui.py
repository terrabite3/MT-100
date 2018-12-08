import kivy
kivy.require('1.10.1')

from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.properties import ObjectProperty

import mt_parameters as mt

parameters = mt.MtParameters()



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