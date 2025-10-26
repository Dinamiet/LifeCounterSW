# LifeCounter Software

This is the embedded software for the [LifeCounter PCB](https://github.com/Dinamiet/LifeCounterPCB)

## Building
Using CMake to configure and build the project

## Programming
Using OpenOCD to program the board

## Usage

### Knobs
Turning the knob increases and decreases the values on the dislay

### Button Press
Cycles though the availble counters in counter mode

Cycles though the available settings in setting mode

### Button Long press (single beep)
Multiplies current counter value by 10. Usefull for quick adjustment for large counters

Not used in settings mode

### Extra long press (more than 2 beeps)
Switch between setting and counter mode

Counter mode - single status LED will be ON (currently selected counter)
Setting mode - single status LED will be OFF (current selected setting)

Settings are in the following order:
1.	Display brightness
2.	Buzzer Volume
3.	Buzzer Frequency
