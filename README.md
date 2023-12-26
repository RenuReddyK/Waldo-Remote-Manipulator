# Waldo-Remote-Manipulator

The system involves two components: an input side, moved by the user's hands, and an output side, manipulated by servos to mimic the input. The input side is designed to resemble the structure being controlled.

<iframe src="https://drive.google.com/file/d/1vWRgFe2hMiQNUlWEOjfz0Tas3roO82In/preview" width="640" height="480" allow="autoplay"></iframe>

## Waldo Input:
Designed the input side, considering how to attach sensors and servosnand wrote subroutines for setting up and reading ADC channels, promoting clean and efficient code for general use. Interfaced the ItsyBitsy with potentiometers to display joint positions and angles in a serial window on a computer.

## Waldo Output:
Designed the output side and fabricated the output side by 3D printing and using SG90 RC servos. Wrote code to integrate the input and output sides, aiming for minimal delay in mimicking user input.
