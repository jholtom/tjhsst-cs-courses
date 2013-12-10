#!/usr/bin/python
#RPI Visualizer - LEDS AND GPIO - Jacob Holtom and Anya Owsenek
import RPi.GPIO as gpio
import time
# HERE WE INITIALIZE SOME PINS
gpio.setmode(gpio.BCM) #THIS LAYOUT MAKES SO MUCH MORE SENSE - I CAN COUNT PINS
x = [4,9,10,11,17,18,22,23,24,25] # THESE ARE THE PINS WE CAN LIGHT UP AND STUFF
#INITIALIZE ALL OF THEM AS OUTPUTS
for i in x:
    gpio.setup(i,gpio.OUT)

#BLACK MAGIC TO PROCESS AUDIO GOES HERE

#CYCLE THROUGH ALL THE PINS AND TURN THEM ON AND OFF AFTER PAUSING FOR A SECOND
print "Activating " + len(x) + " LED'S"
for i in x:
    gpio.output(i,True)
    time.sleep(1)
    gpio.output(i,False)

# SHUT THIS THING DOWN
gpio.cleanup()
