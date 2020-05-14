# Milestone 4
## Detecting the Goal
I added code to detect the end of the maze. This was represented by a "T" intersection where all of the sensors on the front of the Zumo would be covered.  In order to detect the end versus a branched intersection, I added a timer to keep track of how long all the sensors were covered and treat the intersection as the end of the maze if the timer exceeded a threshold.


As I had added a class for the "movement system" earlier, I also created a class for the "navigation system."  This allowed me to store the timer and data when trying to detect a given type of intersection.  This also allowed me to further keep my code organized by keeping particular methods and data private and only message passing more abstract data.

## Video
Milestone 4: Get the Zumo to navigate a simple maze with no branching (only one path) and stop when it reaches the end goal.
[![Milestone 4](http://img.youtube.com/vi/nz6N8sSqoEY/0.jpg)](https://www.youtube.com/watch?v=nz6N8sSqoEY&list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx&index=4)