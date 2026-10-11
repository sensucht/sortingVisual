/*
 * This header handles the raylib drawing function
 * for the columns from the given array.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "raylib.h"
void drawColumns(int *arr, int size, int screenWidth, int screenHeight,
                 int activeA, int activeB, int actionType);

#endif // !GRAPHICS_H
