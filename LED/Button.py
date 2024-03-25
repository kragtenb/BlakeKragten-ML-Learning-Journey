from gpiozero import Button
from time import sleep

button = Button(2)

button.wait_for_press()

print("Button pressed")