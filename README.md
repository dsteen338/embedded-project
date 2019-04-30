# embedded-project


Repository for a project done for my Embdedded Systems class as part of my Software Engineering Degree, by myself and my partner, Alex Everett. The project was done without git for the most part, so the blame considers the work all having been done by me, but it was a collaborative effort.

This contains:

a) A simple python script that runs on a computer alongside the program on the FRDM-K64 board, which communicate with each other via UART serial interface. The script starts by asking the user for how long they want to sleep, and then continuously receieves data from the board every 100ms and plots it. When the user inputted time has passed, the script sends a signal to the program on the FRDM-K64 to sound an alarm.

b) The aformentioned C project that is to be compiled and ran on the board. This program is designed to interface externally with a ADXL337 3-axis accelerometer from sparkfun, and a speaker with an amplifier attached. Upon start, the program takes measurements from the accelerometer, computes the magnitude, and averages and sends them to the script running on the computer, where it is then graphed. After the program receives the "sound alarm" signal, it begins to sound an alarm that plays a varying tone until stopped by pressing a button located on the board. Source files for the project can be found in the `/frdmk64Proj/Sources` folder.
