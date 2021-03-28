# Robot Competition 2020

## Cognitive Science & Autonomous Robotics
I initially created this repository as part of Vassar College's COGS-220-51-2020B: Autonomous Robotics taught by Assistant Professor Josh de Leeuw in Fall of 2020.

## The Project
The goal of this project was to program one of Pololu's Zumo robots to solve an arbitrary maze constructed from electrical tape lines on the floor independently.  The robot was allowed to have a first untimed run to map out the maze and required to solve the maze on its second run (using its stored knowledge) in as little time as possible.  To break up the challenge, the class had 7 milestones.

## The Code
See [Milestone 7](https://github.com/kdpatters/robot_competition_2020/tree/master/milestone_7) cumulative (and best documented!) code [here](https://github.com/kdpatters/robot_competition_2020/tree/master/milestone_7).

<a href="https://www.youtube.com/playlist?list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx
" target="_blank"><img src="http://img.youtube.com/vi/eu42vbh9r0s/0.jpg" 
alt="Milestone 7 attempt" width="240" height="180" border="10" /></a>

### Original milestones
1. Create your own code that moves the Zumo at least 4 feet.
2. Get the Zumo to follow a line on the floor for at least 4 feet.
3. Get the Zumo to follow a line along 2' x 2' square. (Create a square using the tape, 2ft on each side. Place the Zumo anywhere on the square and get it to follow the square for at least a full lap.)
4. Get the Zumo to navigate a simple maze with no branching (only one path) and stop when it reaches the end goal.
5. Get the Zumo to solve a maze with branching.
6. Get the Zumo to solve a maze with branching and then repeat the maze and follow a memorized path.
7. Have a final run in the practice maze of under 15 seconds.

Therefore, this repository is divided into 7 folders, demonstrating incremental versions of a program, from simple to advanced.  Each folder can be uploaded independently onto the Zumo.  My attempts at each of these milestones using the code I wrote are documented in [this YouTube playlist](https://www.youtube.com/playlist?list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx).  I also wrote a little bit about my challenges and thoughts about each week's milestone in the readme files of the associated directories.

## Requirements
- ArduinoSTL library (for vector support)
- ZumoShield library

## References
[Pololu Zumo Shield Arduino Library](https://pololu.github.io/zumo-shield-arduino-library/)
[Pololu Zumo Shield for Arduino User's Guide](https://www.pololu.com/docs/0J57)
