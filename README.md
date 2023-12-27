# Waldo-Remote-Manipulator

The system involves two components: an input side, moved by the user's hands, and an output side, manipulated by servos to mimic the input. The input side is designed to resemble the structure being controlled.

<p align="center">
<img width="550" alt="Screenshot 2023-12-27 at 8 42 44 AM" src="https://github.com/RenuReddyK/Waldo-Remote-Manipulator/assets/68454938/2a9902be-98e8-4719-bb2f-5ab9270ba9e6">
</p>

# Video
[![Watch the video](https://github.com/RenuReddyK/Waldo-Remote-Manipulator/assets/68454938/6a007f56-81cb-4733-a415-1f52da777ac1)](https://drive.google.com/file/d/1vWRgFe2hMiQNUlWEOjfz0Tas3roO82In/preview) 

## Waldo Input:
Designed the input side (Eve), considering how to attach sensors and servosnand wrote subroutines for setting up and reading ADC channels, promoting clean and efficient code for general use. Interfaced the ItsyBitsy with potentiometers to display joint positions and angles in a serial window on a computer.

## Waldo Output:
Designed the output side (Wall-E) and fabricated the output side by 3D printing and using SG90 RC servos. Wrote code to integrate the input and output sides, aiming for minimal delay in mimicking user input.

