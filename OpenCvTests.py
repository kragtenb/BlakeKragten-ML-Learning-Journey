from picamera2 import Picamera2, Preview
import cv2
import numpy as np
import time
from HWTutorials.motor import Motor
from time import sleep

# Initialize Picamera2
picam2 = Picamera2()
preview_config = picam2.create_preview_configuration(main={"size": (640, 480)})
picam2.configure(preview_config)
picam2.start_preview()

# Start camera preview (optional, helps with camera warm up and focus)
# picam2.start_preview(Preview.QTGL)
time.sleep(2)  # Give the camera some time to auto-adjust

# Start camera
picam2.start()

motor = Motor()
speed = 0
turning = 0
max_speed = 100
max_turning = 100
motor.move(0, 0)

try:
    while True:
        # Capture the frame
        image = picam2.capture_array("main")
        # image = cv2.medianBlur(image, 25)
        # Make a copy of the image to draw on
        image_copy = image.copy()

        # Convert BGR to HSV
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        lower_yellow = np.array([5, 240, 50])
        upper_yellow = np.array([20, 255, 255])

        print(hsv[440, 320, :])

        # Threshold the HSV image to get only blue colors
        mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

        # Bitwise-AND mask and original image
        # result = cv2.bitwise_and(image, image, mask=mask)

        # Display the original and the result with matplotlib or use OpenCV's imshow
        # cv2.imshow('Detected Yellow Line', result)

        contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        largest_contour = max(contours, key=cv2.contourArea)

        # Draw the largest contour on the image
        # -1 as the third parameter to draw all contours, (0, 255, 0) for green color, and 2 for thickness
        cv2.drawContours(image_copy, [largest_contour], -1, (0, 255, 0), 2)

        M = cv2.moments(largest_contour)
        if M["m00"] != 0:
            cx = int(M["m10"] / M["m00"])
            cy = int(M["m01"] / M["m00"])

        print("CX: " + str(cx))
        print("CY: " + str(cy))

        x_offset = cx - 320
        turning_value = (x_offset / 320.0) * 100
        if cy >= 300:
            if turning_value < 0:
                turning_value = max(-100, turning_value * 2)
            else:
                turning_value = min(100, turning_value * 2)

        motor.move(max_speed, turning_value)
        sleep(0.25)
        motor.move(0, 0)
        sleep(0.1)

        # cv2.imshow('Original', image)
        # cv2.imshow('Largest Contours', image_copy)

        # cv2.waitKey(0)
        # input()
        cv2.destroyAllWindows()
except KeyboardInterrupt:
    # Stop the preview and camera when the user interrupts the script (e.g., by pressing Ctrl+C)
    picam2.stop_preview()
    picam2.stop()
    motor.move(0, 0)
