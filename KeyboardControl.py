import pygame
from RCFunctionality.motor import Motor
from pygame.locals import (
    QUIT,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    KEYDOWN,
)

from gpiozero import Button
from picamera2 import Picamera2, Preview
from datetime import datetime
from signal import pause
import time

picam2 = Picamera2()
preview_config = picam2.create_preview_configuration(main={"size": (640, 480)})
picam2.configure(preview_config)

# Start camera preview (optional, helps with camera warm up and focus)
picam2.start_preview(Preview.QTGL)
time.sleep(2)  # Give the camera some time to auto-adjust

# Start camera
picam2.start()

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

    if keys_pressed[K_SPACE]:
        file_name = (
            "./TrainingImages/" + datetime.now().strftime("%Y-%m-%dT%H:%M:%S") + ".jpg"
        )
        picam2.capture_file(file_name)
        time.sleep(1)
        print("Captured: " + file_name)

    if not (keys_pressed[K_UP] ^ keys_pressed[K_DOWN]) or (
        keys_pressed[K_UP] and keys_pressed[K_DOWN]
    ):
        speed = 0
    elif keys_pressed[K_UP]:
        speed = max_speed
    elif keys_pressed[K_DOWN]:
        speed = max_speed * -1

    if not (keys_pressed[K_LEFT] ^ keys_pressed[K_RIGHT]) or (
        keys_pressed[K_LEFT] and keys_pressed[K_RIGHT]
    ):
        turning = 0
    elif keys_pressed[K_RIGHT]:
        turning = max_turning
    elif keys_pressed[K_LEFT]:
        turning = max_turning * -1

    if speed == 0 and not turning == 0:
        speed = max_speed

    motor.move(speed, turning)
