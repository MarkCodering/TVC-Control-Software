# Introduction
This Github pages aims to provides a insight information about my coding work on thrust vector control aerospace vehicle.

## Introduction to Thrust Vector Control (TVC)
Thrust vector control (TVC) mechanism is a technique often used in the aerospace industry to control the motion of the vehicle by creating extra torque applied to it.

## Control Program Design Concept
The control program of the TVC   vehicle applies the concept of state-machine and linear controller (P-controller or PID controller). The state-machine is will mainly applied to the mission stage control using if-else determination structure. The linear controller like PID controller will be used to stablised to the motion of the rocket. 

## Control Program Architecture
- Include the libraries
- Declare global variable
- setup Function
- loop Function
- thrust_control_ascend
- thrust_control_descend
- stabilisation
- shutdown