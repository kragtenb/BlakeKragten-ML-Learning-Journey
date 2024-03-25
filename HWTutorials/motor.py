import RPi.GPIO as GPIO

class Motor():
    front_left_enable = 17
    front_left_in1 = 27
    front_left_in2 = 22

    front_right_enable = 2
    front_right_in1 = 3
    front_right_in2 = 4

    rear_left_enable = 18
    rear_left_in1 = 23
    rear_left_in2 = 24

    #rear_right_enable = 18
    #rear_right_in1 = 24
    #rear_right_in2 = 23

    rear_right_enable = 25
    rear_right_in1 = 7
    rear_right_in2 = 8

    front_left_pwm = None
    front_right_pwm = None
    rear_left_pwm = None
    rear_right_pwm = None

    base_speed = 50
    channel_frequency = 100

    def __init__(self):
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        self.setup_motor(self.front_left_enable, self.front_left_in1, self.front_left_in2)
        self.setup_motor(self.front_right_enable, self.front_right_in1, self.front_right_in2)
        self.setup_motor(self.rear_left_enable, self.rear_left_in1, self.rear_left_in2)
        self.setup_motor(self.rear_right_enable, self.rear_right_in1, self.rear_right_in2)
        self.front_left_pwm = GPIO.PWM(self.front_left_enable, self.channel_frequency)
        self.front_left_pwm.start(0)
        self.front_right_pwm = GPIO.PWM(self.front_right_enable, self.channel_frequency)
        self.front_right_pwm.start(0)
        self.rear_left_pwm = GPIO.PWM(self.rear_left_enable, self.channel_frequency)
        self.rear_left_pwm.start(0)
        self.rear_right_pwm = GPIO.PWM(self.rear_right_enable, self.channel_frequency)
        self.rear_right_pwm.start(0)

    def setup_motor(self, enable, in1, in2):
        GPIO.setup(enable, GPIO.OUT)
        GPIO.setup(in1, GPIO.OUT)
        GPIO.setup(in2, GPIO.OUT)
        GPIO.output(in1, GPIO.LOW)
        GPIO.output(in2, GPIO.LOW)

    def move(self, speed, turning):
        """
        Move the device based on speed and turning values.

        Parameters:
        - speed (int): The forward speed (-100 to 100)
        - turning (int): The turning value (-100 to 100)
        """

        # Ensure the input values are within the expected range
        speed = max(-100, min(100, speed))
        turning = max(-100, min(100, turning))

        #print("Speed: " + str(speed))
        #print("Turning: " + str(turning))

        # Base speed for each side
        if turning < 0:
            # Left Turn
            right_speed = speed
            left_speed = speed - (abs(turning) / 100.0) * speed
            #left_speed = speed / 4 * -1
        elif turning > 0:
            right_speed = speed - (abs(turning) / 100.0) * speed
            left_speed = speed
            #right_speed = speed / 4 * -1
        else:
            right_speed = speed
            left_speed = speed
            #left_speed *= 0.63



        self.adjust_motor(int(left_speed), self.front_left_pwm, self.front_left_in1, self.front_left_in2)
        self.adjust_motor(int(left_speed), self.rear_left_pwm, self.rear_left_in1, self.rear_left_in2)
        self.adjust_motor(int(right_speed), self.front_right_pwm, self.front_right_in1, self.front_right_in2)
        self.adjust_motor(int(right_speed), self.rear_right_pwm, self.rear_right_in1, self.rear_right_in2)

    def adjust_motor(self, speed, pwm, in1, in2):
        pwm.ChangeDutyCycle(abs(speed))

        if speed < 0:
            self.backwards(in1, in2)
        elif speed > 0:
            self.forwards(in1, in2)
        else:
            self.stop(in1, in2)

    def forwards(self, in1, in2):
        GPIO.output(in1, GPIO.HIGH)
        GPIO.output(in2, GPIO.LOW)

    def backwards(self, in1, in2):
        GPIO.output(in1, GPIO.LOW)
        GPIO.output(in2, GPIO.HIGH)

    def stop(self, in1, in2):
        GPIO.output(in1, GPIO.LOW)
        GPIO.output(in2, GPIO.LOW)