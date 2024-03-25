import pygame
from motor import Motor
from pygame.locals import (
    QUIT,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    KEYDOWN,
)

from gpiozero import Button
from picamera2 import Picamera2, Preview
from datetime import datetime
from signal import pause

camera = Picamera2()
camera_config = camera.create_still_configuration(main={"size": (1920, 1080)}, lores={"size": (640, 480)}, display="lores")
camera.configure(camera_config)
camera.start_preview(Preview.QTGL)
camera.start()

pygame.init()
window = pygame.display.set_mode((100, 100))
running = True
motor = Motor()
speed = 0
turning = 0
max_speed = 100
max_turning = 100

while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            motor.move(0, 0)
            running = False

    keys_pressed = pygame.key.get_pressed()

    if (not (keys_pressed[K_UP] ^ keys_pressed[K_DOWN]) or (keys_pressed[K_UP] and keys_pressed[K_DOWN])):
        speed = 0
    elif (keys_pressed[K_UP]):
        speed = max_speed
    elif (keys_pressed[K_DOWN]):
        speed = max_speed * -1

    if (not (keys_pressed[K_LEFT] ^ keys_pressed[K_RIGHT]) or (keys_pressed[K_LEFT] and keys_pressed[K_RIGHT])):
        turning = 0
    elif (keys_pressed[K_RIGHT]):
        turning = max_turning
    elif (keys_pressed[K_LEFT]):
        turning = max_turning * -1

    if speed == 0 and not turning == 0:
        speed = max_speed

    motor.move(speed, turning)