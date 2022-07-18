# -*- coding: utf-8 -*-
"""
Created on Fri Jul 15 15:40:46 2022

@author: ben
"""
from kivy.app import App
#https://stackoverflow.com/questions/36869914/how-to-add-scrolling-text-widget-in-kivy
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.button import Button
from kivy.uix.widget import Widget
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.scrollview import ScrollView
import warnings
import string
from kivy.base import runTouchApp
from kivy.lang import Builder
from kivy.properties import StringProperty
from kivy.uix.relativelayout import RelativeLayout
from kivy.uix.boxlayout import BoxLayout


# To change the kivy default settings
# we use this module config
from kivy.config import Config
     
# 0 being off 1 being on as in true / false
# you can use 0 or 1 && True or False
Config.set('graphics', 'resizable', True)

import serial
import time # Optional (required if using time.sleep() below)
from threading import Thread



Builder.load_string('''
<ScrolllabelLabel>:
    Label:
        text: root.text
        font_size: 10
        text_size: self.width, None
        size_hint_y: None
        height: self.texture_size[1]
''')

class ScrolllabelLabel(ScrollView):
    text = StringProperty('')
class h_bridge(App):
    def build(self):
        self.title = "H-Bridge Control"
        grid = BoxLayout(orientation = 'vertical')
        sub_grid = GridLayout(cols=1, size_hint_y=2)
        sub_grid_2 = GridLayout(cols = 1, size_hint_y = 2)
        
        #LR, RL subgrid
        operation_sub_grid = GridLayout(cols = 2, size_hint_y = 1)
        
        main_grid = GridLayout(cols=3, size_hint_y=2)
        self.lbl0 = Label(text='Enter Command Below:')
        sub_grid.add_widget(self.lbl0)
        
        self.txt1 = TextInput(text='', multiline=True)
        sub_grid.add_widget(self.txt1)

        self.lbl1 = ScrolllabelLabel(text='Console: \n')
        sub_grid.add_widget(self.lbl1)
        
        btn1 = Button(text='Send Command')
        
        
        btn1.bind(on_press=self.write_console)
        sub_grid.add_widget(btn1) 
        
        main_grid.add_widget(sub_grid)
        
        self.on_time_lbl = Label(text = 'On Time:') 
        self.on_time_txt = TextInput(text='')
        
        self.off_time_lbl = Label(text = 'Off Time: ')
        self.off_time_txt = TextInput(text='')
        
        #alternate grid
        alternate_grid = GridLayout(cols = 1, size_hint_y=1)

        self.on_time_lr_lbl = Label(text = 'On Time LR:') 
        self.on_time_lr_txt = TextInput(text='')
        self.off_time_lr_lbl = Label(text = 'Off Time LR:') 
        self.off_time_lr_txt = TextInput(text='')
        self.on_time_rl_lbl = Label(text = 'On Time RL:') 
        self.on_time_rl_txt = TextInput(text='')
        self.off_time_rl_lbl = Label(text = 'Off Time RL:') 
        self.off_time_rl_txt = TextInput(text='')

        alt_btn = Button(text='Send Alternate Command')
        alt_btn.bind(on_press=self.write_alt)

        alternate_grid.add_widget(self.on_time_lr_lbl)
        alternate_grid.add_widget(self.on_time_lr_txt)
        alternate_grid.add_widget(self.off_time_lr_lbl)
        alternate_grid.add_widget(self.off_time_lr_txt)
        alternate_grid.add_widget(self.on_time_rl_lbl)
        alternate_grid.add_widget(self.on_time_rl_txt)
        alternate_grid.add_widget(self.off_time_rl_lbl)
        alternate_grid.add_widget(self.off_time_rl_txt)
        alternate_grid.add_widget(alt_btn)
        

        #operation grid
        lr_btn = Button(text = 'LR')
        lr_btn.bind(on_press=self.write_lr)
        rl_btn = Button(text = 'RL')
        rl_btn.bind(on_press=self.write_rl)
        
        operation_sub_grid.add_widget(lr_btn)
        operation_sub_grid.add_widget(rl_btn)
        
        sub_grid_2.add_widget(self.on_time_lbl)
        sub_grid_2.add_widget(self.on_time_txt)
        sub_grid_2.add_widget(self.off_time_lbl)
        sub_grid_2.add_widget(self.off_time_txt)
        sub_grid_2.add_widget(operation_sub_grid)
        
        main_grid.add_widget(sub_grid_2)
        main_grid.add_widget(alternate_grid)

        grid.add_widget(main_grid)
        
        return grid
    
    def mirror(self, userInput):
        self.lbl1.text = self.txt1.text
    def write_console(self, userInput):
        prefix = self.txt1.text[:3]
        if(prefix == "COM"):
            try:
                input_port = "COM" + self.txt1.text[4:]
                self.arduino = serial.Serial(port=input_port, baudrate=9600)
                success_txt = "Successfully connected to COM " + self.txt1.text[4:] + "\n"
                read_console_thread = Thread(target = self.read_console)
                read_console_thread.start()
            except:
                success_txt = "Error connecting to COM " + self.txt1.text[4:] + "\n"
            self.lbl1.text = self.lbl1.text + success_txt
        text_write = bytes(self.txt1.text, 'utf-8')
        self.arduino.write(text_write)
    def write_lr(self, userInput):
        modified_text = "LR " + self.on_time_txt.text + "," + self.off_time_txt.text
        text_write = bytes(modified_text, 'utf-8')
        self.arduino.write(text_write)
    def write_alt(self, userInput):
        modified_text = "ALT " + self.on_time_lr_txt.text + "," + self.off_time_lr_txt.text + "q" + self.on_time_rl_txt.text + "w" + self.off_time_rl_txt.text
        text_write = bytes(modified_text, 'utf-8')
        self.arduino.write(text_write)
    def write_rl(self, userInput):
        modified_text = "RL " + self.on_time_txt.text + "," + self.off_time_txt.text
        text_write = bytes(modified_text, 'utf-8')
        self.arduino.write(text_write)
    def read_console(self):
        while True:
            if (self.arduino.inWaiting() > 0):
                data_str = self.arduino.read(self.arduino.inWaiting()).decode('ascii') 
                self.lbl1.text = self.lbl1.text + data_str
        
            # Put the rest of your code you want here
            
            # Optional, but recommended: sleep 10 ms (0.01 sec) once per loop to let 
            # other threads on your PC run during this time. 
            time.sleep(0.10) 

if __name__ == '__main__':
	h_bridge().run()

