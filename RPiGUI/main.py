#with base from https://github.com/mrichardson23/rpi-kivy-screen

import os
os.environ['KIVY_GL_BACKEND'] = 'gl'
import kivy
#kivy.require('1.11.0rc1') # replace with your current kivy version !

from kivy.app import App
from kivy.core.window import Window
from kivy.uix.button import Button
from kivy.uix.togglebutton import ToggleButton
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
from kivy.graphics import Color, Rectangle
from kivy.uix.checkbox import CheckBox

import RPi.GPIO as GPIO


# Set up GPIO:
ledPinGreen = 23
ledPinBlue = 12
ledPinRed = 4
GPIO.setmode(GPIO.BCM)

GPIO.setup(ledPinGreen, GPIO.OUT)
GPIO.output(ledPinGreen, GPIO.LOW)
GPIO.setup(ledPinBlue, GPIO.OUT)
GPIO.output(ledPinBlue, GPIO.LOW)
GPIO.setup(ledPinRed, GPIO.OUT)
GPIO.output(ledPinRed, GPIO.LOW)

# event when green is chosen
def green_on(checkbox, value):
        if value:
                GPIO.output(ledPinBlue, GPIO.LOW)
                GPIO.output(ledPinRed, GPIO.LOW)
                GPIO.output(ledPinGreen, GPIO.HIGH)
                print('The green led is lit')

# event when blue is chosen
def blue_on(checkbox, value):
        if value:
                GPIO.output(ledPinGreen, GPIO.LOW)
                GPIO.output(ledPinRed, GPIO.LOW)
                GPIO.output(ledPinBlue, GPIO.HIGH)
                print('The blue led is lit')

# event when red is chose
def white_on(checkbox, value):
        if value:
                GPIO.output(ledPinGreen, GPIO.LOW)
                GPIO.output(ledPinBlue, GPIO.LOW)
                GPIO.output(ledPinRed, GPIO.HIGH)
                print('The red led is lit')

# event when close button is chosen
# all led lights will be turned off
def close_func(obj):
	GPIO.output(ledPinGreen, GPIO.LOW)
	GPIO.output(ledPinBlue, GPIO.LOW)
	GPIO.output(ledPinRed, GPIO.LOW)
	App.get_running_app().stop()
	Window.close()


class MyApp(App):

	def build(self):
		# Setting up the layout
		layout = GridLayout(cols=2, spacing=30, padding=30, row_default_height=150)


		# Create the Radio buttons and labels

		outputContGreen = CheckBox(group='led')
		outputContGreen.bind(active=green_on)
		outputContBlue = CheckBox(group='led')
		outputContBlue.bind(active=blue_on)
		outputContRed = CheckBox(group='led')
		outputContRed.bind(active=white_on)
		closeBtn = Button(text='Close')
		closeBtn.bind(on_press=close_func)


		# Add the UI elements to the layout
		layout.add_widget(Label(text='Close button here ---->'))
		layout.add_widget(closeBtn)
		layout.add_widget(outputContGreen)
		layout.add_widget(Label(text='Green'))
		layout.add_widget(outputContBlue)
		layout.add_widget(Label(text='Blue'))
		layout.add_widget(outputContRed)
		layout.add_widget(Label(text='Red'))


		return layout

if __name__ == '__main__':
	MyApp().run()
