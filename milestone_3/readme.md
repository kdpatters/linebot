# Milestone 3
## Detecting and Responding to Turns
To accomplish this week's task, I used the scaled data from the Zumo's IR sensor array which gives a number between 0 and 1000 for each of the six sensors on a scale from maximum lightness to maximum darkness.  Given that either the leftmost or the rightmost sensor was tripped, I made a response (and turned that direction, since this milestone implied no branching on the path).


For turning, I used ballistic turning instead of reactive, meaning that I did not use feedback signals to make turns but instead relied on hard coded constants.  I tuned these constants prior to the maze run for speed and the time to turn.  I chose to use this method of turning since I assumed that the fastest possible way to solve a maze given is to start turning before seeing the whole intersection.


I had one annoying bug this week caused by the delay of interrupting control of the program until the ZumoBuzzer finished playing some musical notes after a given turn was detected.  This caused a problem due to the latency in detecting the path and potentially the next turn, thus affecting ability to control the direction of the robot smoothly.  As a result, I sought to remove any calls to delay in the program to improve responsiveness.


In terms of code style, I also opted to create files for functions related to movement (e.g. taking a left or right turn) and functions related to navigation (e.g. detecting a particular kind of intersection).  The idea was to keep the implementations separate to make them more modular.

## Video
Milestone 3: Get the Zumo to follow a line along 2' x 2' square. (Create a square using the tape, 2ft on each side. Place the Zumo anywhere on the square and get it to follow the square for at least a full lap.)
[![Milestone 3](http://img.youtube.com/vi/jDXZqXjWxuk/0.jpg)](https://www.youtube.com/watch?v=jDXZqXjWxuk&list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx&index=3)