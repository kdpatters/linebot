# Milestone 2
## Line tracking
For this week, I set up the infared sensors on the front of the Zumo to read in the position of the black electrical tape line using Pololu's provided Zumo library.  This required having the robot rotate and check the values received by each of the IR sensors to determine minimum and maximum readings.  One thing I've noticed about robotics from this project is that they can potentially require a lot of parameter tuning and calibration, so automating as much as possible makes life easier.

I also added PD (proportional & gain) control to track the line.  In PD control (a subset of the common PID control which also uses an integration term) speed is adjusted using a term proportional to the error and a term proportional to the rate of change of the error.

I initially wanted to reuse my code from Milestone 1 without copy-pasting the files, but decided against it after struggling with differences in how paths are represented between operating systems.  One thing I did end up doing was moving all my constants to the "config.h" header file to make it easier to keep track of parameters and modify them efficiently.

## Video
Milestone 2: Get the Zumo to follow a line on the floor for at least 4 feet.
[![Milestone 1](http://img.youtube.com/vi/82Ac8Mnc1Ug/0.jpg)](https://www.youtube.com/watch?v=gfHiJcf17po&list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx&index=3)