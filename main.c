#include "arrayManager.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  /* InitWindow(1024, 768, "Sorting Visualizer");
  SetTargetFPS(int 60); */

  int size = 50;
  int *array = arrayCreate(size);

  arrayGenerateData(array, size, 10, 500);

  arrayFree(array);
  return 0;
}
