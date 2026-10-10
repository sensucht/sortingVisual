#include "graphics.h"
#include <raylib.h>
#include <stddef.h> // for NULL definition

void drawColumns(int *arr, int size, int screenWidth, int screenHeight,
                 int activeA, int activeB, int actionType) {
  if (arr == NULL)
    return; // Prevents segfault

  int i;
  float x, y, height;
  float colWidth = (float)screenWidth / size;
  Color colColor = MAROON;

  for (i = 0; i < size; i++) {
    if (i == activeA || i == activeB) {
      if (actionType == 0) {
        colColor = YELLOW; // COMPARE, colors the involved columns yellow
      }
      if (actionType == 1) {
        colColor = GREEN; // SWAP, colors the involved columns green
      }
    }

    x = i * colWidth;
    height = (float)arr[i];
    y = screenHeight - height;

    DrawRectangle((int)x, (int)y, (int)colWidth - 1, (int)height, colColor);

    Vector2 mouse = GetMousePosition();
    Rectangle colRec = {x, y, colWidth, height};

    if (CheckCollisionPointRec(mouse,
                               colRec)) { // Exhibits the value of any column
                                          // when hovering with the mouse
      DrawText(TextFormat("%d", arr[i]), (int)x, (int)y - 20, 20, RAYWHITE);
    }
  }
}
