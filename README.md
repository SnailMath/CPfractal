# CPfractal

A program for the fx-cp400 that draws the Barnsley fern (and other fractals). 

This requires [hollyhock-2](htts://www.github.com/SnailMath/hollyhock-2) (or hollyhock) for the classpad II and it will work on the fx-cp400, fx-cp400+E, fx-cg500 and on Linux or WSL. Only tested it under WSL, but it works. (Until now, we haven't tried any program on the cp400+E or cg500 yet, but they are assumed to have the same hardware)

## Usage

Start the program, it will draw the fern consisting of 40000 points. The screen is updatet after every 100 (or 1000) points and Clear or EXE closes the program.
They key 5 turns the overlay on or off, the dot ('.') adds 40000 more points.

## Modifying the fractal

If you want, you can change the values. The values for each equation are in a matrix:

|  a  |  b  |  e  |
| --- | --- | --- |
|  c  |  d  |  f  |

There are four equations, each is displayed with a red rectangle. You can press 7 to change the rectangle you want to edit (displayed in a stronger red) and you can perss 9 to
change the value pair to edit (the 2 parts of the rotation or the translation). You can edit the selected value with the arrow keys or with the numpad 2,4,6,8 ("Nokia Style").

You can use 1 and 3 to change the speed of the change, press 1 multiple times to reduce the step width, press 3 to make it bigger, default is 0.001

