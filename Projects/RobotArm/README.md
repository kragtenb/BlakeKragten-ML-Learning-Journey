<img src="https://github.com/kragtenb/BlakeKragten-ML-Learning-Journey/blob/main/Projects/RobotArm/RobotArmImage.jpg" width="250">

# Project Goal:

The end goal of this project is to have a robot arm be able to grab my daughter’s different shaped blocks and move them into the corresponding holes that the block fits in. 

# 07/01 Demo
 - [Android Screen Recording ](https://drive.google.com/file/d/1_n_BL7S4Z5jAQlqZ_Yptc92PD86K9Nm2/view?usp=sharing)
 - [Video Recording](https://drive.google.com/file/d/1mE7n4JF-AdyxDxL35CmeQN_0uFCiRvsM/view?usp=sharing)

# Project Milestones:
1. Find and print the 3D printed parts for the robot arm (Completed)
2. Assemble Robot arm with servo motors and raspberry pi. (Completed)
3. Create ROS for initial functionality (Completed)
	1. Servo node that will subscribe to messages that will specify value changes to the different servo motors.
	2. Bluetooth node that will create an RFCOMM server that will listen to bluetooth messages and will publish messages to change servo motors if a change servo message is detected. 
4. Implement an Android application to control the servo motors through bluetooth. (Completed)
5. Redesign part of the robotic arm to add a camera and ultrasonic sensor. (Completed)
6. Implement new ROS nodes: (Completed)
	1. Camera node will capture and processing images and publish it to the camera topic
	2. Ultrasonic node will read distance data from the sensor and publish this data to the ultrasonic topic
7. Develop motion planning and control algorithms. (In-progress)
8. Determine position and orientation data based off of camera and ultrasonic sensor.
9. Develop a computer vision model to identify blocks and block holes by fine-tuning a pre-trained CNN.
10. Setup simulation environment of the robot arm to start reinforcement learning to allow the robot arm to understand how to find, pick up and deposit the specific blocks.
11. Integration and testing
12. (Stretch goal) Fine tune LLM to enable the robot arm to perceive and interact with more items than just children blocks and increase the task completion without teaching again using reinforcement learning.

Hardware:

- Raspberry Pi 4: Served as the robot's brain, handling image processing and motor control.
- 6 Servo motors
- Camera: Captured real-time video of the environment.
- Ultrasonic sensor: Capture distance from arm data.

