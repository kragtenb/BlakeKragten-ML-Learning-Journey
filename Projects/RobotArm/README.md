Project Goal:

The end goal of this project is to have a robot arm be able to grab my daughter’s different shaped blocks and move them into the corresponding holes that the block fits in. 

Project Milestones:
Find and print the 3D printed parts for the robot arm (Completed)
Assemble Robot arm with servo motors and raspberry pi. (Completed)
Create ROS for initial functionality (Completed)
Servo node that will subscribe to messages that will specify value changes to the different servo motors.
Bluetooth node that will create an RFCOMM server that will listen to bluetooth messages and will publish messages to change servo motors if a change servo message is detected. 
Implement an Android application to control the servo motors through bluetooth. (Completed)
Redesign part of the robotic arm to add a camera and ultrasonic sensor. (Completed)
Implement new ROS nodes: (In progress)
Camera node will capture and processing images and publish it to the camera topic
Ultrasonic node will read distance data from the sensor and publish this data to the ultrasonic topic
Develop a computer vision model to identify blocks and block holes by fine-tuning a pre-trained CNN.
Determine position and orientation data based off of camera and ultrasonic sensor.
Develop motion planning and control algorithms.
 Setup simulation environment of the robot arm to start reinforcement learning to allow the robot arm to understand how to find, pick up and deposit the specific blocks.
Integration and testing
(Stretch goal) Fine tune LLM to enable the robot arm to perceive and interact with more items than just children blocks and increase the task completion without teaching again using reinforcement learning.

Hardware:

Raspberry Pi 4: Served as the robot's brain, handling image processing and motor control.
6 Servo motors
Camera: Captured real-time video of the environment.
Ultrasonic sensor: Capture distance from arm data.

