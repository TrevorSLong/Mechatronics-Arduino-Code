# Mechatronics-Arduino-Code
This repository contains Arduino code for many basic mechatronics functions that were used in my mechatronics class. Do not use this code to cheat on your own projects if you are taking this course.

  ![Picture of wiring from LCDDisplayTemperature](https://raw.githubusercontent.com/TrevorSLong/Mechatronics-Arduino-Code/master/LCDDisplayTemperature/PictureOfWiring.jpg)
  
## Included Programs

#### CountUp
   * Counts up on a 7 segment display with the display wired directly to the Arduino
#### CountUpWButtonStartStop
   * Starts at zero, counts to 9 and stays until button is hit again, hitting button again restarts count. Debounce incorporated into this program. Uses shift register to address display.
#### CountUpWShiftRegister
   * Counts up on a 7 segment display using a shift register.
#### CountUpIncremental
   * Counts up 1 for every button press and resets to 0 after 9. Uses shift register.
#### LEDBlink
   * Makes and LED blink at a certain frequency
#### LEDBlinkCount
   * Blinks LED for as many times as the button is clicked
#### LEDFadeInOut
   * Fades an LED in and out with a pause in between
#### LEDSwitch
   * Turns and LED on when a switch is pressed
#### LCDDisplayTemperature
   * Measures the temperature with a thermistor and outputs the reading to an LCD display, button toggles between F and C. PDF instructions included
   
## SevSeg-Master
   * Zip file containing SevSeg to use shift register in CountUp Programs, this version is new as of 3/9/21
   * Newest version can be found at `https://github.com/DeanIsMe/SevSeg`

# Git Command
`git clone https://github.com/TrevorSLong/Mechatronics-Arduino-Code`
*  Clones entire repository
*  add `~/FOLDER/SUBFOLDER` after PROGRAM.m to clone to specific folder
   * Ex: `git clone https://github.com/TrevorSLong/Mechatronics-Arduino-Code ~/Mechatronics-Arduino-Code`
   * to clone repository to a folder in home named Mechatronics-Arduino-Code
