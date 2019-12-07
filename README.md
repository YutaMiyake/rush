# Rush Hour
* https://en.wikipedia.org/wiki/Rush_Hour_(board_game)
* http://www.thinkfun.com/mathcounts/play-rush-hour

# Description
This program solves a given rush game and returns one of the best solutions
which requires the minimum number of moves to get your car out of the box.

# Usage
### Input:<br />
[\# of cars]<br />
[1st car description]<br />
[2nd car description]<br />
...<br />
[end mark = 0]

### Car description:
Syntax: {Length}{Orientation}{Row}{Col}

 Length - the length of car (2|3)<br />
 Orientation - vertical/horizontal (V|H)<br />
 Row - row position [0-5]<br />
 Col - col position [0-5]<br />

### Example:
3<br />
2 H 2 1<br />
2 V 1 3<br />
2 V 3 3<br />
0
### Command:
```bash
$ ./rush [options] < inputfile
```

#### Options:
-t : show the elapsed time to solve

-s : show all the steps to solve

# Author
Yuta Miyake
