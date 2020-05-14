# Milestone 7
## Optimizing the Solution
To shorten the path, I used pointers and a loop to check through the path Vector for reducable patterns which I defined.  After fixing the bugs related to errant redetection of the same intersection, I didn't expect a similar problem to occur when trying to reduce the path to cut out detours.  However, I still had problems with making U-turns since the robot thought that one of these was instead multiple.  To fix this, I needed to increase the ballistic component of turning to ignore sensor readings for the first part and follow a constant routine.


Since the Vector class is implemented using an array, which is somewhat slow to delete elements from in place, I tried using a linked list but decided performance gains were too minimal to implement myself since it doesn't seem to be in the Arduino STL port.  I was able to increase my speed parameters (as well as adding arguments to some of my functions that otherwise would use a slower default speed).  One frusterating problem was that my Zumo's batteries ran quite low a couple times in the last two days which led to erratic behavior with the same parameters which had previously worked fine.  So far my best time is having the robot solve the final maze in about 13 seconds.

### Potential Future Optimizations
- Use higher order functions to adjust speeds (e.g. with peak speed and decay for turning)
- Ignore straight intersections by using approx distance travelled (although this might not be a great idea with the unevenness in my robot's attempts at steering straight forward)
- Begin turning before even eaching a corner and try to keep more momentum by smoothing out the turn (e.g. shifting to the right side of the line before making a left turn)
- Increase speed on straightaways then decrease it before going into intersections.  I was limited by how much I could increase speed by the robot's inability to detect and react to intersections at a high rate of speed.

## Video
Milestone 7: Get the Zumo to solve a maze with branching and then repeat the maze and follow a memorized path.
[![Milestone 6](http://img.youtube.com/vi/eu42vbh9r0s/0.jpg)](https://www.youtube.com/watch?v=eu42vbh9r0s&list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx&index=7)