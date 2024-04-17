from gpiozero import Button
from picamera2 import Picamera2, Preview
from datetime import datetime
from signal import pause

button = Button(2)
camera = Picamera2()
camera_config = camera.create_still_configuration(
    main={"size": (1920, 1080)}, lores={"size": (640, 480)}, display="lores"
)
camera.configure(camera_config)
camera.start_preview(Preview.QTGL)
camera.start()


def capture():
    camera.capture_file(f"/home/bkragten/test_image.jpg")


button.when_pressed = capture

pause()
