# Milestone 6
## Replaying the Path
To store the path, I used a Vector of characters inside of my NavSys class.  To do this, I needed to use ArduinoSTL, a port of C++ STL.  I wanted to have a datatype that was dynamically resizable in order to store an arbitrary size of maze and Vector fit the task. The Vector class also tracks the number of filled elements as well as the capacity of the collection, which is rather convenient.


Despite being able to solve the maze using the left hand strategy for milestone 5, replaying the path was a different story.  I realized I had several bugs leading to redetection of the same intersection multiple times in quick succession.  One problem was that each of the parameters I set seemed quite fickle; it would work with certain code then break later.  I also became quite paranoid about creating shadow over the sensors as I was worried about causing misreadings.  Perhaps as a result of the convenience of having all my parameters in one file, I spent A LOT of time messing with them.

## Video
Milestone 6: Get the Zumo to solve a maze with branching and then repeat the maze and follow a memorized path.
[![Milestone 6](http://img.youtube.com/vi/bNndRgw28Jw/0.jpg)](https://www.youtube.com/watch?v=bNndRgw28Jw&list=PL_vwT-3yRaUgX_wOFEYApaCMzTHfuzczx&index=6)