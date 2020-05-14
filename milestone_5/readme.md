# Milestone 5
## Maze Solving Using the Left Hand on Wall Strategy
To solve a maze (i.e. a path with branches), I needed to make sure that I did not cause the robot to repeat itself.  In an acylical graph (no loops), depth-first search is one valid strategy.  To accomplish this, I programmed the Zumo to always take the leftmost possible path in a fork.  Given my previous week's code, I only needed to make changes in my NavSys (navigation) class to return the desired path to take.  I treated this class as the "brains" of the robot whereas the movement class was the "braun."  On a different note, the way I decided to handle intersections was not to store any state but the turn taken.

## Video
Milestone 5: Get the Zumo to solve a maze with branching.
[![Milestone 5](http://img.youtube.com/vi/eun1vNbt68k/0.jpg)](https://www.youtube.com/watch?v=eun1vNbt68k&list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx&index=5)