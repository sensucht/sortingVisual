# C Sorting Visualizer

An interactive sorting algorithm visualizer built in C using the **Raylib** library. This project animates how different sorting algorithms operate in real-time by breaking them down into step-by-step visual states.

## Features
* **Custom Array Sizes:** Define the exact number of elements to sort dynamically.
* **Real-time Animation:** Watch algorithms sort pseudo-random data step-by-step.
* **Interactive Hover:** Inspect the exact value of any column by hovering over it with the mouse.
* **Modular Design:** Clean C architecture separating memory management, pure sorting logic, and graphical rendering.

## Included Algorithms (for now)
### $O(n^2)$ sorting algorithms
* Selection sort
* Bubble Sort
* Insertion Sort

## Prerequisites
To compile and run this project, you will need:
* A C compiler (GCC recommended)
* [Raylib](https://www.raylib.com/) installed on your system

## Compilation / How to Run
Open your terminal in the project directory and run:

### Linux

```bash
gcc src/main.c src/app.c src/arrayManager.c src/sorting.c src/graphics.c -I include/ -o visualizer -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./visualizer
```

### Windows (MinGW)
```bash

gcc src/main.c src/app.c src/arrayManager.c src/sorting.c src/graphics.c -o visualizer.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
.\visualizer.exe
```

### macOS

```bash

gcc src/main.c src/app.c src/arrayManager.c src/sorting.c src/graphics.c -I include/ -o visualizer -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
./visualizer
```

## To do:
* Add speed modulation to visualize the algorithms slower or faster
* Add user given range for pseudo-random number generation
* Add additional sorting algorithms (next is Cycle Sort)
