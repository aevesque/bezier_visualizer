
# Bezier Editor and Visualizer

Bezier curve editor and visualizer relying on termGL

## Requirements

- A terminal with ANSI colors and Unicode support

## Dependencies

- Make

## How to build

``
 make
``

## Usage

 ./bezierEV

  -o [file]: set [file] as the output file (defaults to 'output')

  -s [number]: set [number] as both x and y output scale

  -x [number]: set [number] as the x output scale

  -y [number]: set [number] as the y output scale

  -h: display help

## Controls

- wasd : move current point
- +/- : add/remove control point
- q/Q : switch to next/previous control point
- e/E : increase/decrease movement sensitivity
- r/R : increase/decrease amount of curve points
- esc : save to file and quit

